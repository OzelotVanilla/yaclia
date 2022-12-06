#include "VerticalScrollSelectField.h"


/* virtual */ void VerticalScrollSelectField::draw()
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

            this->draw_info.char_view[line_index++] = "┌" + repeatStr("─", width - 2) + "┐";
            for (; line_index < height - 2; line_index++)
            {
                // If there is element in the array
                const let pos_in_array = first_line_index + line_index - 1;
                if (pos_in_array < len(this->items))
                {
                    let text = this->items.at(pos_in_array).display_text;

                    let space_remain = max_width_for_text - len(text);

                    if (space_remain < 0) { text = text.substr(0, max_width_for_text - 1) + "…"; }

                    this->draw_info.char_view[line_index] = "│" + text + string(space_remain, ' ') + "│";
                }
                else
                {
                    this->draw_info.char_view[line_index] = "│" + repeatStr(" ", width - 2) + "│";
                }
            }


            this->draw_info.char_view[line_index] = "└" + repeatStr("─", width - 2) + "┘";
        }
        else
        {
            for (isize line_index = 0; line_index < height; line_index++)
            {
                let text = this->items.at(first_line_index + line_index).display_text;

                if (len(text) > max_width_for_text) { text = text.substr(0, max_width_for_text - 1) + "…"; }

                this->draw_info.char_view[line_index] = text;
            }
        }

        // Highlight selected
        {
            let& origin_str =
                (this->draw_info.char_view.at(this->num_selected + (has_frame ? 1 : 0)));
            let text_to_highlight =
                has_frame
                    ? origin_str.substr(3, origin_str.size() - 6) // Notice the vbar is a utf-8, substr index changes.
                    : origin_str;
            origin_str =
                has_frame
                    ? "|\e[38;2;0;148;200m" + text_to_highlight + "\e[0m|"
                    : "\e[48;2;125;125;125m" + text_to_highlight + "\e[0m";
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

    this->need_to_update_char_view = false;
}


/* virtual */ void VerticalScrollSelectField::updateFromNotification(const NotificationDict& info)
{
}


/* virtual */ NotificationDict VerticalScrollSelectField::handleInput(const ProcessedKeyInput& key_input)
{
    // If it is plain control sequence like `arrow_up` or `enter`
    if (key_input.modifier == KbdModifier::none)
    {
        switch (key_input.key)
        {
        case KbdChar::enter:
            return { { "value", this->selectCurrentItem() } };

        case KbdChar::arrow_up:
            this->selectScrollUp();
            return {};

        case KbdChar::arrow_down:
            this->selectScrollDown();
            return {};

        default:
            return { { "unhandled_input", parseString(int(key_input.modifier)) + ":" + parseString(int(key_input.key)) } };
        }
    }

    return {};
}


/* virtual */ VerticalScrollSelectField& VerticalScrollSelectField::addItem(string text)
{
    return this->addItem(text, &text);
}


/* virtual */ VerticalScrollSelectField& VerticalScrollSelectField::addItem(string display_text, string* value_returned)
{
    this->items.push_back(ItemShowing(display_text, value_returned));
    this->need_to_update_char_view = true;
    return *this;
}


/* virtual */ VerticalScrollSelectField& VerticalScrollSelectField::VerticalScrollSelectField::deleteItem(string display_text)
{
    // let checker = lambda_ref(ItemShowing i)
    // {
    //     return i.display_text == display_text;
    // };
    // deleteIfExist(this->items, checker);

    for (isize i = 0; i < len(this->items); i++)
    {
        if (this->items.at(i).display_text == display_text)
        {
            this->items.erase(this->items.begin() + i);
            break;
        }
    }

    this->need_to_update_char_view = true;
    return *this;
}


/* virtual */ VerticalScrollSelectField& VerticalScrollSelectField::selectScrollUp()
{
    if (this->position_selected > 0)
    {
        this->position_selected--;
        this->need_to_update_char_view = true;
    }
    return *this;
}


/* virtual */ VerticalScrollSelectField& VerticalScrollSelectField::selectScrollDown()
{
    if (this->position_selected < this->max_item_to_show - 1)
    {
        this->position_selected++;
        this->need_to_update_char_view = true;
    }
    return *this;
}


/* virtual */ string VerticalScrollSelectField::selectCurrentItem()
{
    return *this->items.at(this->num_selected).value_retuned;
}



// template <typename ItemCallbackFunction>
// VerticalScrollSelectField& VerticalScrollSelectField::addItem(string name, ItemCallbackFunction callback)
// {
//     static_assert(std::is_assignable<function<string(void)>, ItemCallbackFunction>::value, "!");
// }


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

    // field.draw_info.size_vertical = line_to_show + 2;
    field.draw_info.char_view = vector<string>(line_to_show, "");
    field.max_item_to_show    = line_to_show;

    return std::move(field);
}


VerticalScrollSelectField::constructor()
{
    delegate(vector<string>());
}


VerticalScrollSelectField::constructor(const vector<string> init_items)
{
    this->items.reserve(len(init_items));
    for (const string& s : init_items)
    {
        let item = ItemShowing(s, nullptr);

        item.value_retuned = &item.display_text;
        this->items.push_back(item);
    }
}