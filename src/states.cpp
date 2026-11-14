#include "states.h"
#include "buttons.h"
#include "display.h"
#include "matrix.h"
#include "servo.h"
#include "services.h"

State currentState = NON_PROGRAMME;
bool stateChanged = true;

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
    ButtonPressType A = getButtonPressType(BUTTON_A_PIN, buttonA);
    ButtonPressType B = getButtonPressType(BUTTON_B_PIN, buttonB);

    switch (currentState)
    {
    case NON_PROGRAMME:
        if (stateChanged)
        {
            setMatrixColor(0, 255, 0);
            openServo();
            clearDisplay();

            stateChanged = false;
        }
        if (B == BUTTON_LONG)
        {
            changeState(PROG_SAISIE);
        }
        break;

    case PROG_SAISIE:
        // Todo: Logique de l'état PROG_SAISIE
        break;

    case PROG_CONFIRMATION:
        // Todo: Logique de l'état PROG_CONFIRMATION
        break;

    case OUVERT:
        // Todo: Logique de l'état OUVERT
        break;

    case FERME:
        // Todo: Logique de l'état FERME
        break;
    }
}