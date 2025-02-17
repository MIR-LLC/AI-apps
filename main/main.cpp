#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"
#include "portmacro.h"

#include "driver/usb_serial_jtag.h"
#include "esp_console.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_vfs_dev.h"
#include "esp_vfs_usb_serial_jtag.h"
#include "linenoise/linenoise.h"

#include "fcntl.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"

#include "ble_server.h"
#include "grc_cmd.h"
#include "protocol.h"
#include "status.h"
#include "uart.h"

#define PROMPT_STR    CONFIG_IDF_TARGET
#define IO_RX_BUF_LEN IO_MAX_MSG_LEN

#define CTRL_C 3
#define ENTER  10

#define GRC_FLAGS_MONITOR_MODE_MSK BIT0
static EventGroupHandle_t xGRCFlags;
static TaskHandle_t bt_tx_task_handle = NULL;
static TaskHandle_t bt_state_task_handle = NULL;

static int monitor_cmd(int argc, char **argv) {
  printf("Enable UART rx monitor\n");
  xEventGroupSetBits(xGRCFlags, GRC_FLAGS_MONITOR_MODE_MSK);
  return 0;
}

static void register_monitor_cmd(void) {
  const esp_console_cmd_t cmd = {
    .command = "monitor",
    .help = "Enable UART rx monitor",
    .hint = NULL,
    .func = &monitor_cmd,
    .argtable = NULL,
  };
  ESP_ERROR_CHECK(esp_console_cmd_register(&cmd));
}

static void initialize_console(void) {
  /* Drain stdout before reconfiguring it */
  fflush(stdout);
  fsync(fileno(stdout));

  /* Disable buffering on stdin */
  setvbuf(stdin, NULL, _IONBF, 0);

  /* Minicom, screen, idf_monitor send CR when ENTER key is pressed */
  esp_vfs_dev_usb_serial_jtag_set_rx_line_endings(ESP_LINE_ENDINGS_CR);
  /* Move the caret to the beginning of the next line on '\n' */
  esp_vfs_dev_usb_serial_jtag_set_tx_line_endings(ESP_LINE_ENDINGS_CRLF);

  /* Enable blocking mode on stdin and stdout */
  fcntl(fileno(stdout), F_SETFL, 0);
  fcntl(fileno(stdin), F_SETFL, 0);

  usb_serial_jtag_driver_config_t usb_serial_jtag_config =
    USB_SERIAL_JTAG_DRIVER_CONFIG_DEFAULT();

  /* Install USB-SERIAL-JTAG driver for interrupt-driven reads and writes */
  ESP_ERROR_CHECK(usb_serial_jtag_driver_install(&usb_serial_jtag_config));

  /* Tell vfs to use usb-serial-jtag driver */
  esp_vfs_usb_serial_jtag_use_driver();

  /* Initialize the console */
  esp_console_config_t console_config = ESP_CONSOLE_CONFIG_DEFAULT();
  console_config.max_cmdline_length = 256;
  console_config.max_cmdline_args = 8;
  ESP_ERROR_CHECK(esp_console_init(&console_config));

  /* Configure linenoise line completion library */
  /* Enable multiline editing. If not set, long commands will scroll within
   * single line.
   */
  linenoiseSetMultiLine(1);

  /* Tell linenoise where to get command completions and hints */
  linenoiseSetCompletionCallback(&esp_console_get_completion);
  linenoiseSetHintsCallback((linenoiseHintsCallback *)&esp_console_get_hint);

  /* Set command history size */
  linenoiseHistorySetMaxLen(100);

  /* Set command maximum length */
  linenoiseSetMaxLineLen(console_config.max_cmdline_length);

  /* Don't return empty lines */
  linenoiseAllowEmpty(false);
}

static void bt_tx_task(void *pv) {
  char rx_buf[IO_RX_BUF_LEN + 1] = {0};

  for (;;) {
    memset(rx_buf, 0, sizeof(rx_buf));
    int read = uart_read(rx_buf, IO_RECV_HEADER_LEN, portMAX_DELAY);
    if (read > 0) {
      const char *found = strstr(rx_buf, IO_RECV_HEADER);
      if (found == rx_buf) {
        uint8_t msg_len = 0;
        read = uart_read(&msg_len, 1, pdMS_TO_TICKS(1000));
        if (read && msg_len) {
          read = uart_read(rx_buf, msg_len, pdMS_TO_TICKS(1000));
          if (read) {
            rx_buf[read] = '\0';
            if (xEventGroupGetBits(xGRCFlags) & GRC_FLAGS_MONITOR_MODE_MSK) {
              printf("UART rx: bytes=%u: ", read);
              for (size_t i = 0; i < read; i++) {
                printf("%c", rx_buf[i]);
              }
              printf("\n");
            }
            // skip Demo app name
            size_t idx = 0;
            while (idx < read) {
              if (rx_buf[idx] == '_') {
                idx++;
                break;
              }
              idx++;
            }
            // send only actual message
            if (idx < read) {
              ble_msg_send(&rx_buf[idx], read - idx, pdMS_TO_TICKS(0));
            }
          }
        }
      }
    }
  }
}

