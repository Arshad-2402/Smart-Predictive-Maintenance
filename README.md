Smart Predictive Maintenance System (ECS 2003)

An ESP32-based Smart Predictive Maintenance System designed to monitor factory machine operating conditions using vibration, temperature, and electrical current measurements. The system processes sensor readings, displays machine status on an SPI TFT display, and provides visual and audible alerts when configured thresholds are exceeded.

📌 Project Overview

Unexpected machine failures can interrupt production, increase maintenance costs, and affect operational efficiency. This project demonstrates a low-cost embedded monitoring approach that helps identify potentially abnormal machine operating conditions through sensor-based monitoring.

The system integrates an ESP32 microcontroller with sensors and alert components to provide real-time condition monitoring for a small DC motor demonstration setup.

🎯 Objectives

- Monitor machine vibration, temperature, and electrical current.
- Identify potentially abnormal operating conditions using configured thresholds.
- Display sensor information and machine status on a TFT display.
- Provide visual alerts through LEDs and audible alerts through a buzzer.
- Demonstrate an affordable embedded-systems approach to machine condition monitoring.

⚙️ Hardware Components

- ESP32 DevKit V1 — main controller
- SW-420 vibration sensor — vibration detection
- ACS712 20A current sensor — electrical current measurement
- Temperature sensor module — temperature monitoring
- KMR-1.8 SPI TFT display (128 × 160) — status and readings
- Green and red LEDs — status indication
- Buzzer — audible warning
- Small DC motor and separate power supply — demonstration load
- Breadboard, jumper wires, and supporting components

💻 Technologies Used

- Programming language: C++
- Development environment: Arduino IDE
- Microcontroller platform: ESP32
- Embedded systems: Sensor interfacing and GPIO control
- Monitoring method: Threshold-based condition monitoring

🔄 Working Principle

1. The sensors collect information about the motor's operating conditions.
2. The ESP32 reads and processes the available sensor measurements.
3. The readings are compared against configured threshold values.
4. The TFT display presents the sensor information and machine status.
5. LEDs and the buzzer indicate warning conditions when the configured limits are exceeded.

✨ Key Features

- Multi-parameter machine condition monitoring
- ESP32-based sensor integration
- Real-time status display
- Visual and audible warning indicators
- Low-cost hardware implementation
- Modular design for future improvements

📁 Repository Structure

```text
Smart-Predictive-Maintenance/
├── firmware/
│   ├── Smart_Predictive_Maintenance.ino
│   └── README.md
├── images/
│   └── prototype-actual-photo.jpg
├── circuit-diagrams/
│   └── esp32-factory-maintenance-wiring.png
├── docs/
│   ├── project-report.pdf
│   ├── components-and-costs.md
│   └── pin-map.md
├── .gitignore
└── README.md
```


🎓 Project Context

- Project: Smart Predictive Maintenance System
- Project Code: ECS 2003
- Domain: Embedded Systems, IoT, and Industrial Condition Monitoring
- Platform: ESP32
- Application: Factory machine condition monitoring

🚀 Future Enhancements

- Improve sensor calibration and measurement accuracy.
- Add data logging and historical trend analysis.
- Develop a dashboard for remote monitoring.
- Explore machine-learning-based anomaly detection using collected sensor data.
- Evaluate the system under different operating conditions.

📚 Documentation

Refer to the "docs/" directory for the project report, component details, approximate costs, and pin mapping. See "circuit-diagrams/" for the wiring reference and "firmware/" for the ESP32 program.

👥 Acknowledgment

Developed as part of the Engineering and Computer Science (ECS) academic project.

---

Note: The project demonstrates sensor-based condition monitoring using configured thresholds. Predicting future machine failures would require additional data collection, analysis, and validation.
