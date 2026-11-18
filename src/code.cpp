#include "code.h"
#include "buttons.h"
#include "display.h"
#include "constants.h"
#include "states.h"

int enteredCode[4] = {0, 0, 0, 0};
int confirmationCode[4] = {0, 0, 0, 0};

int currentDigit = 0;
int confirmationDigit = 0;

bool codeInputComplete = false;

void handleCodeInput(int code[], int &digit)
{
    if (digit >= 4)
        return;

    ButtonPressType A = getButtonPressType(BUTTON_A_PIN, buttonA);
    ButtonPressType B = getButtonPressType(BUTTON_B_PIN, buttonB);

    if (A == BUTTON_SHORT)
    {
        code[digit]++;

        if (code[digit] > 9)
        {
            code[digit] = 0;
        }

        updateDisplay(code, digit);
    }

    if (B == BUTTON_SHORT)
    {
        digit++;
        Serial.print("Digit incremented to: ");
        Serial.println(digit);

        if (digit >= 4)
        {
            codeInputComplete = true;
        }
        else
        {
            updateDisplay(code, digit);
        }
    }
}

void resetCode()
{
    currentDigit = 0;
    codeInputComplete = false;

    for (int i = 0; i < 4; i++)
    {
        enteredCode[i] = 0;
    }

    updateDisplay(enteredCode, currentDigit);
}

void handleCodeEntry()
{
    if (!codeInputComplete)
    {
        handleCodeInput(enteredCode, currentDigit);
    }
}

void resetCodeConfirmation()
{
    confirmationDigit = 0;
    codeInputComplete = false;

    for (int i = 0; i < 4; i++)
    {
        confirmationCode[i] = 0;
    }

    updateDisplay(confirmationCode, confirmationDigit);
}

void handleCodeConfirmation()
{
    if (!codeInputComplete)
    {
        handleCodeInput(confirmationCode, confirmationDigit);
    }

    if (checkCode())
    {
        startMatrixBlink(0, 255, 0, 3);
    }
    else
    {
        startMatrixBlink(255, 0, 0, 3);
    }
}

bool checkCode()
{
    for (int i = 0; i < 4; i++)
    {
        if (enteredCode[i] != confirmationCode[i])
        {
            return false;
        }
    }

    return true;
}