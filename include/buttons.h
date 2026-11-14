#include "constants.h"

void initButtons();
void updateButtons();

/*
 * Aide de ChatGPT pour adapter la structure ButtonState et la fonction getButtonPressType,
 * afin de gérer les appuis courts et longs des deux boutons.
 */
enum ButtonPressType {
    BUTTON_NONE,
    BUTTON_SHORT,
    BUTTON_LONG
};

struct ButtonState {
    unsigned long pressStart = 0;
    bool pressed = false;
    bool longDetected = false;
};

extern ButtonState buttonA;
extern ButtonState buttonB;

ButtonPressType getButtonPressType(int pin, ButtonState &button);