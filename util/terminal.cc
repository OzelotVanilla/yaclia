#include "terminal.h"


void moveCursorTo(int from_left, int from_top)
{
    string command = "\033[" + parseString(from_top + 1) + ";" + parseString(from_left + 1) + "H";
    printf("%s", command.c_str());
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
