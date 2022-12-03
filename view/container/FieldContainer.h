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

    virtual void handleInput(const ProcessedKeyInput& key_input);

    FieldContainer& addField(Field* f);

  public:
    // /* This use the simple iter version */ virtual void notifySubsriber(const NotificationDict& info);
    virtual void updateFromNotification(const NotificationDict& info);

  private:
    FieldLayout layout;

    vector<Field*>* fields;

  public:
    constructor();
};