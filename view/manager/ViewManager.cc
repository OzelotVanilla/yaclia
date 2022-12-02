#include "ViewManager.h"



ViewManager& ViewManager::run()
{
    while (this->main_process_can_run)
    {
        terminal_namesp::updateConsoleStatusInfo();
        this->processInput();
        this->draw();
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

    return *this;
}


ViewManager& ViewManager::end()
{
    showCursor();
    restoreConsole();
    backFromAlternativeScreen();
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


ViewManager& ViewManager::handleInput(ProcessedKeyInput data)
{
    // If this is directly affecting view manager.
    if (this->input_handlers->contains(data))
    {
        this->input_handlers->at(data)(this);
    }

    // Else, send it to active screen.

    return *this;
}


/* virtual */ void ViewManager::updateFromNotification(const NotificationDict& info)
{
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


void showViewManagerMenu(ViewManager* v)
{
    v->getActiveScreen().addWindow(&view_manager_menu);
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