#include "constants.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoMatrix matrix;

void initMatrix();
void setMatrixColor(int r, int g, int b);
void startMatrixBlink(int r, int g, int b, int times);
void updateMatrix();