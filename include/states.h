#pragma once
#include "constants.h"

enum State { NON_PROGRAMME, PROG_SAISIE, PROG_CONFIRMATION, OUVERT, FERME };

void enterState(State state);
void changeState(State newState);
void updateState();