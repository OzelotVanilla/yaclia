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
        const let from_left = this->draw_info.position_from_left;
        const let from_top  = this->draw_info.position_from_top;

        isize i = 0;
        for (; i < len(this->draw_info.char_view); i++)
        {
            moveCursorTo(from_left, from_top + i);
            printf("%s\r\n", this->draw_info.char_view[i].c_str());
        }
        flushOutputToConsole();
    }

    // Draw all fields
    this->field_container.draw();
    this->need_to_draw = false;
}



Window& Window::setTitle(string title)
{
    this->window_style.has_title = true;
    this->title                  = title;
    return *this;
}


/* virtual */ void Window::updateConsoleRelatedInfo()
{
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
        let has_shadow = this->window_style.has_focus_frame_shadow;

        // Draw title line
        char_view[line_index++] = this->drawTitleLine();

        // Draw the main body
        const let line_to_fill =
            this->window_style.vertical_line_char
            + string(width - 2, ' ')
            + this->window_style.vertical_line_char
            + (has_shadow ? "█" : "");

        for (; line_index < height - 1; line_index++)
        {
            char_view[line_index] = line_to_fill;
        }

        // Draw bottom line
        char_view[line_index++] = this->drawBottomLine();

        // Draw shadow if there
        if (has_shadow)
        {
            char_view[line_index] = " " + repeatStr("▀", width);
        }
    }

    // Draw the layout inside ? Why here.
    this->field_container.updateCharView();

    this->need_to_draw = true;
}


Window& Window::moveTo(int from_left, int from_top)
{
    this->draw_info.position_from_left = from_left;
    this->draw_info.position_from_top  = from_top;
    this->field_container.moveTo(from_left + 1, from_top + 1);
    return *this;
}

/* virtual */ NotificationDict Window::handleInput(const ProcessedKeyInput& key_input)
{
    // If it is for this window.

    // Else give active field.
    return this->field_container.handleInput(key_input);
}


Window& Window::addField(Field* f)
{
    this->field_container.addField(f);
    return *this;
}


/* virtual */ void Window::updateFromNotification(const NotificationDict& info)
{
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
     *    width_left_to_title             │               │
     *    (why it is called               │               │
     *     left_to_title ?            title               │
     *     Because there might                            │
     *     be no status_icon)            width_title_to_end
     *
     * The status icon or title might not exist.
     *
     * The status icon must be 3 char width, while the title has minimum 3 char width.
     *
     * The
     */

    // Only if user defined it has a brief icon, and it also can contain a brief icon (width is enough to show).
    const bool need_draw_status_icon =
        this->window_style.has_status_icon and width >= 7;

    // Same as status_icon.
    const bool need_draw_title =
        this->window_style.has_title and (need_draw_status_icon ? width >= 11 : width >= 7);

    // If there is only 1 char for title, it is '…'
    const isize width_for_max_title_text =
        need_draw_title
            ? width - (need_draw_status_icon ? 10 : 6)
            : 0;
    const bool title_text_too_long  = len(this->title) > width_for_max_title_text;
    const int  width_for_title_text = title_text_too_long ? width_for_max_title_text : len(this->title);
    const let  title_text =
        need_draw_title
             ? title_text_too_long
                   ? (this->title.substr(0, width_for_title_text - 1) + "…")
                   : this->title
             : "";
    const isize width_for_title =
        need_draw_title
            ? width_for_title_text + 2
            : 0;

    // Until now, the width of window title (include left and right bracket) is ensured
    // With upper-left and upper-right corner

    //┌─[ ]──────[Too long string]───────────┐
    //┌─[ ]───────[Too long string]──────────┐

    // Calculate how many hbar remained
    const let width_hbar_remain =
        width
        - 4                               // For upper-left and upper-right corner.
        - (need_draw_status_icon ? 3 : 0) // If there is status icon.
        - width_for_title;                // For the width of window title (include left and right bracket), maybe no title.

    // Calculate width_left_to_title. Notice the whole title should be in the middle as possible.
    int width_left_to_title = 0;
    int width_title_to_end  = 0;
    if (width_hbar_remain > 0)
    {
        if (need_draw_status_icon) // Left width of h_bar is equivalent to
        {
            // To make title-left looks equal to title-right,
            // (width_left_to_title + 3) == width_title_to_end == (width_hbar_remain + 3) / 2
            width_left_to_title = (width_hbar_remain + 3) / 2 - 3;
            if (width_left_to_title <= 0) { width_left_to_title = 1; }
            // width_left_to_title = 1;
            width_title_to_end = width_hbar_remain - (width_left_to_title);
        }
        else
        {
            // width_left_to_title == width_title_to_end == (width_hbar_remain / 2)
            // If odd, width_left_to_title + 1 == width_title_to_end
            width_left_to_title = width_hbar_remain / 2;
            width_title_to_end  = width_hbar_remain - width_left_to_title;
        }
    }

    // Calculate right side

    std::stringstream result;

    result << this->window_style.upper_left_char << h_bar;
    if (need_draw_status_icon) { result << '[' << this->status_icon << ']'; }
    result << repeatStr(h_bar, width_left_to_title);
    if (need_draw_title) { result << '[' << title_text << ']'; };
    result << repeatStr(h_bar, width_title_to_end) << h_bar << this->window_style.upper_right_char;

    return result.str();
}


string Window::drawBottomLine() const
{
    return this->window_style.lower_left_char
           + repeatStr(this->window_style.horizontal_line_char, this->draw_info.size_horizontal - 2)
           + this->window_style.lower_right_char
           + (this->window_style.has_focus_frame_shadow ? "█" : "");
}


Window::constructor()
{
    delegate(40, 15, 1, 1);
}


Window Window::createSized(int width, int height)
{
    let w = constructor(width, height, 1, 1);
    return std::move(w);
}


Window::constructor(int width, int height, int top_offset, int left_offset)
{
    this->draw_info.size_horizontal    = width;
    this->draw_info.size_vertical      = height;
    this->draw_info.position_from_top  = top_offset;
    this->draw_info.position_from_left = left_offset;

    const let char_view_length = this->window_style.has_focus_frame_shadow ? height + 1 : height;
    this->draw_info.char_view  = vector<string>(char_view_length);
    this->field_container      = FieldContainer::createSized(width - 2, height - 2);
    this->field_container.moveTo(left_offset + 1, top_offset + 1);
}