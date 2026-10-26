# Smart Predictive Maintenance System (ECS 2003)

A low-cost ESP32-based condition-monitoring prototype intended to demonstrate how machine temperature, vibration, and electrical current can be observed to flag potentially abnormal operating conditions.

> **Project status:** Academic prototype / under development. The repository documents the current design and demonstration materials; it does not claim industrial validation or fully validated predictive-maintenance accuracy.

## Prototype overview

- **Controller:** ESP32 DevKit V1
- **Vibration sensing:** SW-420 vibration module
- **Current sensing:** ACS712 20 A module (the analog interface/divider and calibration still need validation)
- **Temperature sensing:** Three-pin analog temperature module was discussed for the physical setup. The reference firmware in this repository currently uses a **DHT11 temperature/humidity sensor**, so confirm the exact module before uploading or adapt the code.
- **Display:** KMR-1.8 SPI TFT, 128 × 160
- **Indicators:** Green LED, red LED, buzzer
- **Demonstration load:** Small DC motor with separate motor supply

## Repository contents

- `firmware/Smart_Predictive_Maintenance.ino` — reference firmware extracted from the report appendix; **not verified as compile-ready for the current physical wiring**.
- `firmware/README.md` — configuration and safety notes before upload.
- `circuit-diagrams/esp32-factory-maintenance-wiring.png` — wiring reference diagram.
- `images/prototype-actual-photo.jpg` — photo of the physical prototype.
- `docs/project-report.pdf` — project report.
- `docs/components-and-costs.md` — component overview and approximate costs.
- `docs/pin-map.md` — pin map from the report appendix; verify against actual wiring.

## Intended operation

1. Read sensor inputs through the ESP32.
2. Compare readings with configurable threshold values.
3. Show a machine status on the TFT and serial monitor.
4. Use LEDs and a buzzer to indicate a warning state.

The thresholds in the reference code are demonstration values only. They must be tuned for the actual motor and sensors, and must not be treated as industrial safety limits.

## Setup

1. Open the `.ino` file in Arduino IDE.
2. Install the libraries listed in `firmware/README.md`.
3. Verify the exact temperature sensor, TFT controller/tab setting, GPIO wiring, ACS712 variant, divider ratio, and zero-current calibration.
4. Compile and test with the motor supply disconnected first.
5. Test the alert outputs using safe, controlled conditions before connecting the motor supply.

## Limitations

- This is a low-cost academic prototype, not a certified industrial monitoring or safety device.
- Current-sensor readings have previously appeared unstable; validate the analog interface and calibration before relying on current thresholds.
- Predictive capability should not be claimed unless a suitable dataset/model and evaluation results are actually implemented and measured.

## Credits

Developed as an ECS academic project at VIT-AP. Refer to the project report for the team and guidance details.
