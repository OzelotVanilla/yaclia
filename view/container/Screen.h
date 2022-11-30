#pragma once

#include "../../head.h"
#include "../../util/terminal.h"
#include "ViewContainer.h"
#include "Window.h"
#include "../../util/observer_pattern/Publisher.trait.h"

#ifdef constructor
#undef constructor
#endif

#define constructor Screen


/**
 * Screen of the
 *
 * It will hold several `Window`.
 */
class Screen : public ViewContainer, public Publisher
{
  public:
    Screen& pushInWindow(Window* w);
    Screen& popOutWindow(Window* w);

    inline Screen& addWindow(Window* w);
    inline Screen& deleteWindow(Window* w);

    /* virtual */ void draw();

    /* virtual */ void updateCharView();

    /* virtual */ void updateConsoleRelatedInfo();

    Screen& setBackgroundChar(uchar c);

  public:
    virtual void notifySubsriber(const NotificationDict& info);

  private:
    bool registerd_into_stack = false;

    bool has_frame = false;

    uchar background_char = ' ';

    vector<Window*>* window_binded;

  public:
    constructor();
};