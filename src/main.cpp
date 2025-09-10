#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SHTC3.h>
#include <Adafruit_BME680.h>
#include <Adafruit_Sensor.h>
#include <BH1750.h>
#include <SparkFun_SCD4x_Arduino_Library.h>

// === Sensor Objects ===
Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();
Adafruit_BME680 bme;
BH1750 lightMeter;
SCD4x scd40;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("ESP32 IAQ Node - Part 1 Prototype");
  Wire.begin(21, 22); // SDA=21, SCL=22

  // ---- SHTC3 ----
  if (!shtc3.begin()) {
    Serial.println("SHTC3 not found!");
  } else {
    Serial.println("SHTC3 ready.");
  }

  // ---- BME680 ----
  if (!bme.begin()) {
    Serial.println("BME680 not found!");
  } else {
    Serial.println("BME680 ready.");
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320 °C for 150 ms
  }

  // ---- BH1750 ----
  if (!lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("BH1750 not found!");
  } else {
    Serial.println("BH1750 ready.");
  }

  // ---- SCD40 ----
  if (!scd40.begin()) {
    Serial.println("SCD40 not found!");
  } else {
    Serial.println("SCD40 ready.");
    scd40.startPeriodicMeasurement();
  }
}

void loop() {
  // --- SHTC3 ---
  sensors_event_t humidity, temp;
  shtc3.getEvent(&humidity, &temp);
  Serial.print("SHTC3 Temp: "); Serial.print(temp.temperature); Serial.print(" °C, ");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println(" %");

  // --- BME680 ---
  if (bme.performReading()) {
    Serial.print("BME680 Temp: "); Serial.print(bme.temperature); Serial.print(" °C, ");
    Serial.print("Humidity: "); Serial.print(bme.humidity); Serial.print(" %, ");
    Serial.print("Pressure: "); Serial.print(bme.pressure / 100.0); Serial.print(" hPa, ");
    Serial.print("Gas: "); Serial.print(bme.gas_resistance / 1000.0); Serial.println(" KΩ");
  } else {
    Serial.println("BME680 reading failed.");
  }

  // --- BH1750 ---
  float lux = lightMeter.readLightLevel();
  Serial.print("BH1750 Light: "); Serial.print(lux); Serial.println(" lx");

  // --- SCD40 ---
  if (scd40.readMeasurement()) {
    if (scd40.getCO2() > 0) {
      Serial.print("SCD40 CO₂: "); Serial.print(scd40.getCO2()); Serial.print(" ppm, ");
      Serial.print("Temp: "); Serial.print(scd40.getTemperature()); Serial.print(" °C, ");
      Serial.print("Humidity: "); Serial.print(scd40.getHumidity()); Serial.println(" %");
    }
  } else {
    Serial.println("SCD40 measurement not ready.");
  }

  Serial.println("-----------------------------");
  delay(5000); // 5 seconds
}
