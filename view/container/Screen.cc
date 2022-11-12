#include "Screen.h"

void Screen::draw()
{
    // Let each window draw itself
    for (Window* window : *this->window_binded)
    {
        this->draw();
    }
}

void Screen::updateConsoleRelatedInfo()
{
}

Screen& Screen::pushInWindow(Window* w)
{
    this->window_binded->push_back(w);
    return *this;
}

Screen& Screen::popOutWindow()
{
    this->window_binded->pop_back();
    return *this;
}

Screen& Screen::addWindow(Window* w)
{
    return this->pushInWindow(w);
}

Screen& Screen::deleteWindow()
{
    return this->popOutWindow();
}

Screen::constructor()
{
    delegate(ConsoleConfig());
}

Screen::constructor(ConsoleConfig c)
{
    this->console_config = &c;
    this->window_binded  = new vector<Window*>();
}