# Fire-Fighting-Robot-
An autonomous and remote‑controlled robot built with an ESP32 that detects fires using IR flame sensors and gas leaks with an MQ‑6 sensor, avoids obstacles, and extinguishes flames via a relay‑controlled water pump. Includes SIM800L GSM alerts, line‑following capability, and web‑based manual control.


# 🚒 ESP32 Fire‑Detecting & Extinguishing Robot

An **autonomous and remote‑controlled firefighting robot** powered by an **ESP32**, designed to detect and extinguish fires while providing real‑time alerts. Equipped with multiple sensors for environmental awareness, the robot can navigate, detect fire sources, extinguish them, and send notifications via GSM.

---

## 📌 Features

* 🔥 **Fire Detection** – Dual IR flame sensors detect fires quickly.
* 💨 **Gas Leak Detection** – MQ‑6 sensor detects flammable gas leaks.
* 🚧 **Obstacle Avoidance** – Ultrasonic sensor with servo scanning.
* 🚗 **Dual Mode** – Operates autonomously or via **web‑based manual control**.
* 📡 **GSM Alerts** – SIM800L sends **SMS/calls** when fire is detected.
* 🚒 **Fire Extinguishing** – Relay‑controlled water pump.
* 🛤 **Line Following** – IR sensors for path tracking.
* 🔊 **Buzzer Alerts** – Audible alerts on hazard detection.

---

## 🛠 Hardware Used

* **ESP32 Dev Board** – Main microcontroller
* **Dual IR Flame Sensors** – Fire detection
* **MQ‑6 Gas Sensor** – Gas leak detection
* **Ultrasonic Sensor + Servo** – Obstacle avoidance
* **SIM800L GSM Module** – Alerts via SMS/Call
* **IR Line Sensors** – Path tracking
* **L298N Motor Driver** – Motor control
* **Relay Module** – Water pump control
* **DC Motors + Wheels** – Robot movement
* **Water Pump** – Fire extinguishing
* **Buzzer** – Alert system

---

## ⚙️ Installation & Setup

1. **Clone the Repository**

   ```bash
   git clone https://github.com/your-username/FireDetectingRobot.git
   cd FireDetectingRobot
   ```

2. **Install Required Libraries** (Arduino IDE)

   * ESPAsyncWebServer
   * AsyncTCP
   * ArduinoJson
   * TinyGSM
   * Any required sensor libraries

3. **Upload the Code**

   * Open in **Arduino IDE**
   * Select **ESP32 Dev Module**
   * Configure **Wi‑Fi credentials** and **phone number** in the code
   * Upload

4. **Power the Robot**

   * Ensure **proper battery connection** (with voltage regulator for SIM800L)

---


## 🚀 How It Works

1. **Autonomous Mode** –

   * Detects flames and gas leaks
   * Avoids obstacles using ultrasonic scanning
   * Extinguishes fire automatically

2. **Manual Mode** –

   * Controlled through a **web interface** over Wi‑Fi
   * Live camera feed (if connected)
   * Remote motor driving and pump activation

3. **Alert System** –

   * Sends **SMS/phone call** on fire detection
   * Displays hazard status on **Firebase dashboard**

---
