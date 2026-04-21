# 🌊 Flood Monitoring System using ESP8266

## 📌 Overview

A smart flood monitoring system using ESP8266 and an ultrasonic sensor to detect rising water levels in real-time. The system improves accuracy by taking multiple readings and calculating their mean value to reduce noise caused by water waves.

---

## 🚨 Problem Statement

Floods can cause severe damage to life and property. Early detection of rising water levels is crucial. This project provides a low-cost and reliable solution for real-time flood monitoring and alert alerts.

---

## ⚙️ How It Works

* Ultrasonic sensor measures distance between sensor and water surface
* A floating thermocol object stabilizes readings and reduces wave disturbance
* System takes 50 readings and calculates the mean value
* Mean value is displayed on OLED screen
* If water level crosses threshold (~3 cm):

  * Buzzer turns ON
  * LED turns ON
* ESP8266 enables WiFi monitoring (Blynk integration)

---

## ✨ Features

* Accurate measurement using mean of 50 readings
* Real-time monitoring
* OLED display output
* Buzzer alert system
* LED warning indicator
* WiFi-based monitoring

---

## 🔌 Components Used

* ESP8266 (NodeMCU)
* Ultrasonic Sensor (HC-SR04)
* OLED Display (SSD1306)
* Buzzer
* LEDs
* Thermocol (floating object)
* Jumper wires & breadboard

---

## 📐 Working Logic

* Distance increases as water level rises
* Mean of 50 readings avoids false alerts due to waves
* Threshold set around 3 cm
* If mean ≤ threshold → ALERT triggered

---

## 📊 Applications

* Flood monitoring
* River water level monitoring
* Dam safety systems
* Water tank level detection

---

## 🚀 Future Improvements

* SMS/Email alerts
* Solar-powered system
* Data logging
* AI-based flood prediction

---

## 📸 Project Images

*Add your project images here*

## 🎥 Demo Video

*Add your demo video link here*

## 🔧 Circuit Diagram

*Add your circuit diagram here*

---

## 👨‍💻 Author

**Nishchay Agrawal**

---

## 📜 License

This project is open-source and free to use for educational purposes.
