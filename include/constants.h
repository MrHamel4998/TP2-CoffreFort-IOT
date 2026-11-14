#include <Arduino.h>

// Boutons
#define BUTTON_A_PIN 14
#define BUTTON_B_PIN 27
#define BUTTON_DEBOUNCE_TIME 30
#define BUTTON_LONG_PRESS_TIME 3000

/*
 * Aide de ChatGPT pour adapter la structure ButtonState et la fonction getButtonPressType,
 * afin de gérer les appuis courts et longs des deux boutons.
 */
enum ButtonPressType {
    BUTTON_NONE,
    BUTTON_SHORT,
    BUTTON_LONG
};

struct ButtonState {
    unsigned long pressStart = 0;
    bool pressed = false;
    bool longDetected = false;
};

extern ButtonState buttonA;
extern ButtonState buttonB;

ButtonPressType getButtonPressType(int pin, ButtonState &button);

// Écran TM1637
#include <TM1637Display.h>
#define CLK_PIN 26
#define DIO_PIN 25
#define BRIGHTNESS 20

// Matrice NeoPixel (WS2812B)
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#define MATRIX_PIN 12

// Servo moteur
#include <ESP32Servo.h>
#define SERVO_PIN 13
#define SERVO_STOP_ANGLE 90
#define SERVO_OPEN_ANGLE 0
#define SERVO_CLOSE_ANGLE 180

// Wifi & Firebase
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <secrets.h>