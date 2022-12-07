#include "TextField.h"

TextField::constructor(isize height, isize width)
{
    this->text_height       = height;
    this->text_width        = width;
    this->lines             = new string[height];
    for (isize i = 0; i < height; i++)
    {
        this->lines[i] = string(width, '\0');
    }
    this->cursor_position_x = 0;
    this->cursor_position_y = 0;
    for (isize i = 0; i < height; i++)
    {
        this->draw_info.char_view.push_back("");
    }
}

/* virtual */ void TextField::draw()
{
    if (this->need_to_update_char_view)
    {
        this->updateCharView();
        this->need_to_draw = true;
    }

    if (this->need_to_draw)
    {
        const let from_left = this->draw_info.position_from_left;
        const let from_top  = this->draw_info.position_from_top;

        for (isize i = 0; i < len(this->draw_info.char_view); i++)
        {
            moveCursorTo(from_left, from_top + i);
            printf("%s\r\n", this->draw_info.char_view[i].c_str());
        }
        flushOutputToConsole();

        this->need_to_draw = false;
    }
}



/* virtual */ void TextField::updateCharView()
{
    for (isize i = 0; i < this->text_height; i++)
    {
        this->draw_info.char_view[i] = this->lines[i];
    }

    this->need_to_update_char_view = false;
}


/* virtual */ NotificationDict TextField::handleInput(const ProcessedKeyInput& key_input)
{
    if ((key_input.modifier == key_input_namesp::KbdModifier::none) && (32 <= int(key_input.key)) && (int(key_input.key) <= 126))
    {
        char last_bit;
        for (int x = this->cursor_position_x, y = this->cursor_position_y; (x < this->text_width) && (this->lines[y][x] != '\0');)
        {
            char bit = this->lines[y][x];
            x        = (x + 1);
            if((x < this->text_width) && (this->lines[y][x] != '\0'))
            {last_bit = this->lines[y][x];}
            this->lines[y][x] = bit;
        }
        this->lines[cursor_position_y][cursor_position_x] = char(key_input.key);
    } else {
        if(key_input.key == key_input_namesp::KbdChar::enter) {
            for(int y = this->text_height - 1; y > this->cursor_position_y + 1; y--) {
                this->lines[y] = this->lines[y - 1];
            }
            char* c_string_next_line = new char[text_width - this->cursor_position_x];
            this->lines[this->cursor_position_y].copy(c_string_next_line, text_width - this->cursor_position_x, this->cursor_position_x);
            string next_line;
            this->lines[this->cursor_position_y + 1];
        }
    }

    return {};
}