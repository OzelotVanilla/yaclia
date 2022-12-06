#pragma once

#include "../../head.h"
#include "../../util/terminal.h"
#include "ViewContainer.h"
#include "Window.h"
#include "../../util/observer_pattern/Publisher.trait.h"
#include "../../util/observer_pattern/Subscriber.trait.h"

#ifdef constructor
#undef constructor
#endif

#define constructor Screen


/**
 * Screen of the
 *
 * It will hold several `Window`.
 */
class Screen : public ViewContainer, virtual public Publisher, virtual public Subscriber
{
  public:
    Screen& pushInWindow(Window* w);
    Screen& popOutWindow(Window* w);

    Screen& addWindow(Window* w)
    {
        return this->pushInWindow(w);
    }

    Screen& deleteWindow(Window* w)
    {
        return this->popOutWindow(w);
    }

    Screen& deleteWindowById(const string& win_id)
    {
        return *this;
    }

    Window& getActiveWindow()
    {
        return *this->window_binded->at(len(*this->window_binded) - 1);
    }

    virtual void draw();

    virtual void updateCharView();

    virtual void updateConsoleRelatedInfo();

    virtual NotificationDict handleInput(const ProcessedKeyInput& key_input);

    Screen& setId(string new_id)
    {
        this->id = new_id;
        return *this;
    }

    Screen& setBackgroundChar(uchar c);

  public:
    // virtual void notifySubsriber(const NotificationDict& info);
    virtual void updateFromNotification(const NotificationDict& info);

  private:
    bool registerd_into_stack = false;

    bool has_frame = false;

    uchar background_char = ' ';

    vector<Window*>* window_binded;

  public:
    constructor();
};