#include "constants.h"
#include "addons/TokenHelper.h"
#include "buttons.h"
#include "display.h"
#include "matrix.h"
#include "servo.h"
#include "states.h"
#include "services.h"

// Variables
bool isLocked = false;
int userCode[4] = {};

void setup() {
    Serial.begin(9600);

    // TM1637
    initDisplay();
    Serial.println("Écran TM1637 initialisé.");

    // NeoMatrix
    initMatrix();
    Serial.println("Matrice NeoPixel initialisée.");

    // Servo moteur
    initServo();
    Serial.println("Servo moteur initialisé.");

    // Boutons
    initButtons();
    Serial.println("Boutons initialisés.");

    // Services
    initWiFi();
    initFirebase();
    Serial.println("Services WiFi et Firebase initialisés.");
}

void loop() {

}