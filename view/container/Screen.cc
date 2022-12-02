#include "Screen.h"


void Screen::draw()
{
    // Update if need
    if (this->need_to_update_char_view)
    {
        this->updateCharView();
        this->need_to_update_char_view = false;
        this->need_to_draw             = true;
    }

    if (this->need_to_draw)
    {
        // Draw the background
        const let from_left = this->draw_info.position_from_left;
        const let from_top  = this->draw_info.position_from_top;
        const let size_vert = this->draw_info.size_vertical;

        size_t line_index = 0;
        for (; line_index < size_vert; line_index++)
        {
            moveCursorTo(from_left, from_top + line_index);
            printf("%s\r\n", this->draw_info.char_view[line_index].c_str());
        }
        flushOutputToConsole();

        // Until next change, like changing background, or some refresh
        this->need_to_draw = false;
    }

    // Let each window draw itself
    for (Window* window : *this->window_binded)
    {
        window->draw();
    }
}


void Screen::updateCharView()
{
    this->updateConsoleRelatedInfo();

    const let line_to_fill = string(this->draw_info.size_horizontal, this->background_char);

    for (size_t line_index = 0; line_index < this->draw_info.size_vertical; line_index++)
    {
        this->draw_info.char_view[line_index] = line_to_fill;
    }
}


void Screen::updateConsoleRelatedInfo()
{
    const let height = terminal_namesp::current_console_status.height;
    const let width  = terminal_namesp::current_console_status.width;

    if (height != this->draw_info.size_vertical or width != this->draw_info.size_horizontal)
    {
        this->draw_info.size_vertical   = height;
        this->draw_info.size_horizontal = width;
        this->draw_info.char_view.reserve(height);
    }
}


Screen& Screen::pushInWindow(Window* w)
{
    this->window_binded->push_back(w);
    w->addSubscriber(this);
    return *this;
}


Screen& Screen::popOutWindow(Window* w)
{
    const let index = indexOfFirst(*this->window_binded, w);
    if (index >= 0)
    {
        this->window_binded->at(index)->removeSubscriber(this);
        std::swap(this->window_binded->at(index), this->window_binded->at(len(*this->window_binded) - 1));
        this->window_binded->pop_back();
    }
    else
    {
        // TODO: Throw an error
    }
    return *this;
}


Screen& Screen::setBackgroundChar(uchar c)
{
    this->background_char          = c;
    this->need_to_update_char_view = true;
    this->notifySubsriber({ { "redraw", "true" } });
    return *this;
}


void Screen::notifySubsriber(const NotificationDict& info)
{
    forEach(*this->subscribers, (function<void(Subscriber*)>)(lambda_ref(Subscriber * s) { s->updateFromNotification(info); }));
}


/* virtual */ void Screen::updateFromNotification(const NotificationDict& info)
{
    if (info.contains("window_close"))
    {
        const let& win_to_close_id = info.at("window_close");
        indexOfFirst(
            *this->window_binded,
            (std::function<bool(Window*)>)
                lambda_ref(Window * w_pointer) { return w_pointer->getId() == win_to_close_id; }
        );
    }
}


Screen::constructor()
{
    this->window_binded            = new vector<Window*>();
    this->need_to_update_char_view = true;
    // This will be updated
    this->draw_info.size_horizontal = terminal_namesp::current_console_status.width;
    this->draw_info.size_vertical   = terminal_namesp::current_console_status.height;
    this->draw_info.char_view       = vector<string>();
    this->draw_info.char_view.reserve(this->draw_info.size_vertical);
}