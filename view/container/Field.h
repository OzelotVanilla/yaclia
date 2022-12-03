#pragma once

#include "../../head.h"
#include "ViewContainer.h"
#include "../../util/observer_pattern/Publisher.trait.h"
#include "../../util/observer_pattern/Subscriber.trait.h"
#include "../../util/terminal.h"


#ifdef constructor
#undef constructor
#endif

#define constructor Field

class Field : public ViewContainer, virtual public Subscriber, virtual public Publisher
{
  public:
    virtual void draw() = 0;

    virtual void updateCharView() = 0;

    virtual void handleInput(const ProcessedKeyInput& key_input) = 0;

    const vector<string>& getCharView()
    {
        return this->draw_info.char_view;
    }

  public:
    // /* This use the simple iter version */ virtual void notifySubsriber(const NotificationDict& info);
    virtual void updateFromNotification(const NotificationDict& info) = 0;
};