#pragma once

#include "../../head.h"
#include "Field.h"
#include "FieldLayout.h"
#include "ViewContainer.h"
#include "../../util/observer_pattern/Publisher.trait.h"
#include "../../util/observer_pattern/Subscriber.trait.h"
#include "../../util/terminal.h"


#ifdef constructor
#undef constructor
#endif

#define constructor FieldContainer

class FieldContainer : public Field, virtual public Subscriber, virtual public Publisher
{
  public:
    virtual void draw();

    virtual void updateCharView();

    virtual NotificationDict handleInput(const ProcessedKeyInput& key_input);

    FieldContainer& addField(Field* f);

    FieldContainer& moveTo(isize from_left, isize from_top);

    FieldContainer& setId(string new_id)
    {
        this->id = new_id;
        return *this;
    }

  public:
    // /* This use the simple iter version */ virtual void notifySubsriber(const NotificationDict& info);
    virtual void updateFromNotification(const NotificationDict& info);

  private:
    FieldLayout layout;

    vector<Field*>* fields;

    Field* active_field = nullptr;

  public:
    static FieldContainer createSized(int width, int height);

  public:
    constructor();
    constructor(int width, int height);
};