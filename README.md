# 🚀 Missile Defence System Prototype 

This project is a prototype of a **missile defence system** built using Arduino Uno. It detects approaching objects using an ultrasonic sensor and simulates tracking and targeting using servo motors, with alerts via buzzer and LED.

---

## 🚀 Features
- Object detection using ultrasonic sensor  
- Target tracking using dual servo motors  
- Audio alert using buzzer  
- Visual alert using LED  
- Real-time response system  

---

## 🧰 Components Used
- Arduino Uno  
- Breadboard  
- Servo Motor (SG90)  
- Servo Motor (MG996R)  
- Ultrasonic Sensor (HC-SR04)  
- Buzzer  
- LED  
- Resistors  
- Jumper Wires  

---

# 🔌 Pin Connections

## 🔹 Ultrasonic Sensor (HC-SR04)
| Pin | Arduino |
|-----|--------|
| VCC | 5V |
| GND | GND |
| TRIG | 9 |
| ECHO | 10 |

---

## 🔹 Servo Motor (SG90 - Horizontal)
| Wire | Arduino |
|------|--------|
| Red | 5V |
| Brown | GND |
| Orange | 5 |

---

## 🔹 Servo Motor (MG996R - Vertical)
| Wire | Arduino |
|------|--------|
| Red | External 5V/6V |
| Brown | GND |
| Orange | 6 |

---

## 🔹 Buzzer
| Pin | Arduino |
|-----|--------|
| + | 7 |
| - | GND |

---

## 🔹 LED
| Pin | Arduino |
|-----|--------|
| Anode (+) | 8 (via resistor) |
| Cathode (-) | GND |

---

# ⚙️ Working Principle
The ultrasonic sensor continuously measures distance. When an object is detected within a threshold range, the Arduino activates the servo motors to simulate tracking. Simultaneously, the buzzer and LED are triggered to provide warning signals.

---

#🔄 Flow Logic
Start → Measure Distance → Object Detected?
          ↓ YES                ↓ NO
     Move Servos          Keep Scanning
     Activate Alert
          ↓
        Loop

---

## 🎥 Project Demo

[![Watch the video](https://img.youtube.com/vi/7qkNw4xBlLQ/0.jpg)](https://youtu.be/7qkNw4xBlLQ)

---

🎯 Applications
1. Defence system simulation
2. Object tracking systems
3. Robotics learning projects

---

📚 Learning Outcomes
1. Sensor interfacing
2. Servo motor control
3. Real-time system response
4. Embedded programming

---

📄 License

Open-source for educational purposes.
