#include "constants.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoMatrix matrix;

void initMatrix();
void updateMatrix(uint16_t color);