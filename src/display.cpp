#include "display.h"
#include "constants.h"

TM1637Display display(CLK_PIN, DIO_PIN);

void initDisplay()
{
    display.setBrightness(3);
    display.clear();
}

void updateDisplay(int code[], int currentDigit)
{
    uint8_t segments[4];

    for (int i = 0; i < 4; i++)
    {
        if (i <= currentDigit)
        {
            segments[i] = display.encodeDigit(code[i]);
        }
        else
        {
            segments[i] = SEG_G;
        }
    }

    display.setSegments(segments);
}

void clearDisplay()
{
    display.clear();
}