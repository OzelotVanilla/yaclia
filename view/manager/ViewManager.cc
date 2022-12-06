#include "ViewManager.h"
#include "../instance/YacliaMainMenu.h"



ViewManager& ViewManager::run()
{
    try
    {
        while (this->main_process_can_run)
        {
            terminal_namesp::updateConsoleStatusInfo();
            this->processInput();
            this->draw();
        }
    }
    catch (std::exception& any_err)
    {
        this->end(string(any_err.what()));
        system("\n");
    }

    return *this;
}


ViewManager& ViewManager::draw()
{
    // Update the console information to the global var.
    terminal_namesp::current_console_status = terminal_namesp::updateConsoleStatusInfo();

    if (this->need_to_draw)
    {
        // Check if no screen, give error
        if (len(*this->screens) <= 0)
        {
            throw NoScreenToShowError();
        }

        // Draw top screen
        this->getActiveScreen().draw();

        this->need_to_draw = false;
    }

    // If use printf, force console to show, do not be lazy.
    flushOutputToConsole();

    return *this;
}


ViewManager& ViewManager::pushScreen(Screen* s)
{
    this->screens->push_back(s);
    s->addSubscriber(this);
    return *this;
}


ViewManager& ViewManager::popScreen()
{
    this->getActiveScreen().removeSubscriber(this);
    this->screens->pop_back();
    return *this;
}

Screen& ViewManager::getActiveScreen()
{
    return *this->screens->at(this->screens->size() - 1);
}


ViewManager& ViewManager::start()
{
    changeToAlternativeScreen();
    // Make the current console non-blocking and non-echo-input
    prepareConsole();
    moveCursorTo(0, 0);
    hideCursor();
    this->main_process_can_run = true;

    return *this;
}


ViewManager& ViewManager::end(string reason)
{
    this->main_process_can_run = false;
    showCursor();
    restoreConsole();
    backFromAlternativeScreen();
    cout << reason << endl;
    return *this;
}


ViewManager& ViewManager::processInput()
{
    // Get input (at this time, console should be non-blocking and non-echo-input)
    getAndWriteKeyInputToBuffer(*this->key_input_buffer);

    // Send input to screen, and it may also send to active window
    if (not this->key_input_buffer->empty())
    {
        this->handleInput(this->key_input_buffer->front());
        this->key_input_buffer->pop();
    }

    return *this;
}


ViewManager& ViewManager::handleInput(const ProcessedKeyInput& data)
{
    // If this is directly affecting view manager.
    if (this->input_handlers->contains(data))
    {
        this->input_handlers->at(data)(this);
    }

    // Else, send it to active screen.
    else { this->getActiveScreen().handleInput(data); }

    return *this;
}


ViewManager& ViewManager::showMenu()
{
    if (not this->showing_menu)
    {
        this->getActiveScreen().addWindow(&view_manager_menu);
        this->showing_menu = true;
    }
    return *this;
}


// ViewManager& ViewManager::closeMenu()
// {
//     if (this->showing_menu)
//     {
//         this->getActiveScreen().deleteWindow(&view_manager_menu);
//         this->showing_menu = false;
//     }
//     return *this;
// }


/* virtual */ void ViewManager::updateFromNotification(const NotificationDict& info)
{
    if (info.contains("view_manager_control"))
    {
        const let action = info.at("view_manager_control");
        if (action == "end") { this->end(); }
    }
    if (dictCheckEqual(info, "redraw", "true")) { this->need_to_draw = true; }
}



void ViewManager::handleInterrupt()
{
    this->end();
}


void ViewManager::checkAndUpdateConsoleInfo()
{
}


void ViewManager::handleSignal()
{
}


ViewManager::constructor()
{
    terminal_namesp::current_console_status = terminal_namesp::updateConsoleStatusInfo();

    this->screens        = new vector<Screen*>();
    this->input_handlers = new RegisteredInputHandle();
    // // Push a default screen in
    // this->pushScreen(new Screen());
    // let w = Window::createSized(20, 5).setTitle("Too long string");
    // this->getActiveScreen().pushInWindow(&w);

    this->key_input_buffer = new KeyInputBuffer();

    // By default, `alt + m` create a menu window
    (*this->input_handlers)[ProcessedKeyInput(KbdChar::m, KbdModifier::alt)] = showViewManagerMenu;
}


ViewManager::destructor()
{
    delete this->screens;
}