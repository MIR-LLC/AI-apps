# GRC AI Apps Kit#1

## Voice PIN
- Name: VoicePIN
- Messages:
  - correct
  - incorrect
  - unlocked
  - locked
- After entering the correct voice PIN, a high signal is sent to pin `GPIO_NUM_14` on ESP32S3 part which is connected to `GPIO_NUM_2` on ESP32C3 part.

## Robot Control
- Name: RobotControl
- Messages:
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
- Name: AIteacher
- Messages:
  - correct
  - incorrect
