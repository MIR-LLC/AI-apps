# Управление роботом 

TПриложение для управления различными устройствами, прежде всего - движением роботов.   

> Check out our [Arduino open-source program](https://github.com/Grovety/CrowBot_GRC_program/tree/main) for the [CrowBot-BOLT robot](https://www.elecrow.com/crowbot-bolt-programmable-smart-robot-car-steam-robot-kit.html), which is ready to use right out of the box! We designed it to showcase voice control and tilt-based movement. You can also use it as a reference for your projects, adapt it for other robots and devices, or explore new possibilities with the CrowBot.

## Как устроено управление роботом 

Решение состоит из двух частей 

The first part is a neural network-based proprietary software running on the ESP32-S3 SoC on the GRC Development Board. It performs two main functions: 
Первая часть - это программное обеспечение, в том числе нейронные сети, которые работают на ESP32-S3 на нашей плате. Их задача  

1. Распознавание голосовых команд 
2. Определение углов наклона платы в пространстве (по осям X и Y)

![RCax](https://github.com/user-attachments/assets/df23ef1b-fbf7-4044-8efd-d63a35861690)

Вторая часть - это API и программное обеспечение, которые дают разработчику возможность работать с результатом работы первой части для создания собственных кастомизированных решений. 

- описание API 
- Открытый пример реализации работы с API

## Voice Control
The board "listens" to user commands through its built-in microphones and recognizes them using a neural network running on the S3.

The recognized command is transmitted as a text string for further use by the user application, which runs on the C3 (use the reference<link>).

Additionally, the board provides visual and audio feedback for recognized commands:

- The command is displayed on the built-in screen.
- In case of successful recognition, the DevBoard LEDs blink green.

**Important:** Users cannot modify the list of commands or adjust the neural network settings. You have access to the results of the neural network's inference, which are provided as a recognized text command in string format transferred to C3.

### List of Predefined Voice Commands

- ROBOT WAKE UP
- ROBOT SLEEP
- MANUAL CONTROL
- VOICE CONTROL
- GO RIGHT
- GO LEFT
- GO FORWARD
- GO BACK
- GO HOME
- SLOWER SPEED
- FASTER SPEED
- LIGHTS ON
- LIGHTS OFF
- PLAY MUSIC

## Tilt Control
### Entering the Mode

To switch to tilt control mode:
-	Use the voice command "Start Control"
or
-	Press the USER button.

**Note:** When entering tilt control mode, calibration is performed. Keep the board horizontal. To recalibrate, press the SW3 button (located on the bottom-left side of the board).

After switching to tilt control mode, this image will appear on the DevBoard's screen.

![DB](https://github.com/user-attachments/assets/97d87ccf-da3e-4ba6-912a-830ea2277bbc)

The deviation of the circle from the center of the intersecting lines visually indicates the degree of board tilt.

**Important Note:** In tilt control mode, you can continue to use voice commands. The board will no longer repeat or display them on the screen, but LED indicators will remain active, and you can still retrieve the recognized command as a text string via the API.

### Exiting the Mode
- Use the voice command "Stop control"
- Press the USER button.

### Message Format:
- Messages from the **ESP32S3** to the **ESP32C3** follow this [protocol](https://github.com/Grovety/GRC-AI-apps/blob/main/GRC_protocol.md).
- **Sample rate:** 15 Hz.
- Board orientation is represented by two angles: **x (roll)** and **y (pitch)**, in the range **(-90°, 90°)**.
- Each coordinate is stored in **1 byte**.
- Coordinates are prefixed with the string **`XY`**.
- Example message: `"RobotControl_XY"[x_coord][y_coord]`.







