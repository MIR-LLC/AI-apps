# GRC AI Apps Kit#1

## Robot Control
- Name: RobotControl
- Messages:
  - Robot Wake Up
  - Robot Sleep
  - Start Control
  - Stop Control
  - Go Right
  - Go Left
  - Go Forward
  - Go Back
  - Go Home
  - Slower Speed
  - Faster Speed
  - Lights On
  - Lights Off
  - Play Music

## Voice PIN
- Name: VoicePIN
- Messages:
  - correct
  - incorrect
  - unlocked
  - locked
- After entering the correct voice PIN, a high signal is sent to pin `GPIO_NUM_14` on ESP32S3 part which is connected to `GPIO_NUM_2` on ESP32C3 part.

## Teacher 3+
- Name: AIteacher
- Messages:
  - correct
  - incorrect
