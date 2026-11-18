#pragma once
#include "constants.h"
#include <TM1637Display.h>

void initDisplay();
void displayClear();
void updateDisplayCode(int code[], int currentDigit);