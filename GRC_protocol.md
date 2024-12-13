**Protocol for Interaction between ESP32S3 and ESP32C3**

> **Note**
>
> - Strings in double quotes are sent byte by byte without null-terminator over the serial interface (UART).
> - Message length passed as a single-byte, so the maximum message length is 256 bytes.

The communication protocol is structured as follows:
1. **Message (command) from ESP32C3 to ESP32S3**:
   - Format: `"GRC_[chip_name]"[message_length_in_bytes]"[actual_message]"`.

   - **Components**:
     - `"GRC_[chip_name]"`: Prefix identifying the chip (e.g., `esp32c3`).
     - `[message_length_in_bytes]`: The length of the `actual message` as a single-byte number.
     - `"[actual_message]"`: The command or data being sent, represented as a string.

   **Example**:  
   A command from ESP32C3 to ESP32S3 to simulate a button press would look like this:  
   `"GRC_esp32c3"17"BUTTON_USER_CLICK"`.

2. **Response from ESP32S3 to ESP32C3**:
   - Format: `"GRC_[chip_name]"[message_length_in_bytes]"[application_name]_[response_message]"`.
   - **Components**:
     - `"GRC_[chip_name]"`: Prefix identifying the chip (e.g., `esp32c3`).
     - `[message_length_in_bytes]`: The length of the actual message as a single-byte number.
     - `"[application_name]"`: The name of the application generating the response (e.g., `"AD4fan"`, `"AIteacher"`).
     - `"[response_message]"`: The actual message or feedback provided by the application.

   **Examples**:
   - `"GRC_esp32s3"12"AD4fan_MODE1"`: Response from the `"AD4fan"` application with the message `"MODE1"`.
   - `"GRC_esp32s3"17"AIteacher_correct"`: Response from the `"AIteacher"` application with the message `"correct"`.
   - `"GRC_esp32s3"20"RobotControl_forward"`: Response from the `"RobotControl"` application with the message `"forward"`.

3. **Commands supported by ESP32S3**:
    - "BUTTON_[button_name]_[button_action]" - simulate button press.

        - **Components**:
        - `[button_name]`: USER, SW3, SW4.
        - `[button_action]`: CLICK, HOLD.

    - "SEL_DEMO_[application_name]" - select demo application.

        - **Components**:
        - `[application_name]`: The name of the target application (e.g., `"AD4fan"`, `"AIteacher"`).

    - "RESTART" - restart ESP32S3.