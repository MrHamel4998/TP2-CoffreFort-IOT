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
        beginCodeEntry(CODE_INITIAL);
        break;
    case PROG_CONFIRMATION:
        Serial.println("État: PROG_CONFIRMATION");
        matrixSetMode(MATRIX_MODE_ORANGE_BLINK);
        beginCodeEntry(CODE_CONFIRMATION);
        break;
    case OUVERT:
        Serial.println("État: OUVERT");
        // Todo: Logique de l'état OUVERT
        break;
    case FERME:
        Serial.println("État: FERME");
        // Todo: Logique de l'état FERME
        break;
    }
}

void changeState(State newState)
{
    if (currentState != newState)
    {
        currentState = newState;
        stateChanged = true;
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
        // Todo: Logique de l'état OUVERT
        break;

    case FERME:
    {
        // Todo: Logique de l'état FERME
    }
    }
}