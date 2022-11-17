#include "terminal.h"


void moveCursorTo(int from_left, int from_top)
{
    char buffer[20];
    buffer[0]    = '\033';
    buffer[1]    = '[';
    size_t index = 2;

    // Manually converting to raise speed
    // Index value need to plus one to fit ANSI escape sequence
    snprintf(&buffer[index], 20, "%d", ++from_top);
    for (; buffer[index] != '\000'; index++) { }
    buffer[index++] = ';';
    snprintf(&buffer[index], 20, "%d", ++from_left);
    buffer[++index] = 'H';

    printf("%s", buffer);
}


void moveCursorTo(CursorPosition pos)
{
    return moveCursorTo(pos.position_from_left, pos.position_from_top);
}


CursorPosition getCursorPosition()
{
    int from_left, from_top;
    sscanf(
        getANSIResponse("\033[6n", /* stop when read */ 'R').c_str(),
        "\033[%d;%dR",
        &from_top, &from_left
    );
    // Because they start with 1
    return { /* position_from_left: */ --from_left, /* position_from_top: */ --from_top };
}


void resetTerminalToDefault()
{
    printf("%s", "\033c");
}


void clearTerminal()
{
    printf("%s", "\033[3J");
}