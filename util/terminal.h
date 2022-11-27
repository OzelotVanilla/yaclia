#pragma once

#include "../head.h"
#include "../system/sys_call.h"
#include "ConsoleStatus.h"


namespace terminal_namesp
{
ConsoleStatus updateConsoleStatusInfo();

static ConsoleStatus current_console_status = updateConsoleStatusInfo();
} // namespace terminal_namesp


struct CursorPosition
{
    int position_from_left;
    int position_from_top;
};


CursorPosition getCursorPosition();



/**
 * @brief Move cursor
 *
 * @param from_left
 * @param from_top
 */
void moveCursorTo(int from_left, int from_top);


inline void moveCursorTo(CursorPosition pos)
{
    return moveCursorTo(pos.position_from_left, pos.position_from_top);
}


inline void resetTerminalToDefault()
{
    printStdout("%s", "\033c");
}


/**
 * Clean the whole screen.
 */
inline void clearConsole()
{
    printStdout("%s", "\033[3J");
}