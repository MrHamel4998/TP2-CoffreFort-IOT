#include "display.h"
#include "constants.h"

TM1637Display display(CLK_PIN, DIO_PIN);

void initDisplay()
{
    display.setBrightness(3);
    display.clear();
}

void updateDisplay()
{
    // Todo
}