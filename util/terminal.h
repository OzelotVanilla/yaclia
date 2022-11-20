#pragma once

#include "../head.h"
#include "../system/sys_call.h"



struct CursorPosition
{
    int position_from_left;
    int position_from_top;
};


void moveCursorTo(int from_left, int from_top);

inline void moveCursorTo(CursorPosition pos);

CursorPosition getCursorPosition();

inline void resetTerminalToDefault();

/**
 * Clean the whole screen.
 */
inline void clearTerminal()
{
    printf("%s", "\033[3J");
}