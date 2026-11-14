#include "constants.h"

/*
 * Aide de ChatGPT pour adapter la fonction getButtonPressType,
 * afin de gérer les appuis courts et longs des deux boutons.
 */
ButtonState buttonA;
ButtonState buttonB;

ButtonPressType getButtonPressType(int pin, ButtonState &button)
{
    if (digitalRead(pin) == LOW)
    {
        if (!button.pressed)
        {
            button.pressed = true;
            button.pressStart = millis();
            button.longDetected = false;
        }

        if (!button.longDetected &&
            millis() - button.pressStart >= BUTTON_LONG_PRESS_TIME)
        {
            button.longDetected = true;
            return BUTTON_LONG;
        }
    }
    else if (button.pressed)
    {
        button.pressed = false;

        if (!button.longDetected &&
            millis() - button.pressStart >= BUTTON_DEBOUNCE_TIME)
        {
            return BUTTON_SHORT;
        }
    }

    return BUTTON_NONE;
}