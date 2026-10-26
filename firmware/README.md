# Firmware — read before uploading

`Smart_Predictive_Maintenance.ino` is a **reference draft extracted from the project report appendix**, not a confirmed final firmware release. It has not been verified against the current hardware in this repository.

## Libraries expected by the draft

- Adafruit GFX Library
- Adafruit ST7735 and ST7789 Library
- DHT sensor library (Adafruit)

## Important hardware checks

1. **Temperature sensor mismatch:** this draft uses a DHT11 on GPIO 4 (temperature and humidity). The physical project discussion also described a three-pin `OUT`, `+`, `-` temperature module. Identify the exact part first. Do not connect a DHT11 sketch to an analog-only temperature module without changing the code.
2. **TFT:** draft uses CS=GPIO 5, DC=GPIO 2, RST=GPIO 14, SCLK=GPIO 18, MOSI=GPIO 23 and `INITR_GREENTAB`. Confirm your display pin labels and controller/tab option.
3. **ACS712:** draft assumes 0.100 V/A sensitivity and a 1.5 divider multiplier. Confirm these match the exact sensor and divider wiring. The observed readings have been unstable, so do not trust the current threshold until zero-current calibration is stable.
4. **Vibration module:** draft assumes active HIGH on GPIO 27. Confirm the module's output polarity.
5. **Motor power:** keep the motor supply disconnected while checking wiring and compiling. Never power the motor directly from an ESP32 GPIO.

## Draft pin map

| Signal | GPIO |
|---|---:|
| TFT CS | 5 |
| TFT DC | 2 |
| TFT RST | 14 |
| TFT SCLK | 18 |
| TFT MOSI | 23 |
| DHT11 data (draft only) | 4 |
| SW-420 digital output | 27 |
| ACS712 analog input | 34 |
| Green LED | 25 |
| Red LED | 26 |
| Buzzer | 33 |

Compile first; then test each sensor separately. Treat the displayed `NORMAL` / `WARNING` status as a demonstration indicator, not a safety guarantee.
