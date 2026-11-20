#include "matrix.h"

const unsigned long BLINK_INTERVAL = 300;
const int RESULT_BLINKS = 3;

Adafruit_NeoMatrix matrix(
    8, 8, MATRIX_PIN,
    NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
    NEO_GRB + NEO_KHZ800);

MatrixColor blinkColor = MATRIX_GREEN;
unsigned long lastBlink = 0;
int completedBlinks = 0;
bool blinking = false;
bool blinkOn = false;
bool repeating = false;

void showColor(MatrixColor color)
{
    int red = 0;
    int green = 0;
    int blue = 0;

    switch (color)
    {
    case MATRIX_RED:
        red = 255;
        break;
    case MATRIX_GREEN:
        green = 255;
        break;
    case MATRIX_ORANGE:
        red = 255;
        green = 165;
        break;
    }

    matrix.fillScreen(matrix.Color(red, green, blue));
    matrix.show();
}

void clearMatrix()
{
    matrix.fillScreen(0);
    matrix.show();
}

void startBlink(MatrixColor color, bool repeat)
{
    blinkColor = color;
    repeating = repeat;
    completedBlinks = 0;
    blinkOn = false;
    blinking = true;
    lastBlink = millis();
}

void initMatrix()
{
    matrix.begin();
    matrix.setBrightness(BRIGHTNESS);
    showColor(MATRIX_GREEN);
}

void matrixSetMode(MatrixMode mode)
{
    blinking = false;
    repeating = false;

    switch (mode)
    {
    case MATRIX_MODE_GREEN:
        showColor(MATRIX_GREEN);
        break;
    case MATRIX_MODE_ORANGE_BLINK:
        startBlink(MATRIX_ORANGE, true);
        break;
    case MATRIX_MODE_RED:
        showColor(MATRIX_RED);
        break;
    }
}

void matrixError()
{
    startBlink(MATRIX_RED, false);
}

void matrixSuccess()
{
    startBlink(MATRIX_GREEN, false);
}

void updateMatrix()
{
    if (!blinking || millis() - lastBlink < BLINK_INTERVAL)
    {
        return;
    }

    lastBlink = millis();
    blinkOn = !blinkOn;
    if (blinkOn)
    {
        showColor(blinkColor);
    }
    else
    {
        clearMatrix();
    }

    if (!blinkOn && !repeating && ++completedBlinks >= RESULT_BLINKS)
    {
        blinking = false;
    }
}

bool matrixAnimationComplete()
{
    return !repeating && !blinking;
}