#pragma once
#include "constants.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

enum MatrixMode
{
    MATRIX_MODE_GREEN,
    MATRIX_MODE_ORANGE_BLINK,
    MATRIX_MODE_RED
};

enum MatrixColor
{
    MATRIX_RED,
    MATRIX_GREEN,
    MATRIX_ORANGE,
};

void initMatrix();
void showColor(MatrixColor color);
void startBlink(MatrixColor color, bool repeat);
void clearMatrix();
void matrixSetMode(MatrixMode mode);
void matrixError();
void matrixSuccess();
void updateMatrix();
bool matrixAnimationComplete();