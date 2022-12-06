#include "terminal.h"


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


void moveCursorTo(int from_left, int from_top)
{
    char buffer[20];
    buffer[0]   = '\033';
    buffer[1]   = '[';
    isize index = 2;

    // Manually converting to raise speed
    // Index value need to plus one to fit ANSI escape sequence
    sprintf(&buffer[index], "%d", ++from_top);
    for (; buffer[index] != '\0'; index++) { }
    buffer[index++] = ';';
    sprintf(&buffer[index], "%d", ++from_left);
    for (; buffer[index] != '\0'; index++) { }
    buffer[index++] = 'H';
    // buffer[index]   = '\0';

    writeStdout(buffer, index);
}


ConsoleStatus terminal_namesp::updateConsoleStatusInfo()
{
    sys_call_namesp::winsize current_console_size;
    sys_call_namesp::ioctl(stdio::stdout_fd, TIOCGWINSZ, &current_console_size);
    ConsoleStatus latest;
    latest.height = current_console_size.ws_row;
    latest.width  = current_console_size.ws_col;

    return terminal_namesp::current_console_status = latest;
}