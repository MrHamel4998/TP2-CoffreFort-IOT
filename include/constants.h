#include <Arduino.h>

// Boutons
#define BUTTON_A_PIN 32
#define BUTTON_B_PIN 33

// Écran TM1637
#include <TM1637Display.h>
#define CLK_PIN 27
#define DIO_PIN 26
#define BRIGHTNESS 20

// Matrice NeoPixel (WS2812B)
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#define LED_PIN 25

// Servo moteur
#include <ESP32Servo.h>
#define SERVO_PIN 13

// Wifi & Firebase
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h" 
#include <secrets.h>