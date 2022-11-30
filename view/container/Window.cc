#include "Window.h"

/* virtual */ void Window::draw()
{
    if (this->need_to_update_char_view)
    {
        this->updateCharView();
        this->need_to_update_char_view = false;
        this->need_to_draw             = true;
    }

    if (this->need_to_draw)
    {
        // TODO: draw

        this->need_to_draw = false;
    }
}


/* virtual */ void Window::updateConsoleRelatedInfo()
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


void Window::updateCharView()
{
    this->updateConsoleRelatedInfo();

    const let width     = this->draw_info.size_horizontal;
    const let height    = this->draw_info.size_vertical;
    let&      char_view = this->draw_info.char_view;

    // Draw the frame, code also from previous Java project.
    {
        let line_index = 0;

        // Draw title line
        char_view[line_index++] = this->drawTitleLine();

        // Draw the main body
        const let line_to_fill =
            this->window_style.vertical_line_char
            + string(width - 2, ' ')
            + this->window_style.vertical_line_char;
        for (; line_index < height; line_index++)
        {
            char_view[line_index] = line_to_fill;
        }

        // Draw bottom line
        char_view[line_index] = this->drawBottomLine();
    }

    // Draw the layout inside
}


string Window::drawTitleLine() const
{
    const let width  = this->draw_info.size_horizontal;
    const let height = this->draw_info.size_vertical;
    const let h_bar  = this->window_style.horizontal_line_char;

    /* The title structure goes like this
     *
     *            ┌─[*]─────────────[Window Title]─────────────────┐
     *               ↑      ↑             ↑               ↑
     *     status_icon      │             │               │
     *                      │             │               │
     *  width_left_to_title               │               │
     *  (why it is called                 │               │
     *   left_to_title ?              title               │
     *   Because there might                              │
     *   be no status_icon)              width_title_to_end
     *
     * The status icon or title might not exist.
     *
     * The status icon must be 3 char width, while the title has minimum 3 char width.
     *
     * The
     */

    // Only if user defined it has a brief icon, and it also can contain a brief icon (width is enough to show).
    const bool need_draw_status_icon =
        this->window_style.has_brief_icon and width >= 7;

    // Same as status_icon.
    const bool need_draw_title =
        this->window_style.has_title and (need_draw_status_icon ? width >= 10 : width >= 7);

    // If there is only 1 char for title, it is '…'
    const int width_for_title = width - (need_draw_status_icon ? 10 : 7) + 1;
    const let title_text      = this->title.substr(0, width_for_title - 1) + "…";

    // Calculate width_left_to_title. Notice the whole title should be in the middle as possible.


    std::stringstream result;

    result << this->window_style.upper_left_char << h_bar;
    if (need_draw_status_icon) { result << '[' << this->status_icon << ']' << h_bar; }
    else { result << string(h_bar, 3); }
    if (need_draw_title) { };

    return result.str();
}


string Window::drawBottomLine() const
{
    return this->window_style.lower_left_char
           + string(this->window_style.horizontal_line_char, this->draw_info.size_horizontal - 2)
           + this->window_style.lower_right_char;
}


Window::constructor()
{
    delegate(40, 20, 1, 1);
}


Window Window::createSized(int width, int height)
{
    return constructor(width, height, 1, 1);
}


Window::constructor(int width, int height, int top_offset, int left_offset)
{
    this->draw_info.position_from_top  = top_offset;
    this->draw_info.position_from_left = left_offset;
    this->draw_info.size_horizontal    = width;
    this->draw_info.size_vertical      = height;
}