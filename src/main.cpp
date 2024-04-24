#include <Arduino.h>
#include <TB6612FNG.h>
#include <ps5Controller.h>

#define AIN1 2
#define AIN2 0
#define PWMA 4

Tb6612fng motor(27, AIN1, AIN2, PWMA);

void setup() {
  Serial.begin(115200);
  motor.begin();
  Serial.print("hello");
}

void loop() {
  Serial.printf("Loop: %d\n", millis());
  // 500ms forwards
  motor.drive(0.5, 500);
  // 500ms backwards
  motor.drive(-0.5, 500);
  // Full range of motor speed
  for (auto i = 1; i <= 10; i += 1) {
    motor.drive(0.1 * i, 200, false);
  }
  motor.brake();
  delay(1000);
}