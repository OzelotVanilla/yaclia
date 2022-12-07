#pragma once

#include "../../head.h"
#include "ViewContainer.h"
#include "../../util/observer_pattern/Publisher.trait.h"
#include "../../util/terminal.h"


#ifdef constructor
#undef constructor
#endif

#define constructor TextField

class TextField : public ViewContainer, virtual public Publisher
{
    private:
    isize text_height;

    isize text_width;

    isize cursor_position_x;

    isize cursor_position_y;

    string* lines;

    public:
    constructor(isize height, isize width);

    virtual void draw();

    virtual void updateCharView();

    // TODO: Should not be here.
    virtual NotificationDict handleInput(const ProcessedKeyInput& key_input);
};