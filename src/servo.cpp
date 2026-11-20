#include "servo.h"

Servo servo;
bool servoMoving = false;
unsigned long servoStartTime = 0;

void initServo()
{
    servo.attach(SERVO_PIN);
}

void updateServo()
{
    if (servoMoving && millis() - servoStartTime >= SERVO_DURATION)
    {
        servo.write(SERVO_STOP_ANGLE);
        servoMoving = false;
    }
}

void openServo()
{
    servo.write(SERVO_OPEN_ANGLE);
    servoStartTime = millis();
    servoMoving = true;
}

void closeServo()
{
    servo.write(SERVO_CLOSE_ANGLE);
    servoStartTime = millis();
    servoMoving = true;
}

bool isServoMoving()
{
    return servoMoving;
}
