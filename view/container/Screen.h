#pragma once

#include "../../head.h"
#include "ConsoleConfig.h"
#include "ViewContainer.h"
#include "Window.h"

#ifdef constructor
#undef constructor
#endif

#define constructor Screen


class Screen;

namespace view_container_screen
{
static let screen_stack = vector<Screen>();
} // namespace view_container_screen

/**
 * Screen of the
 *
 * It will hold several `Window`.
 */
class Screen : public ViewContainer
{
  public:
    Screen& pushInWindow(Window* w);
    Screen& popOutWindow();

    inline Screen& addWindow(Window* w);
    inline Screen& deleteWindow();

    /* virtual */ void draw();
    /* virtual */ void updateConsoleRelatedInfo();

  private:
    bool registerd_into_stack = false;

    bool has_frame = false;

    vector<Window*>* window_binded;

  public:
    constructor();
    constructor(ConsoleConfig c);
};