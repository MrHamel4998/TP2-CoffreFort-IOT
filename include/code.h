#pragma once
#include "constants.h"

enum CodeEntryResult { CODE_IN_PROGRESS, CODE_COMPLETE, CODE_MATCH, CODE_MISMATCH };
enum CodeEntryMode { CODE_INITIAL, CODE_CONFIRMATION, CODE_UNLOCK };

void beginCodeEntry(CodeEntryMode mode);
CodeEntryResult updateCodeEntry();
bool codesMatch();
