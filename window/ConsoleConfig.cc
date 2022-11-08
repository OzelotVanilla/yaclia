#include "ConsoleConfig.h"

int ConsoleConfig::getConsoleHeight()
{
    return parseInt(getShellOutput("tput lines"));
}

int ConsoleConfig::getConsoleWidth()
{
    return parseInt(getShellOutput("tput cols"));
}

ConsoleConfig::constructor()
{
    this->console_height = ConsoleConfig::getConsoleHeight();
    this->console_width  = ConsoleConfig::getConsoleWidth();
}
