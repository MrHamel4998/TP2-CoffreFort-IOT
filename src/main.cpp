#include "constants.h"

// Écran TM1637
TM1637Display display(CLK_PIN, DIO_PIN);

// Matrice NeoPixel
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
    8, 8,
    MATRIX_PIN,
    NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
    NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
    NEO_GRB + NEO_KHZ800
);

// Servo moteur
Servo servo;

void setup() {
  Serial.begin(9600);

  // TM1637
  display.setBrightness(7);
  display.clear();
  Serial.println("Écran TM1637 initialisé.");

  // NeoMatrix
  matrix.begin();
  matrix.setBrightness(BRIGHTNESS);
  matrix.fillScreen(0);
  matrix.show();
  Serial.println("Matrice NeoPixel initialisée.");

  // Servo moteur
  servo.attach(SERVO_PIN);
  servo.write(SERVO_STOP_ANGLE);
  Serial.println("Servo moteur initialisé.");

  // Boutons
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  pinMode(BUTTON_B_PIN, INPUT_PULLUP);
  Serial.println("Boutons initialisés.");
}

void loop() {

}