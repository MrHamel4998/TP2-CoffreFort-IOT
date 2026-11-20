#include "states.h"
#include "buttons.h"
#include "display.h"
#include "matrix.h"
#include "servo.h"
#include "services.h"
#include "code.h"

State currentState = NON_PROGRAMME;
bool stateChanged = true;
bool waitingForMatrix = false;
State stateAfterMatrix = NON_PROGRAMME;

void enterState(State state)
{
    switch (state)
    {
    case NON_PROGRAMME:
        Serial.println("État: NON_PROGRAMME");
        matrixSetMode(MATRIX_MODE_GREEN);
        displayClear();
        break;
    case PROG_SAISIE:
        Serial.println("État: PROG_SAISIE");
        matrixSetMode(MATRIX_MODE_ORANGE_BLINK);
        beginCodeEntry(true);
        break;
    case PROG_CONFIRMATION:
        Serial.println("État: PROG_CONFIRMATION");
        matrixSetMode(MATRIX_MODE_ORANGE_BLINK);
        beginCodeEntry(false);
        break;
    case OUVERT:
        Serial.println("État: OUVERT");
        matrixSetMode(MATRIX_MODE_GREEN);
        displayClear();
        break;
    case FERME:
        Serial.println("État: FERME");
        matrixSetMode(MATRIX_MODE_RED);
        displayClear();
        beginCodeEntry(false);
        break;
    }
}

void changeState(State newState)
{
    State previousState = currentState;

    currentState = newState;
    stateChanged = true;

    if (previousState == FERME && newState == OUVERT)
    {
        openServo();
    }
    else if (previousState == OUVERT && newState == FERME)
    {
        closeServo();
    }
}

void updateState()
{
    if (stateChanged)
    {
        enterState(currentState);
        stateChanged = false;
    }

    if (waitingForMatrix)
    {
        if (matrixAnimationComplete())
        {
            waitingForMatrix = false;
            changeState(stateAfterMatrix);
        }
        return;
    }

    switch (currentState)
    {
    case NON_PROGRAMME:
        if (getButtonPressType(BUTTON_B_PIN, buttonB) == BUTTON_LONG)
        {
            changeState(PROG_SAISIE);
        }
        break;

    case PROG_SAISIE:
    {
        const CodeEntryResult result = updateCodeEntry();
        if (result == CODE_COMPLETE)
        {
            changeState(PROG_CONFIRMATION);
        }
        break;
    }

    case PROG_CONFIRMATION:
    {
        const CodeEntryResult result = updateCodeEntry();
        if (result == CODE_MATCH || result == CODE_MISMATCH)
        {
            if (result == CODE_MATCH)
            {
                matrixSuccess();
                stateAfterMatrix = OUVERT;
            }
            else
            {
                matrixError();
                stateAfterMatrix = PROG_SAISIE;
            }

            waitingForMatrix = true;
        }
        break;
    }

    case OUVERT:
        if (getButtonPressType(BUTTON_A_PIN, buttonA) == BUTTON_SHORT)
        {
            changeState(FERME);
        }
        if (getButtonPressType(BUTTON_B_PIN, buttonB) == BUTTON_LONG)
        {
            changeState(PROG_SAISIE);
        }
        break;

    case FERME:
    {
        const CodeEntryResult result = updateCodeEntry();

        if (result == CODE_MATCH)
        {
            changeState(OUVERT);
        }
        else if (result == CODE_MISMATCH)
        {
            matrixError();
            stateAfterMatrix = FERME;
            waitingForMatrix = true;
        }
        break;
    }
    }
}