#include "matrix.h"

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
    8, 8,
    MATRIX_PIN,
    NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
    NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
    NEO_GRB + NEO_KHZ800
);

void initMatrix() {
    matrix.begin();
    matrix.setBrightness(BRIGHTNESS);
    matrix.fillScreen(0);
    matrix.show();
}

void updateMatrix(uint16_t color) {
    // TODO
}