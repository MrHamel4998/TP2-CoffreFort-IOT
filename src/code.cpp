#include "code.h"
#include "buttons.h"
#include "display.h"
#include "constants.h"
#include "states.h"

const int CODE_LENGTH = 4;

int savedCode[CODE_LENGTH] = {0, 0, 0, 0};
int workingCode[CODE_LENGTH] = {0, 0, 0, 0};
int currentDigit = 0;

CodeEntryMode mode = CODE_INITIAL;
bool complete = false;

bool codesMatch()
{
    for (int i = 0; i < CODE_LENGTH; ++i)
    {
        if (savedCode[i] != workingCode[i])
        {
            return false;
        }
    }
    return true;
}

void beginCodeEntry(CodeEntryMode entryMode)
{
    mode = entryMode;
    currentDigit = 0;
    complete = false;

    for (int i = 0; i < CODE_LENGTH; ++i)
    {
        workingCode[i] = 0;
    }
    updateDisplayCode(workingCode, currentDigit);
}

CodeEntryResult updateCodeEntry()
{
    if (complete)
    {
        return CODE_IN_PROGRESS;
    }

    const ButtonPressType A = getButtonPressType(BUTTON_A_PIN, buttonA);
    const ButtonPressType B = getButtonPressType(BUTTON_B_PIN, buttonB);

    if (A == BUTTON_SHORT)
    {
        workingCode[currentDigit]++;

        if (workingCode[currentDigit] > 9)
        {
            workingCode[currentDigit] = 0;
        }

        updateDisplayCode(workingCode, currentDigit);
    }

    if (B == BUTTON_SHORT)
    {
        ++currentDigit;
        if (currentDigit >= CODE_LENGTH)
        {
            complete = true;
            if (mode == CODE_INITIAL)
            {
                for (int i = 0; i < CODE_LENGTH; ++i)
                {
                    savedCode[i] = workingCode[i];
                }
                return CODE_COMPLETE;
            }
            if (codesMatch())
            {
                return CODE_MATCH;
            }
            else
            {
                return CODE_MISMATCH;
            }
        }
        updateDisplayCode(workingCode, currentDigit);
    }
    return CODE_IN_PROGRESS;
}