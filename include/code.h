#pragma once
#include "constants.h"

enum CodeEntryResult
{
    CODE_IN_PROGRESS,
    CODE_COMPLETE,
    CODE_MATCH,
    CODE_MISMATCH
};

void beginCodeEntry(bool isInitial);
CodeEntryResult updateCodeEntry();
bool codesMatch();
