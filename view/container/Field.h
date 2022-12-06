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

    virtual NotificationDict handleInput(const ProcessedKeyInput& key_input) = 0;

    virtual const vector<string>& getCharView()
    {
        return this->draw_info.char_view;
    }

    virtual Field& moveTo(isize from_left, isize from_top)
    {
        this->draw_info.position_from_left = from_left;
        this->draw_info.position_from_top  = from_top;
        return *this;
    }

    virtual Field& changeSize(isize width, isize height)
    {
        this->draw_info.size_horizontal = width;
        this->draw_info.size_vertical   = height;
        return *this;
    };

  public:
    // /* This use the simple iter version */ virtual void notifySubsriber(const NotificationDict& info);
    virtual void updateFromNotification(const NotificationDict& info) = 0;
};