[Описание "Управления роботом"](https://github.com/MIR-LLC/AI-apps/blob/main/docs/Robot_Control_Description.md)

[Описание набора приложений App1 (Управление роботом, Голосовой ПИН-код, Тичер3+)](https://github.com/MIR-LLC/AI-apps/blob/main/docs/GRC_AI_App%231.md)

[Описание отладочной платы](https://github.com/MIR-LLC/AI-apps/blob/main/docs/DevBoard_Specification.md)


# Пример приложения взаимодействия ESP32S3 и ESP32C3

1. Пример показывает как установить приложение на С3 для взаимодействия с S3 с помощью UART интерфейса.
    - Введите `help` для просмотра поддерживаемых команд.
    - По умаолчанию все ссобщения полученные от ESP32S3 отправляются с использованием [BLE](https://github.com/MIR-LLC/AI-apps/blob/main/BLE.md). Все возможные сообщения описаны здесь: [GRC_AI_apps_kit#1.md](https://github.com/MIR-LLC/AI-apps/blob/main/GRC_AI_apps_kit%231.md).

2. Протокол взаимодействия через UART [здесь](https://github.com/MIR-LLC/AI-apps/blob/main/GRC_protocol.md).

3. UART параметры:

| Parameter           | Value                                |
| ------------------- | ------------------------------------ |
| UART TX pin         | GPIO_NUM_21                          |
| UART RX pin         | GPIO_NUM_20                          |
| UART NUM            | UART_NUM_1                           |

# Build instructions

ESP-IDF version: v5.2.1

## Supported devices

- GRC Devboard esp32c3

## Configure the project

```bash
idf.py menuconfig
```

## Build, Flash and Run

Build the project and flash it to the board:

```
idf.py -p PORT build flash monitor
```

(Replace PORT with the name of the serial port to use)
___________

Также вы можете использовать готовый бинарный файл: https://github.com/MIR-LLC/AI-apps/tree/main/firmware

Чтобы прошить плату используйте: https://github.com/MIR-LLC/AI-apps/blob/main/firmware/flash_tool.zip
