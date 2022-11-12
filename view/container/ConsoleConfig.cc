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
    return parseInt(getShellOutput("tput lines"));
}

int ConsoleConfig::fetchConsoleWidthFromSys()
{
    return parseInt(getShellOutput("tput cols"));
}

ConsoleConfig::constructor()
{
    this->height = ConsoleConfig::fetchConsoleHeightFromSys();
    this->width  = ConsoleConfig::fetchConsoleWidthFromSys();
}
