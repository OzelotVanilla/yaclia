#pragma once

#include "../../head.h"
#include "Field.h"

#ifdef constructor
#undef constructor
#endif

#define constructor VerticalScrollSelectField

/** first: text to show; second: text returned. */
struct ItemShowing
{
    string  display_text;
    string* value_retuned;

    ItemShowing(const string display_text, string* value_retuned)
    {
        this->display_text  = display_text;
        this->value_retuned = value_retuned;
    }
};


class VerticalScrollSelectField : public Field, virtual public Publisher
{
  public:
    virtual void draw();

    virtual void updateCharView();

    virtual void updateFromNotification(const NotificationDict& info);

    virtual NotificationDict handleInput(const ProcessedKeyInput& key_input);

    virtual VerticalScrollSelectField& addItem(string text);

    virtual VerticalScrollSelectField& addItem(string display_text, string* value_return);

    virtual VerticalScrollSelectField& deleteItem(string display_text);

    virtual VerticalScrollSelectField& selectScrollUp();

    virtual VerticalScrollSelectField& selectScrollDown();

    virtual string selectCurrentItem();

    // virtual void notifySubsriber(const NotificationDict& info)
    // {
    //     for (size_t i = 0; i < len(*this->subscribers); i++)
    //     {
    //         this->subscribers->at(i)->updateFromNotification(info);
    //     }
    // }

    // template <typename ItemCallbackFunction>
    // VerticalScrollSelectField& addItem(string name, ItemCallbackFunction callback);

    VerticalScrollSelectField& setHasFrame(bool has_frame);

    VerticalScrollSelectField& setId(string new_id)
    {
        this->id = new_id;
        return *this;
    }


  protected:
    vector<ItemShowing> items;

    isize num_selected = 0;

    isize position_selected = 0;

    isize max_item_to_show;

    bool has_frame = true;

    VerticalScrollSelectField& getSelectResult(string select_result);


  public:
    static VerticalScrollSelectField createSized(isize line_to_show);
    static VerticalScrollSelectField createSized(isize line_to_show, const vector<string> init_items);

  public:
    constructor();
    constructor(const vector<string> init_items);
};