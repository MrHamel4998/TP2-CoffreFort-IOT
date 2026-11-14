#include "servo.h"

Servo servo;

void initServo() {
    servo.attach(SERVO_PIN);
    servo.write(SERVO_STOP_ANGLE);
}

void openServo() {
    // TODO
}

void closeServo() {
    // TODO
}