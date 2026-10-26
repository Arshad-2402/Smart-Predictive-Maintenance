// REFERENCE DRAFT extracted from the project report appendix. See firmware/README.md before uploading.
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <DHT.h>
#include <math.h>
#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST 14
#define TFT_SCLK 18
#define TFT_MOSI 23
Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);
#define DHT_PIN       4
#define DHT_TYPE      DHT11
#define VIBRATION_PIN 27
#define CURRENT_PIN   34
#define GREEN_LED     25
#define RED_LED       26
#define BUZZER_PIN    33
DHT dht(DHT_PIN, DHT_TYPE);
const float TEMP_LIMIT = 40.0;
const float HUMIDITY_LIMIT = 80.0;
const float CURRENT_LIMIT = 1.5;
const float ACS_SENSITIVITY = 0.100;
const float DIVIDER_RATIO = 1.5;
const bool VIBRATION_ACTIVE_HIGH = true;
float temperature = NAN, humidity = NAN;
float currentAmps = 0.0, zeroCurrentVoltage = 2.50;
bool vibrationDetected = false, warning = false;
unsigned long lastRead = 0;
const unsigned long READ_INTERVAL = 2000;
float readCurrent() {
uint32_t totalMilliVolts = 0;
for (int i = 0; i < 20; i++) {
totalMilliVolts += analogReadMilliVolts(CURRENT_PIN);
delay(2);
}
float adcVoltage = (totalMilliVolts / 20.0) / 1000.0;
float sensorVoltage = adcVoltage * DIVIDER_RATIO;
float amps = (sensorVoltage - zeroCurrentVoltage)
/ ACS_SENSITIVITY;
return fabs(amps);
}
void calibrateCurrentSensor() {
Serial.println("Calibrating ACS712...");
Serial.println("Keep motor OFF.");
delay(1500);
uint32_t totalMilliVolts = 0;
for (int i = 0; i < 100; i++) {
totalMilliVolts += analogReadMilliVolts(CURRENT_PIN);
delay(10);
}
float adcVoltage = (totalMilliVolts / 100.0) / 1000.0;
zeroCurrentVoltage = adcVoltage * DIVIDER_RATIO;
Serial.print("Zero-current voltage: ");
Serial.println(zeroCurrentVoltage, 3);
}
void displayDashboard() {
tft.fillScreen(ST77XX_BLACK);
tft.setTextWrap(false);
tft.setTextSize(1);
tft.setTextColor(ST77XX_CYAN);
tft.setCursor(4, 4);
tft.println("MACHINE MONITOR");
tft.drawFastHLine(0, 16, 160, ST77XX_WHITE);
tft.setTextColor(ST77XX_WHITE);
tft.setCursor(4, 24);
tft.print("Temp: ");
if (isnan(temperature)) {
tft.println("Sensor error");
} else {
tft.print(temperature, 1);
tft.println(" C");
}
tft.setCursor(4, 42);
tft.print("Humidity: ");
if (isnan(humidity)) {
tft.println("Sensor error");
} else {
tft.print(humidity, 0);
tft.println(" %");
}
tft.setCursor(4, 60);
tft.print("Current: ");
tft.print(currentAmps, 2);
tft.println(" A");
tft.setCursor(4, 78);
tft.print("Vibrations: ");
tft.println(vibrationDetected ? "Detected" : "No");
tft.drawFastHLine(0, 94, 160, ST77XX_WHITE);
if (warning) {
tft.setTextColor(ST77XX_RED);
tft.setTextSize(2);
tft.setCursor(4, 102);
tft.println("WARNING!");
} else {
tft.setTextColor(ST77XX_GREEN);
tft.setTextSize(2);
tft.setCursor(4, 102);
tft.println("NORMAL");
}
}
void printSerialData() {
Serial.println("\\n===== MACHINE STATUS =====");
Serial.print("Temperature: ");
if (isnan(temperature)) {
Serial.println("DHT11 read error");
} else {
Serial.print(temperature, 1);
Serial.println(" C");
}
Serial.print("Humidity: ");
if (isnan(humidity)) {
Serial.println("DHT11 read error");
} else {
Serial.print(humidity, 1);
Serial.println(" %");
}
Serial.print("Current: ");
Serial.print(currentAmps, 2);
Serial.println(" A");
Serial.print("Vibrations: ");
Serial.println(vibrationDetected ? "Detected" : "No");
Serial.print("Machine status: ");
Serial.println(warning ? "WARNING" : "NORMAL");
Serial.println("==========================");
}
void setup() {
Serial.begin(115200);
pinMode(VIBRATION_PIN, INPUT);
pinMode(GREEN_LED, OUTPUT);
pinMode(RED_LED, OUTPUT);
pinMode(BUZZER_PIN, OUTPUT);
digitalWrite(GREEN_LED, LOW);
digitalWrite(RED_LED, LOW);
digitalWrite(BUZZER_PIN, LOW);
analogReadResolution(12);
analogSetPinAttenuation(CURRENT_PIN, ADC_11db);
dht.begin();
SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);
tft.initR(INITR_GREENTAB);
tft.setRotation(1);
tft.fillScreen(ST77XX_BLACK);
tft.setTextColor(ST77XX_WHITE);
tft.setTextSize(1);
tft.setCursor(4, 30);
tft.println("Machine Monitor");
tft.setCursor(4, 50);
tft.println("Starting...");
calibrateCurrentSensor();
Serial.println("\\nSmart Predictive Maintenance");
Serial.println("System started.");
delay(1000);
}
void loop() {
if (millis() - lastRead < READ_INTERVAL) {
return;
}
lastRead = millis();
temperature = dht.readTemperature();
humidity = dht.readHumidity();
int vibrationState = digitalRead(VIBRATION_PIN);
if (VIBRATION_ACTIVE_HIGH) {
vibrationDetected = (vibrationState == HIGH);
} else {
vibrationDetected = (vibrationState == LOW);
}
currentAmps = readCurrent();
bool temperatureWarning =
!isnan(temperature) && temperature > TEMP_LIMIT;
bool humidityWarning =
!isnan(humidity) && humidity > HUMIDITY_LIMIT;
bool currentWarning = currentAmps > CURRENT_LIMIT;
bool sensorWarning = isnan(temperature) || isnan(humidity);
warning = vibrationDetected || temperatureWarning ||
humidityWarning || currentWarning || sensorWarning;
digitalWrite(GREEN_LED, warning ? LOW : HIGH);
digitalWrite(RED_LED, warning ? HIGH : LOW);
digitalWrite(BUZZER_PIN, warning ? HIGH : LOW);
displayDashboard();
printSerialData();
}
