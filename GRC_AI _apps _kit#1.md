# GRC AI Apps Kit#1

## Interfaces
**Protocol for Interaction between S3 and C3**

The communication protocol is structured as follows:

1. **Message from C3 to S3**:
   - Format: `"GRC_[chip_name]"[message_length_in_bytes]"[actual_message]"`.
   - **Components**:
     - `"GRC_[chip_name]"`: Prefix identifying the chip (e.g., `"GRC_esp32c3"`).
     - `[message_length_in_bytes]`: The length of the actual message as a single-byte number.
     - `[actual_message]`: The command or data being sent, represented as a string.

   **Example**:  
   A command from C3 to S3 to simulate a button press would look like this:  
   `"GRC_esp32c3"17"BUTTON_USER_CLICK"`.

2. **Response from S3 to C3**:
   - Format: `"[application_name][response_message]"`.
   - **Components**:
     - `[application_name]`: The name of the application generating the response (e.g., `"AD4fan"`, `"en_ai_teacher"`).
     - `[response_message]`: The actual message or feedback provided by the application.

   **Examples**:
   - `"AD4fan_MODE1"`: Response from the `"AD4fan"` application with the message `"MODE1"`.
   - `"en_ai_teacher_correct"`: Response from the `"en_ai_teacher"` application with the message `"correct"`.

## Voice PIN
Messages:
- correct
- incorrect
- unlocked
- locked

## Robot Control
- robot
- sleep
- start
- stop
- right
- left
- forward
- backward
- home
- slow
- fast

## Teacher 3+
Messages:
- correct
- incorrect