static int uart_msg_send(const char *msg, size_t len) {
  if (uart_send((void *)IO_SEND_HEADER, IO_SEND_HEADER_LEN,
                pdMS_TO_TICKS(1000)) < 0) {
    printf("UART send timeout\n");
    return -1;
  }

  if (uart_send((void *)msg, len, pdMS_TO_TICKS(1000)) < 0) {
    printf("UART send timeout\n");
    return -1;
  }
  return 0;
}

static void bt_state_task(void *pv) {
  bool ble_connected = false;
  char tx_msg[] = {5, 'B', 'L', 'E', '_', 0};

  for (;;) {
    const auto xBits = xEventGroupGetBits(xStatusEventGroup);
    if (!ble_connected && (xBits & STATUS_STATE_BLE_CONNECTED_MSK)) {
      tx_msg[sizeof(tx_msg) - 1] = 1;
      uart_msg_send(tx_msg, sizeof(tx_msg));
      ble_connected = true;
    } else if (ble_connected && !(xBits & STATUS_STATE_BLE_CONNECTED_MSK)) {
      tx_msg[sizeof(tx_msg) - 1] = 0;
      uart_msg_send(tx_msg, sizeof(tx_msg));
      ble_connected = false;
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

extern "C" void app_main(void) {
  xGRCFlags = xEventGroupCreate();
  if (xGRCFlags == NULL) {
    printf("Error creating xGRCFlags\n");
    return;
  }

  int errors = 0;
  errors += uart_init() < 0;
  if (errors) {
    printf("UART init error\n");
    return;
  }

  errors += ble_server_init() < 0;
  if (errors) {
    printf("ble server init error\n");
    return;
  }

  auto xReturned =
    xTaskCreate(bt_tx_task, "bt_tx_task", configMINIMAL_STACK_SIZE + 1024, NULL,
                1, &bt_tx_task_handle);
  if (xReturned != pdPASS) {
    printf("Unable to create bt_tx_task\n");
  }

  xReturned =
    xTaskCreate(bt_state_task, "bt_state_task", configMINIMAL_STACK_SIZE + 1024,
                NULL, tskIDLE_PRIORITY, &bt_state_task_handle);
  if (xReturned != pdPASS) {
    printf("Unable to create bt_state_task\n");
  }

  initialize_console();

  /* Register commands */
  esp_console_register_help_command();
  register_grc_cmd();
  register_monitor_cmd();

  /* Prompt to be printed before each line.
   * This can be customized, made dynamic, etc.
   */
  const char *prompt = PROMPT_STR "> ";

  printf("\n"
         "This is an example of ESP-IDF console component.\n"
         "Type 'help' to get the list of commands.\n"
         "Use UP/DOWN arrows to navigate through command history.\n"
         "Press TAB when typing command name to auto-complete.\n");

  /* Figure out if the terminal supports escape sequences */
  int probe_status = linenoiseProbe();
  if (probe_status) { /* zero indicates success */
    printf("\n"
           "Your terminal application does not support escape sequences.\n"
           "Line editing and history features are disabled.\n"
           "On Windows, try using Putty instead.\n");
    linenoiseSetDumbMode(1);
  }

  /* Main loop */
  while (true) {
    /* Get a line using linenoise.
     * The line is returned when ENTER is pressed.
     */
    if (xEventGroupGetBits(xGRCFlags) & GRC_FLAGS_MONITOR_MODE_MSK) {
      printf("Press Ctrl+C or Enter to stop\n");
      char c;
      while (read(fileno(stdin), &c, 1)) {
        if (c == CTRL_C || c == ENTER) {
          break;
        }
      }
      printf("Disable UART rx monitor\n");
      xEventGroupClearBits(xGRCFlags, GRC_FLAGS_MONITOR_MODE_MSK);
    }
    char *line = linenoise(prompt);

    if (line == NULL) { /* Break on EOF or error */
      continue;
    }
    /* Add the command to the history if not empty*/
    if (strlen(line) > 0) {
      linenoiseHistoryAdd(line);
    }

    /* Try to run the command */
    int ret;
    esp_err_t err = esp_console_run(line, &ret);
    if (err == ESP_ERR_NOT_FOUND) {
      printf("Unrecognized command\n");
    } else if (err == ESP_ERR_INVALID_ARG) {
      // command was empty
    } else if (err == ESP_OK && ret != ESP_OK) {
      printf("Command returned non-zero error code: 0x%x (%s)\n", ret,
             esp_err_to_name(ret));
    } else if (err != ESP_OK) {
      printf("Internal error: %s\n", esp_err_to_name(err));
    }
    /* linenoise allocates line buffer on the heap, so need to free it */
    linenoiseFree(line);
  }
  esp_console_deinit();
}
