#include "VerticalScrollSelectField.h"


/* virtual */ void VerticalScrollSelectField::draw()
{
}


/* virtual */ void VerticalScrollSelectField::updateCharView()
{
    if (len(this->items) > 0)
    {
    }
    else
    {
        this->draw_info.char_view.push_back(
            "\e[38;2;236;109;113m\e[3m"
            "<no item to select>"
            "\e[0m"
        );
    }
}


/* virtual */ void VerticalScrollSelectField::updateFromNotification(const NotificationDict& info)
{
}


/* virtual */ void VerticalScrollSelectField::handleInput(const ProcessedKeyInput& key_input)
{
}


/* static */ VerticalScrollSelectField VerticalScrollSelectField::createSized(isize line_to_show)
{
    return VerticalScrollSelectField::createSized(line_to_show, {});
}


/* static */ VerticalScrollSelectField VerticalScrollSelectField::createSized(isize line_to_show, const vector<string> init_items)
{
    let field = VerticalScrollSelectField(init_items);

    field.draw_info.size_vertical = line_to_show;
    field.draw_info.char_view     = vector<string>(line_to_show, "");

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