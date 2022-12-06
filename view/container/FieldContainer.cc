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

        const let field     = (this->fields->at(0)); // TODO: Now only can draw one element
        const let char_view = field->getCharView();

        isize line_index = 0;
        for (; line_index < std::min(isize(size_vert), len(char_view)); line_index++)
        {
            moveCursorTo(from_left, from_top + line_index);
            printf("%s\r\n", char_view.at(line_index).c_str());
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
    this->fields->at(0)->updateCharView();
}


/* virtual */ NotificationDict FieldContainer::handleInput(const ProcessedKeyInput& key_input)
{
    // TODO: Now it is wrong: If no active, select first
    let a_field = this->active_field = this->fields->at(0);
    // If it is affecting the container

    // If it is not affecting the container.
    return this->active_field->handleInput(key_input);
}


FieldContainer& FieldContainer::addField(Field* f)
{
    // TODO: Problematic since only one field.
    // In the future, should be function to calculate width.
    f->moveTo(this->draw_info.position_from_left, this->draw_info.position_from_top);
    f->changeSize(this->draw_info.size_horizontal, this->draw_info.size_vertical);
    f->addSubscriber(this);
    this->fields->push_back(f);
    return *this;
}


FieldContainer& FieldContainer::moveTo(isize from_left, isize from_top)
{
    this->draw_info.position_from_left = from_left;
    this->draw_info.position_from_top  = from_top;
    return *this;
}


/* virtual */ void FieldContainer::updateFromNotification(const NotificationDict& info)
{
    if (dictCheckEqual(info, "redraw", "true"))
    {
        this->notifySubsriber({ { "redraw", "true" } });
    }
}


FieldContainer FieldContainer::createSized(int width, int height)
{
    let c = FieldContainer(width, height);
    return std::move(c);
}


FieldContainer::constructor()
{
    // TODO: How to set a reasonable value here.
    delegate(-1, -1);
}


FieldContainer::constructor(int width, int height)
{
    this->draw_info.size_horizontal = width;
    this->draw_info.size_vertical   = height;
    this->fields                    = new vector<Field*>();
}
