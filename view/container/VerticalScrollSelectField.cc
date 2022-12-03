#include "VerticalScrollSelectField.h"


/* virtual */ void VerticalScrollSelectField::draw()
{
    this->updateCharView();
    const let from_left = this->draw_info.position_from_left;
    const let from_top  = this->draw_info.position_from_top;

    for (isize i = 0; i < len(this->draw_info.char_view); i++)
    {
        moveCursorTo(from_left, from_top + i);
        printf("%s\r\n", this->draw_info.char_view[i].c_str());
    }
    flushOutputToConsole();
}


/* virtual */ void VerticalScrollSelectField::updateCharView()
{
    const let has_frame          = this->has_frame;
    const let max_width_for_text = this->draw_info.size_horizontal - (has_frame ? 2 : 0);

    if (len(this->items) > 0)
    {
        const let height = this->draw_info.size_vertical;
        const let width  = this->draw_info.size_horizontal;

        // If the window is resized, the current selected element's line index will be bigger than max height
        this->position_selected = std::min(this->num_selected, this->position_selected);

        // Index should not exceed vector's range
        // Calculate first line's "index in vector"
        const let first_line_index = std::max(0_isize, this->num_selected - this->position_selected);
        const let last_line_index =
            std::min(
                isize(this->items.size()),
                isize(this->num_selected + (height - this->position_selected - 1))
            );

        // If draw info char view's size need to increase, push in more empty element
        {
            let num_to_add = height - this->items.size();
            while (num_to_add-- > 0) { this->draw_info.char_view.push_back(""); }
        }

        if (has_frame)
        {
            isize line_index = 0;

            this->draw_info.char_view[line_index] = "┌" + repeatStr("─", width - 2) + "┐";
            for (; line_index < height - 2; line_index++)
            {
                let text = this->items.at(first_line_index + line_index - 1);

                if (len(text) > max_width_for_text) { text = text.substr(0, max_width_for_text - 1) + "…"; }

                this->draw_info.char_view[line_index] = "│" + text + "│";
            }
            this->draw_info.char_view[line_index] = "└" + repeatStr("─", width - 2) + "┘";
        }
        else
        {
            for (isize line_index = 0; line_index < height; line_index++)
            {
                let text = this->items.at(first_line_index + line_index);

                if (len(text) > max_width_for_text) { text = text.substr(0, max_width_for_text - 1) + "…"; }

                this->draw_info.char_view[line_index] = text;
            }
        }
    }
    else // No item
    {
        string text = "<no item to select>";
        if (len(text) > max_width_for_text) { text = text.substr(0, max_width_for_text - 1) + "…"; }

        this->draw_info.char_view.clear();
        this->draw_info.char_view.push_back(
            "\e[38;2;236;109;113m\e[3m" + text + "\e[0m"
        );
    }
}


/* virtual */ void VerticalScrollSelectField::updateFromNotification(const NotificationDict& info)
{
}


/* virtual */ void VerticalScrollSelectField::handleInput(const ProcessedKeyInput& key_input)
{
}


VerticalScrollSelectField& VerticalScrollSelectField::setHasFrame(bool has_frame)
{
    if (has_frame != this->has_frame)
    {
        if (has_frame)
        {
            this->max_item_to_show -= 2;
        }
        else // Set no frame
        {
            this->max_item_to_show += 2;
        }

        this->has_frame = has_frame;
    }

    return *this;
}


/* static */ VerticalScrollSelectField VerticalScrollSelectField::createSized(isize line_to_show)
{
    return VerticalScrollSelectField::createSized(line_to_show, {});
}


/* static */ VerticalScrollSelectField VerticalScrollSelectField::createSized(isize line_to_show, const vector<string> init_items)
{
    let field = VerticalScrollSelectField(init_items);

    field.draw_info.size_vertical = line_to_show + 2;
    field.draw_info.char_view     = vector<string>(line_to_show, "");
    field.max_item_to_show        = line_to_show;

    return std::move(field);
}


VerticalScrollSelectField::constructor()
{
    delegate(vector<string>());
}


VerticalScrollSelectField::constructor(const vector<string> init_items)
{
    this->items = init_items;
}