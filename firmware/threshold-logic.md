#include <Wire.h>
#include <SensirionI2cScd4x.h>

SensirionI2cScd4x sensor;

#define LED_G 25
#define LED_Y 26
#define LED_R 27

static int16_t error;

void setLED(uint16_t co2) {
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_Y, LOW);
  digitalWrite(LED_R, LOW);

  if (co2 < 1000) {
    digitalWrite(LED_G, HIGH);   // ดี
  }
  else if (co2 < 2000) {
    digitalWrite(LED_Y, HIGH);   // ปานกลาง
  }
  else {
    digitalWrite(LED_R, HIGH);   // แย่
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  // I2C
  Wire.begin(21, 22);

  // LED
  pinMode(LED_G, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_R, OUTPUT);

  digitalWrite(LED_G, LOW);
  digitalWrite(LED_Y, LOW);
  digitalWrite(LED_R, LOW);

  // SCD41
  sensor.begin(Wire, SCD41_I2C_ADDR_62);
  delay(500);

  error = sensor.startPeriodicMeasurement();

  Serial.print("Start error: ");
  Serial.println(error);

  Serial.println("System running...");
}

void loop() {
  delay(5000);

  bool ready = false;
  sensor.getDataReadyStatus(ready);

  Serial.print("Ready: ");
  Serial.println(ready);

  if (!ready) return;

  uint16_t co2;
  float temp, hum;

  error = sensor.readMeasurement(co2, temp, hum);

  if (error == 0) {
    Serial.print("CO2: ");
    Serial.print(co2);
    Serial.print(" ppm | Temp: ");
    Serial.print(temp);
    Serial.print(" C | RH: ");
    Serial.println(hum);

    setLED(co2);
  }
  else {
    Serial.print("Read error: ");
    Serial.println(error);
  }
}
