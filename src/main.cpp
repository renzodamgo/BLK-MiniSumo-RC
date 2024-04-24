#include <Arduino.h>
#include <TB6612FNG.h>
// #include <ps5Controller.h>

#define AIN1_LEFT 2
#define AIN2_LEFT 0
#define PWMA_LEFT 4
#define BIN1_RIGHT 16
#define BIN2_RIGHT 17
#define PWMB_RIGHT 5
#define STANDBY 17
#define DUALSENSE_MAC "D0:BC:C1:05:69:31"
#define STICK_DEADZONE 30

Tb6612fng motor(STANDBY, AIN1_LEFT, AIN2_LEFT, PWMA_LEFT);

void setup() {
  Serial.begin(115200);
  motor.begin();
  // ps5.begin(DUALSENSE_MAC);
  Serial.println("Ready.");
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


  // while (ps5.isConnected() == true) {
  //   float left_pwm = 0.0;  // 0..1
  //   float right_pwm = 0.0; // 0..1
  //   float speed_normalized = 0.0;

  //   if (ps5.LStickX() < -STICK_DEADZONE) { // x-Left from -30 to -130
  //   }

  //   if (STICK_DEADZONE < ps5.LStickX()) { // x-right from 30 to 130
  //   }

  //   // if (ps5.L2()) { // 0..255 Frenar
  //   //   Serial.printf("L2 button at %d\n", ps5.L2Value());
  //   // }
  //   if (ps5.R2()) { // 0..255 Acelerar
  //     speed_normalized = float(map(ps5.R2Value(), 0, 255, 0, 100)) / 100.0;
  //     Serial.printf("speed_normalized: %.2f\n", speed_normalized);
  //     Serial.printf("L2 button at %d\n", ps5.L2Value());
  //     motor.drive(speed_normalized, 100);
  //   }
  // }
}