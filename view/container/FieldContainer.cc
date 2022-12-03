#include "FieldContainer.h"



/* virtual */ void FieldContainer::draw()
{
    if (this->need_to_update_char_view)
    {
        this->updateCharView();
        this->need_to_draw = true;
    }

    if (this->need_to_draw)
    {
        // TODO: BUG: Now only can draw one element
        // Let each element update their char view
        std::for_each(
            this->fields->begin(), this->fields->end(), lambda(Field * f) { f->updateCharView(); }
        );

        // Draw the fields
        const let from_left = this->draw_info.position_from_left;
        const let from_top  = this->draw_info.position_from_top;
        const let size_vert = this->draw_info.size_vertical;

        const let field = (this->fields->at(0));

        isize line_index = 0;
        for (; line_index < size_vert; line_index++)
        {
            moveCursorTo(from_left, from_top + line_index);
            printStdout("%s", field->getCharView().at(line_index));
        }
        moveCursorTo(0, 0);

        this->need_to_draw = false;
    }
}


/* virtual */ void FieldContainer::updateCharView()
{
    //
    let space_to_draw = 0;

    // Check direction of element
    const let layout_direction = this->layout.direction;
    if (layout_direction == FieldLayoutDirection::vertical)
    {
        space_to_draw = this->draw_info.size_vertical;
    }
    else if (layout_direction == FieldLayoutDirection::horizontal)
    {
        space_to_draw = this->draw_info.size_horizontal;
    }
    else { throw "Unknown direction num: " + parseString(isize(layout_direction)); }

    // TODO: Can only draw one element at now.
}


/* virtual */ void FieldContainer::handleInput(const ProcessedKeyInput& key_input)
{
}


FieldContainer& FieldContainer::addField(Field* f)
{
    this->fields->push_back(f);
    return *this;
}


/* virtual */ void FieldContainer::updateFromNotification(const NotificationDict& info)
{
}


FieldContainer::constructor()
{
    this->fields = new vector<Field*>();
}
