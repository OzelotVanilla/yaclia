#pragma once

#include "../../head.h"
#include "../container/Screen.h"
#include "../container/Window.h"
#include "../../util/terminal.h"
#include "../../system/sys_call.h"
#include "../../util/key_input.h"
#include "../../util/observer_pattern/Subscriber.trait.h"


#ifdef constructor
#undef constructor
#endif

#define constructor ViewManager


class Screen;

class ViewManager;

using RegisteredInputHandle = std::unordered_map<ProcessedKeyInput, function<void(ViewManager*)>>;

// There exist a static member.
/* static ViewManager view_manager; */

class ViewManager : public Subscriber
{
  public:
    /**
     * @brief Start main loop and run yaclia.
     *
     */
    ViewManager& run();

    ViewManager& draw();

    ViewManager& start() noexcept(false);
    ViewManager& end();

    ViewManager& pushScreen(Screen* s);
    ViewManager& popScreen();
    Screen&      getActiveScreen();

    int getConsoleLines();
    int getConsoleColumns();

  public:
    /* virtual */ void updateFromNotification(const NotificationDict& info);

    void handleInterrupt();

  private:
    /**
     * @brief Check and update if there is changes in console settings.
     *
     */
    void checkAndUpdateConsoleInfo();

    void handleSignal();

    ViewManager& processInput();
    ViewManager& handleInput(ProcessedKeyInput data);

    ViewManager& updateConsoleRelatedInfo();

  private:
    vector<Screen*>* screens = nullptr;

    RegisteredInputHandle* input_handlers = nullptr;

    bool should_run = true;

    bool need_to_draw = true;

    bool main_process_can_run = true;

    bool showing_menu = false;

    KeyInputBuffer* key_input_buffer = nullptr;

  public:
    constructor();
    destructor();
};

static ViewManager view_manager = ViewManager();

static Window view_manager_menu =
    Window::createSized(
        terminal_namesp::current_console_status.width - 4,
        terminal_namesp::current_console_status.height - 4
    )
        .setTitle("Yaclia Menu")
        .setId("view_manager_menu")
        .moveTo(2, 1);

void showViewManagerMenu(ViewManager* v);
void closeViewManagerMenu(ViewManager* v);

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