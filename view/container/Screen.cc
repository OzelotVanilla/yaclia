#include "Screen.h"


void Screen::draw()
{
    // Update if need
    if (this->need_to_update_char_view)
    {
        this->updateCharView();
        this->need_to_update_char_view = false;

        // Draw the background, if the screen itself is changed

        const let from_left = this->draw_info.position_from_left;
        const let from_top  = this->draw_info.position_from_top;
        const let size_vert = this->draw_info.size_vertical;

        for (size_t line_index = 0; line_index < size_vert; line_index++)
        {
            moveCursorTo(from_left, from_top + line_index);
            // printf("%s", this->draw_info.char_view[line_index].c_str());
            printf("%s", this->draw_info.char_view[line_index].c_str());
        }
    }

    // Let each window draw itself
    for (Window* window : *this->window_binded)
    {
        window->draw();
    }
}


void Screen::updateCharView()
{
    const let line_to_fill = string(this->draw_info.size_horizontal, this->background_char);

    for (size_t line_index = 0; line_index < this->draw_info.size_vertical; line_index++)
    {
        this->draw_info.char_view[line_index] = line_to_fill;
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
    this->background_char          = c;
    this->need_to_update_char_view = true;
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
    this->need_to_update_char_view  = true;
    this->draw_info.size_horizontal = c.getWidth();
    this->draw_info.size_vertical   = c.getHeight();
    this->draw_info.char_view       = vector<string>();
    this->draw_info.char_view.reserve(this->draw_info.size_vertical);
}