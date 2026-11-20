#include "constants.h"
#include "buttons.h"
#include "display.h"
#include "matrix.h"
#include "servo.h"
#include "states.h"
#include "services.h"
#include "code.h"

// ChatGPT a corrigé le dépassement : le handshake TLS/ECDSA de Firebase dépassait la stack par défaut de 8 Ko.
size_t getArduinoLoopTaskStackSize(void) {
    return 16384;
}

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
    initTime();
    Serial.println("Services initialisés.");
}

void loop() {
    updateState();
    updateServo();
    updateMatrix();
    updateServices();
}