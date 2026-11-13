#include "constants.h"

ButtonPressType getButtonPressType() {
    static unsigned long buttonPressStartTime = 0;
    static bool buttonPressed = false;
    static bool longPressDetected = false;

    if (digitalRead(BUTTON_PIN) == LOW) {
        if (!buttonPressed) {
            buttonPressed = true;
            buttonPressStartTime = millis();
            longPressDetected = false;
        }

        if (!longPressDetected &&
            millis() - buttonPressStartTime >= BUTTON_LONG_PRESS_TIME) {

            longPressDetected = true;
            return BUTTON_LONG;
        }

    } else {
        if (buttonPressed) {
            buttonPressed = false;

            if (!longPressDetected &&
                millis() - buttonPressStartTime >= BUTTON_DEBOUNCE_TIME) {
                return BUTTON_SHORT;
            }
        }
    }

    return BUTTON_NONE;
}