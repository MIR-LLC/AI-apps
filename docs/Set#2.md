# GRC AI Apps Kit #2

Ready-to-use software for quickly starting the development of Edge AI applications based on the GRC Development Board.

This kit includes preinstalled applications that can be used for your scenarios:

- **Teacher 7+**
- **Rhythm PIN**
- **Anomaly Detection**

<img src="https://github.com/user-attachments/assets/20e785a2-c038-4ea8-bf42-8d3d5cd57d95" width=30%>

## Demo Applications

### Rhythm PIN-code
Springs into action when a user inputs a pre-rhythmic sequence.

### Anomaly Detection
Identifies equipment operational modes and detects malfunctions.

### Teacher 7+ (English)
Full version of App for English words learning for kids 7+.

You can utilize these pre-installed apps in your own scripts by using the open-source component that runs on the ESP32-C3. Feel free to modify it to meet your specific needs, equipment, and tasks.

**[Open-source software component on GitHub](https://github.com/Grovety/GRC-AI-apps/blob/main/GRC_AI_apps_kit%232.md)**


### Where can it be used?
- **tinyML devices development**
- **DIY electronics**
- **AI/ML technologies studying**

## Applications Overview

### Rhythm PIN
This application allows the DevBoard to function as an electronic switch that activates when a user inputs a rhythmic sequence.

This personalized rhythm acts as a secure key to prevent unauthorized use, ensuring that the switch activates only for the right person, at the right beat.

#### Use Cases
- Automated entry management
- Smart home device regulating access with a rhythmic 'password' — imagine simply tapping a beat to control lighting, fans, and your HVAC system.
- Access to the car: secrets and a code rhythm for starting the engine.
- Restriction of access inside office premises.
- Personal lockers without physical keys or memorizing digital combinations.

#### Interfaces
You can use UART and other interfaces to interact with the app. [Learn more](https://github.com/Grovety/GRC-AI-apps/blob/main/GRC_AI_apps_kit%232.md).


You can utilize the specified DevBoard output to control external devices, such as an electric lock latch. Alternatively, you can use the second microcontroller (ESP32-C3) to develop your own methods for controlling external devices.

---

### Anomaly Detection
The app leverages a vibration sensor (built-in or external) and analyzes data streams for real-time monitoring of mechanical equipment. It employs advanced recurrent neural networks for on-device learning, negating the need for extensive pre-training.

#### Usage
- Identifies equipment operational modes and detects malfunctions.
- Acts as a field sensor for predictive maintenance systems.

#### Features
- Learns equipment operational modes.
- Classifies normal operation and identifies anomalies when malfunctions occur.

#### Target Equipment
- Electric Motors
- Pumps and Turbines
- Internal Combustion Engines
- Generators
- Refrigeration Units

#### Interfaces
You can use UART and other interfaces to interact with the app. [Learn more](https://github.com/Grovety/GRC-AI-apps/blob/main/GRC_AI_apps_kit%232.md).

---

### Teacher 7+
The application uses an approach that involves engaging the child through different perception channels. This includes demonstrating how to write and pronounce words, as well as showing pictures, sounds, and examples of addition and subtraction.

#### How It Works
This toy displays pictures of various objects, plays sounds, shows numbers, and provides simple examples of addition and subtraction up to 20.

Children not only learn new words but also memorize them through immediate communication with the toy, similar to how native speakers acquire language.

When using the toy, children vocalize their answers, and the AI Teacher recognizes whether their responses are correct. If a child is unable to answer, they can skip the word by pressing the left button or request a hint by pressing the right button. This action will display the word and produce the correct pronunciation.

#### Summary
- **English language learning device**
- **Learning words**
- **Pronunciation training**
- **Training through different channels**
  - Pictures
  - Sounds
  - Numbers in addition and subtraction examples

#### Topics
- Numbers (0 to 20)
- Animals
- Nature
- Human
- Objects
- House
- Alphabet
- Verbs
- School
- Shapes

#### Interfaces
You can use UART and other interfaces to interact with the app. [Learn more](https://github.com/Grovety/GRC-AI-apps/blob/main/GRC_AI_apps_kit%232.md).


---

## Overview

### Master Module
- ESP32-S3

### Communication Module
- ESP32-C3

### Connectivity
- USB, UART to USB interface CP2102N
- Wi-Fi 802.11 b/g/n
- Bluetooth LE: Bluetooth 5, Bluetooth mesh

### Periphery
- 2 MEMS microphone
- Accelerometer MPU-9250
- 4 buttons
- Amplifier MAX98357A
- Speaker FUET_FS_1340
- 3 RGB LEDs – SK6805
- Monochrome OLED Display 0.96" 128x64

### Power
- **USB-C port:** 5V, 500mA (min)
- **2 PIN socket:** LiPo 1S - 3.7V
- **Power consumption (average):** 30mA

Check the full specification at link: **[GRC tinyML DevBoard Specification](https://github.com/Grovety/GRC-AI-apps/blob/main/DevBoard_Specification.md)**

---

## Links
- [GRC tinyML DevBoard Specification](https://github.com/Grovety/GRC-AI-apps/blob/main/DevBoard_Specification.md)
- [ESP32-S3-WROOM](https://www.espressif.com/sites/default/files/documentation/esp32-s3-wroom-1_wroom-1u_datasheet_en.pdf)
- [MP34DT06JTR Datasheet](https://www.st.com/resource/en/datasheet/mp34dt06j.pdf)
- [MPU-9250 Datasheet](https://invensense.tdk.com/wp-content/uploads/2015/02/PS-MPU-9250A-01-v1.1.pdf)
