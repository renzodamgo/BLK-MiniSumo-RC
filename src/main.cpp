#include <Arduino.h>
#include <TB6612FNG.h>
#include <ps5Controller.h>

#define AIN1_LEFT 2
#define AIN2_LEFT 0
#define PWMA_LEFT 4
#define BIN1_RIGHT 16
#define BIN2_RIGHT 17
#define PWMB_RIGHT 5
#define STANDBY 18
#define DUALSENSE_MAC "D0:BC:C1:05:69:31"
#define STICK_DEADZONE 30

Tb6612fng motors(STANDBY, BIN1_RIGHT, BIN2_RIGHT, PWMB_RIGHT, AIN1_LEFT, AIN2_LEFT, PWMA_LEFT);

bool connected = false;

void setup() {
    Serial.begin(115200);
    motors.begin();
    ps5.begin(DUALSENSE_MAC);
    Serial.println("Ready.");
}

void dance() {
    for (int i = 0; i < 4; i++) {
        motors.drive(0.5, -0.5, 30);  // Turn right
        delay(100);
        motors.drive(-0.5, 0.5, 30);  // Turn left
        delay(100);
        motors.drive(0.5, -0.5, 30);  // Turn right
        delay(100);
        motors.drive(-0.5, 0.5, 30);  // Turn left
        delay(100);
        motors.drive(-0.5, -0.5, 30);  // Turn right
        delay(100);
        motors.drive(0.5, 0.5, 30);  // Turn left
        delay(100);
        motors.drive(-0.5, -0.5, 30);  // Turn right
        delay(100);
        motors.drive(0.5, 0.5, 30);  // Turn left
        delay(100);
    }
}

void loop() {
    while (ps5.isConnected()) {
        if (!connected) {
            connected = true;
            Serial.println("Connected!");
        }
        Serial.println("Connected!");
        float left_pwm = 1.0;                   // 0..1
        float right_pwm = 1.0;                  // 0..1
        float speed_normalized = 0.0;           // -1.00 ..  1.00
        if (ps5.LStickX() < -STICK_DEADZONE) {  // x-Left from -30 to -1pa
            // Serial.printf("LStickX: %d\n", ps5.LStickX());
            left_pwm = float(map(ps5.LStickX(), -140, 0, 0, 100)) / 100.0;
            Serial.printf("left_pwm: %.2f\n", left_pwm);
        }
        if (STICK_DEADZONE < ps5.LStickX()) {  // x-right from 30 to 1
            // Serial.printf("LStickX: %d\n", ps5.LStickX());
            right_pwm = float(map(ps5.LStickX(), 0, 130, 100, 0)) / 100.0;
            Serial.printf("right_pwm: %.2f\n", right_pwm);
        }

        if (ps5.L1()) {
            right_pwm = 0.5;
            left_pwm = -0.5;
            motors.drive(left_pwm, right_pwm, 30);
            Serial.println("R1 button pressed");
        }

        if (ps5.R1()) {
            left_pwm = 0.5;
            right_pwm = -0.5;
            motors.drive(left_pwm, right_pwm, 30);
            Serial.println("R1 button pressed");
        }

        if (ps5.R3()) {
            dance();
        }

        if (ps5.R2() || ps5.L2()) {  // 0..255 Acelerar
            float accelerate_normalized =
                float(map(ps5.R2Value(), 0, 255, 0, 100)) / 100.0;
            float retro_normalized =
                float(map(ps5.L2Value(), 0, 255, 0, 100)) / 100.0;
            speed_normalized = accelerate_normalized - retro_normalized;
            // Serial.printf("speed_normalized: %.2f\n", speed_normalized);
            // Serial.printf("R2 button at %d\n", ps5.R2Value());
            motors.drive(left_pwm * speed_normalized, right_pwm * speed_normalized, 20);
            Serial.printf("left_pwm: %.2f\n", left_pwm * speed_normalized);
            Serial.printf("right_pwm: %.2f\n", right_pwm * speed_normalized);
        }
        delay(10);
    }
}