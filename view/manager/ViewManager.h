#pragma once

#include "../../head.h"
#include "../container/Screen.h"

#ifdef constructor
#undef constructor
#endif

#define constructor ViewManager


class ViewManager;
static ViewManager view_manager = ViewManager();

class ViewManager
{
  private:
    /**
     * @brief Check if there is changes in console settings.
     *
     */
    void checkConsole();

  private:
    vector<Screen*> screens;
};