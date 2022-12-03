#pragma once

#include "../../head.h"
#include "ViewContainer.h"
#include "../../util/observer_pattern/Publisher.trait.h"
#include "../../util/observer_pattern/Subscriber.trait.h"


#ifdef constructor
#undef constructor
#endif

#define constructor Field

class Field : public ViewContainer, public Subscriber, public Publisher
{
  public:
    virtual void draw() = 0;

    virtual void updateCharView() = 0;

    virtual void handleInput(const ProcessedKeyInput& key_input) = 0;

  public:
    // /* This use the simple iter version */ virtual void notifySubsriber(const NotificationDict& info);
    virtual void updateFromNotification(const NotificationDict& info) = 0;
};