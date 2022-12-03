#pragma once

#include "../../head.h"
#include "Field.h"

#ifdef constructor
#undef constructor
#endif

#define constructor VerticalScrollSelectField


class VerticalScrollSelectField : public Field
{
  public:
    virtual void draw();
    virtual void updateCharView();
    virtual void updateFromNotification(const NotificationDict& info);
    virtual void handleInput(const ProcessedKeyInput& key_input);

    VerticalScrollSelectField& setHasFrame(bool has_frame);


  protected:
    vector<string> items;

    isize num_selected = 0;

    isize position_selected = 0;

    isize max_item_to_show;

    bool has_frame = true;

  public:
    static VerticalScrollSelectField createSized(isize line_to_show);
    static VerticalScrollSelectField createSized(isize line_to_show, const vector<string> init_items);

  public:
    constructor();
    constructor(const vector<string> init_items);
};