#pragma once

#include "../../head.h"
#include "../container/Screen.h"

#ifdef constructor
#undef constructor
#endif

#define constructor ViewManager


// There exist a static member.
/* static ViewManager view_manager; */

class ViewManager
{
  public:
    ViewManager& draw();

    ViewManager& pushScreen(Screen* s);
    ViewManager& popScreen();

    ViewManager& start() noexcept(false);
    ViewManager& end();

  private:
    /**
     * @brief Check and update if there is changes in console settings.
     *
     */
    void checkAndUpdateConsoleInfo();

    void handleSignal();

  private:
    vector<Screen*> screens;

    bool should_run = true;
};

static ViewManager view_manager = ViewManager();

class NoScreenToShowError : public std::exception
{
  public:
    string reason;

    virtual const char* what() const noexcept override
    {
        return this->reason.c_str();
    }

    NoScreenToShowError(string reason = "No screen could be show at this time.")
    {
        this->reason = "\033[38;2;236;109;113m[ERR!] " + reason + "\033[0m";
    }
};