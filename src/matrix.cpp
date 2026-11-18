#include "matrix.h"

bool blinking = false;
bool matrixOn = false;

int blinkCount = 0;
int maxBlinks = 0;

int blinkR, blinkG, blinkB;

unsigned long lastBlinkTime = 0;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
    8, 8,
    MATRIX_PIN,
    NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
        NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
    NEO_GRB + NEO_KHZ800);

void initMatrix()
{
    matrix.begin();
    matrix.setBrightness(BRIGHTNESS);
    matrix.fillScreen(0);
    matrix.show();
}

void setMatrixColor(int r, int g, int b)
{
    uint16_t color = matrix.Color(r, g, b);
    matrix.fillScreen(color);
    matrix.show();
}

void startMatrixBlink(int r, int g, int b, int times)
{
    blinkR = r;
    blinkG = g;
    blinkB = b;

    maxBlinks = times;
    blinkCount = 0;

    matrixOn = false;
    blinking = true;
    lastBlinkTime = millis();
}

void updateMatrix()
{
    if (!blinking) return;

    if (millis() - lastBlinkTime >= 300)
    {
        lastBlinkTime = millis();
        matrixOn = !matrixOn;

        if (matrixOn) {
            setMatrixColor(blinkR, blinkG, blinkB);
        }
        else {
            setMatrixColor(0, 0, 0);
            blinkCount++;

            if (blinkCount >= maxBlinks) {
                blinking = false;
            }
        }
    }
}