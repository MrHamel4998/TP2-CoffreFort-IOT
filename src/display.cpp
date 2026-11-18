#include "display.h"
#include "constants.h"

TM1637Display display(CLK_PIN, DIO_PIN);

void initDisplay()
{
    display.setBrightness(BRIGHTNESS);
    display.clear();
}

void displayClear()
{
    display.clear();
}

void updateDisplayCode(int code[], int currentDigit)
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
