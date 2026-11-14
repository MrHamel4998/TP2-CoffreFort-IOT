#include "constants.h"

enum State {
    NON_PROGRAMME,
    PROG_SAISIE,
    PROG_CONFIRMATION,
    OUVERT,
    FERME
};

extern State currentState;

void updateState();