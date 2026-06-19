#include <Wire.h>
#include <SensirionI2cScd4x.h>

SensirionI2cScd4x sensor;

// LED
#define LED_G 25
#define LED_Y 26
#define LED_R 27

// Buzzer
#define BUZZER 14

// Button
#define BTN 13   // 🔥 เปลี่ยนได้ถ้าคุณใช้ขาอื่น

bool mute = false;
bool lastBtn = HIGH;
unsigned long lastPress = 0;

static int16_t error;

void setAlert(uint16_t co2) {

  digitalWrite(LED_G, LOW);
  digitalWrite(LED_Y, LOW);
  digitalWrite(LED_R, LOW);

  Serial.print("CO2 = ");
  Serial.print(co2);
  Serial.print(" | BTN = ");
  Serial.println(digitalRead(BTN));   // 🔥 ดูสถานะปุ่มจริง

  // 🟢
  if (co2 < 1000) {
    digitalWrite(LED_G, HIGH);
    mute = false;
  }

  // 🟡
  else if (co2 < 2000) {
    digitalWrite(LED_Y, HIGH);
    mute = false;
  }

  // 🔴
  else {
    digitalWrite(LED_R, HIGH);

    if (!mute) {
      digitalWrite(BUZZER, HIGH);
    } else {
      digitalWrite(BUZZER, LOW);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  Wire.begin(21, 22);

  pinMode(LED_G, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_R, OUTPUT);

  pinMode(BUZZER, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);

  digitalWrite(BUZZER, LOW);

  sensor.begin(Wire, SCD41_I2C_ADDR_62);
  delay(10000);

  sensor.startPeriodicMeasurement();

  Serial.println("System ready");
}

void loop() {
  delay(3000);

  // 🔥 อ่านปุ่มแบบกันเด้ง
  bool btnState = digitalRead(BTN);

  if (btnState == LOW && lastBtn == HIGH && millis() - lastPress > 300) {
    mute = true;
    digitalWrite(BUZZER, LOW);
    Serial.println("🔇 MUTE ON");
    lastPress = millis();
  }

  lastBtn = btnState;

  bool ready = false;
  sensor.getDataReadyStatus(ready);

  if (!ready) return;

  uint16_t co2;
  float t, h;

  error = sensor.readMeasurement(co2, t, h);

  if (error == 0) {
    setAlert(co2);
  }
}
