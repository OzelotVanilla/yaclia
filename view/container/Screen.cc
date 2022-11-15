#include "Screen.h"


void Screen::draw()
{
    // Draw the background
    {
        moveCursorTo(this->draw_info.position_from_left, this->draw_info.position_from_top);
        let line_to_fill = string(this->draw_info.size_horizontal, this->background_char);

        for (size_t line_index = 0; line_index < this->draw_info.size_vertical; line_index++)
        {
            cout << line_to_fill;
        }
    }


    // Let each window draw itself
    for (Window* window : *this->window_binded)
    {
        window->draw();
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

Screen& Screen::setBackgroundChar(uchar c)
{
    this->background_char = c;
    return *this;
}

Screen::constructor()
{
    delegate(ConsoleConfig());
}

Screen::constructor(ConsoleConfig c)
{
    this->console_config            = &c;
    this->window_binded             = new vector<Window*>();
    this->draw_info.size_horizontal = c.getWidth();
    this->draw_info.size_vertical   = c.getHeight();
}