# GRC AI Apps#1

Ready-to-use software for quickly starting the development of Edge AI applications based on the GRC Development Board. 

This kit includes preinstalled applications that can be used for your scenarios:

- Robot Control
- Voice PIN
- Teacher 3+
  
<img src="https://github.com/user-attachments/assets/20e785a2-c038-4ea8-bf42-8d3d5cd57d95" width=30%>

---

## Preinstalled Applications

### Robot Control
Voice command recognition and tilt control for Arduino robots and other devices. 

### Voice PIN-Code
Springs into action when a user inputs a pre-set voice PIN code (four digits) that the user says.

### Teacher 3+ (English)
Full version of an app for English word learning for kids 3+.

---

**You can utilize these pre-installed applications alongside an open-source component running on the ESP32-C3.**

While the applications themselves are not open-source, this component provides access to their output data and enables you to control and manage them, send commands, and supply data for processing, allowing integration and customization for your specific tasks, equipment, and scenarios. 

**[Open-source software component on GitHub](https://github.com/Grovety/GRC-AI-apps/blob/main/GRC_AI_apps_kit%231.md)**

---

## Where Can It Be Used?

- tinyML devices development
- DIY electronics
- AI/ML technologies studying

---

## Applications Overview

### Robot Control
An app for controlling devices, such as robots, using voice commands and gestures like tilting a board in different directions. Both modes can be used simultaneously or separately. 


**Voice Control**

Commands List: robot, sleep, start, stop, right, left, forward, backward, home, slow, fast, light, music. 

The application operates in constant mode, listening for user commands through the built-in microphones. When it detects a command from its predefined list, the application recognizes it, announces it through the speaker on the development board, and transmits it via BLE and wired connections. 

The command that is sent can be transformed into movement commands by the robot or other devices. Additionally, you can process the command using the onboard ESP32-C3 microcontroller, allowing you to convert it directly into commands for controlling the motors without the need for extra computing boards. 

**Tilt Control**

The app detects the tilt of a board and translates it into commands to control a robot. Tilting forward makes the robot accelerate, while tilting backward slows it down or moves it in reverse. Tilting to the sides makes it turn. The controls are intuitive and engaging, offering a fun user experience. This system can be adapted to control different types of machines.  

#### Interfaces:
You can use UART and other interfaces to interact with the app. [Learn more](https://github.com/Grovety/GRC-AI-apps/blob/main/GRC_AI_apps_kit%231.md).

---

### Voice PIN
This application allows the DevBoard to function as an electronic switch that activates when a user says a pre-set voice PIN code consisting of four digits. 

It serves as a secure key to prevent unauthorized use, ensuring that the switch activates only for the authorized user who knows the correct PIN.

#### Use Cases:
- Automated entry management.
- Smart home device regulating access — imagine simply saying a PIN code to control lighting, fans, and your HVAC system.
- Access to the car: voice activation for starting the engine.
- Restriction of access inside office premises.
- Personal lockers without physical keys.

#### Interfaces:
You can use UART and other interfaces to interact with the app. [Learn more](https://github.com/Grovety/GRC-AI-apps/blob/main/GRC_AI_apps_kit%231.md).

You can utilize the specified DevBoard output to control external devices, such as an electric lock latch. Alternatively, you can use the second microcontroller (ESP32-C3) to develop your own methods for controlling external devices.

---

### Teacher 3+
The application uses an approach that involves engaging the child through different perception channels. This includes demonstrating how to write and pronounce words, as well as showing pictures, sounds, and examples of addition and subtraction.

#### How It Works:
- The Teacher displays pictures of various objects, plays sounds, shows numbers, and provides simple examples of addition and subtraction up to 20.
- Children not only learn new words but also memorize them through immediate communication with the toy, similar to how native speakers acquire language.
- When using the toy, children vocalize their answers, and the AI Teacher recognizes whether their responses are correct.
- If a child is unable to answer, they can skip the word by pressing the left button or request a hint by pressing the right button. This action will display the word and produce the correct pronunciation.

#### Summary:
- English language learning device.
- Learning words.
- Pronunciation training.
- Training through different channels:
  - Pictures.
  - Sounds.
  - Numbers in addition and subtraction examples.

#### Topics:
- Numbers (0 to 20).
- Animals.
- Nature.
- Human.
- Objects.

#### Interface:
You can use UART and other interfaces to interact with the app. [Learn more](https://github.com/Grovety/GRC-AI-apps/blob/main/GRC_AI_apps_kit%231.md).

---

## Overview

### Master Module:
- ESP32-S3

### Communication Module:
- ESP32-C3

### Connectivity:
- USB, UART to USB interface CP2102N
- Wi-Fi 802.11 b/g/n
- Bluetooth LE: Bluetooth 5, Bluetooth mesh

### Periphery:
- 2 MEMS microphones
- Accelerometer MPU-9250
- 4 buttons
- Amplifier MAX98357A
- Speaker FUET_FS_1340
- 3 RGB LEDs – SK6805
- Monochrome OLED Display 0.96" 128x64

### Ports:
- USB-C port: 5V, 500mA (min)
- 2 PIN socket: LiPo 1S - 3.7V

### Power Consumption (Average):
- 30mA

Check the full specification at the link: **[GRC tinyML DevBoard Specification](https://github.com/Grovety/GRC-AI-apps/blob/main/DevBoard_Specification.md)**

---

## Links:
- [GRC tinyML DevBoard Specification](https://github.com/Grovety/GRC-AI-apps/blob/main/DevBoard_Specification.md)
- [ESP32-S3-WROOM](https://www.espressif.com/sites/default/files/documentation/esp32-s3-wroom-1_wroom-1u_datasheet_en.pdf)
- [MP34DT06JTR Datasheet](https://www.st.com/resource/en/datasheet/mp34dt06j.pdf)
- [MPU-9250 Datasheet](https://invensense.tdk.com/wp-content/uploads/2015/02/PS-MPU-9250A-01-v1.1.pdf)
