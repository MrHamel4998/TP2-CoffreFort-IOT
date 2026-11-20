#include "constants.h"

void initButtons();
void updateButtons();

/*
 * Aide de ChatGPT pour adapter la structure ButtonState et la fonction getButtonPressType,
 * afin de gérer les appuis courts et longs des deux boutons. [Voir prompt ci-dessous]
 */
enum ButtonPressType
{
    BUTTON_NONE,
    BUTTON_SHORT,
    BUTTON_LONG
};

struct ButtonState
{
    unsigned long pressStart = 0;
    bool pressed = false;
    bool longDetected = false;
};

extern ButtonState buttonA;
extern ButtonState buttonB;

ButtonPressType getButtonPressType(int pin, ButtonState &button);

/*
 Prompt utilisé pour générer le code ci-dessus :
 | J'ai déjà une fonction getButtonPressType() qui permet de détecter les
 | appuis courts et longs d'un bouton. Je voudrais que tu adaptes mon code
 | existant pour gérer deux boutons indépendants, A et B, chacun ayant son
 | propre état. Conserve autant que possible la structure et la logique de
 | ma version originale : 
 | [Code de la version originale de l'exercice précédent sur les boutons]
*/