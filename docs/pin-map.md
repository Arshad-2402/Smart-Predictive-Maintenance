# Pin map reference

This map is transcribed from the report's reference firmware. **It is not proof that the current physical wiring uses these exact pins.** Check the actual circuit before powering the system.

| Module / signal | ESP32 GPIO |
|---|---:|
| TFT CS | 5 |
| TFT DC | 2 |
| TFT RST | 14 |
| TFT SCLK | 18 |
| TFT MOSI | 23 |
| Temperature/humidity data (DHT11 draft) | 4 |
| SW-420 digital output | 27 |
| ACS712 analog output via divider | 34 |
| Green LED | 25 |
| Red LED | 26 |
| Buzzer | 33 |

The report draft assumes the ACS712 sensor output is scaled by a divider ratio of 1.5 when converting the ESP32 ADC voltage back to sensor-output voltage. Validate the divider wiring and calibration with the actual components before relying on readings.
