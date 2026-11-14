#include "code.h"
#include "buttons.h"
#include "display.h"
#include "constants.h"
#include "states.h"

int enteredCode[4] = {0, 0, 0, 0};
int currentDigit = 0;

void resetCode()
{
    currentDigit = 0;

    for (int i = 0; i < 4; i++) {
        enteredCode[i] = 0;
    }

    updateDisplay(enteredCode, currentDigit);
}

void handleCodeInput()
{
    ButtonPressType A = getButtonPressType(BUTTON_A_PIN, buttonA);
    ButtonPressType B = getButtonPressType(BUTTON_B_PIN, buttonB);

    if (A == BUTTON_SHORT)
    {
        enteredCode[currentDigit]++;

        if (enteredCode[currentDigit] > 9) {
            enteredCode[currentDigit] = 0;
        }

        updateDisplay(enteredCode, currentDigit);
    }

    if (B == BUTTON_SHORT)
    {
        currentDigit++;

        if (currentDigit >= 4) {
            changeState(PROG_CONFIRMATION);
            return;
        }

        updateDisplay(enteredCode, currentDigit);
    }
}