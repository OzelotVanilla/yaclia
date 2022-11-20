#include "ConsoleConfig.h"


int ConsoleConfig::getHeight()
{
    this->update();
    return this->height;
}

int ConsoleConfig::getWidth()
{
    this->update();
    return this->width;
}

void ConsoleConfig::update()
{
    this->height = fetchConsoleHeightFromSys();
    this->width  = fetchConsoleWidthFromSys();
}

int ConsoleConfig::fetchConsoleHeightFromSys()
{
#ifdef _env_linux
    return parseInt(getShellOutput("tput lines"));
#elif _env_windows
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#endif
}

int ConsoleConfig::fetchConsoleWidthFromSys()
{
#ifdef _env_linux
    return parseInt(getShellOutput("tput cols"));
#elif _env_windows
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
#endif
}

ConsoleConfig::constructor()
{
    this->height = ConsoleConfig::fetchConsoleHeightFromSys();
    this->width  = ConsoleConfig::fetchConsoleWidthFromSys();
}
