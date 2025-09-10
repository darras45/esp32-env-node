# ESP32 IAQ Node

An ESP32-WROOM-32E based Indoor Air Quality (IAQ) monitoring node built with PlatformIO.

## ✨ Features
- ESP32 DevKit (WROOM-32E)
- Sensors (all I²C):
  - **SHTC3** → Temperature & Humidity (low power, high accuracy)
  - **BME680** → VOC/IAQ, Pressure, backup T/RH
  - **SCD40** → CO₂ concentration (ppm)
  - **BH1750** → Ambient light (lux)
- Shared I²C bus (GPIO21 = SDA, GPIO22 = SCL)
- Serial logging at 115200 baud
- Modular design for future BLE advertising and OTA updates

## 🛠 Build Instructions
1. Clone this repo:
   ```bash
   git clone https://github.com/darras45/esp32-env-node.git
2. Open in VS Code with PlatformIO.

3. Build (✓) and Upload (→) to ESP32 DevKit.

4. Open Serial Monitor at 115200 baud to see logs.

| Sensor | VCC  | GND | SDA (ESP32 GPIO21) | SCL (ESP32 GPIO22) |
| ------ | ---- | --- | ------------------ | ------------------ |
| SHTC3  | 3.3V | GND | SDA                | SCL                |
| BME680 | 3.3V | GND | SDA                | SCL                |
| SCD40  | 3.3V | GND | SDA                | SCL                |
| BH1750 | 3.3V | GND | SDA                | SCL                |

All devices share the same I²C bus.

Roadmap

 Part 1: ESP32 + basic code skeleton ✅

 Part 1b: Breadboard prototype with sensors

 Part 2: Custom PCB design (KiCad)

 Part 3: BLE advertisement + OTA updates

 Part 4: Enclosure + field testing