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

class FieldContainer : public Field, public virtual Subscriber, public virtual Publisher
{
  public:
    virtual void draw();

    virtual void updateCharView();

    virtual NotificationDict handleInput(const ProcessedKeyInput& key_input);

    FieldContainer& addField(Field* f);

    FieldContainer& moveTo(isize from_left, isize from_top);

  public:
    // /* This use the simple iter version */ virtual void notifySubsriber(const NotificationDict& info);
    virtual void updateFromNotification(const NotificationDict& info);

  private:
    FieldLayout layout;

    vector<Field*>* fields;

    Field* active_field;

  public:
    static FieldContainer createSized(int width, int height);

  public:
    constructor();
    constructor(int width, int height);
};