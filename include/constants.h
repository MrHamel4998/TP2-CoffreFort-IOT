#include <Arduino.h>

// Boutons
#define BUTTON_A_PIN 14
#define BUTTON_B_PIN 27
#define BUTTON_DEBOUNCE_TIME 30
#define BUTTON_LONG_PRESS_TIME 3000

// Écran TM1637
#define CLK_PIN 26
#define DIO_PIN 25
#define BRIGHTNESS 20

// Matrice NeoPixel (WS2812B)
#define MATRIX_PIN 12

// Servo moteur
#define SERVO_PIN 13
#define SERVO_DURATION 333
#define SERVO_STOP_ANGLE 90
#define SERVO_OPEN_ANGLE 0
#define SERVO_CLOSE_ANGLE 180