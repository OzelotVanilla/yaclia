#include "ViewManager.h"



ViewManager& ViewManager::run()
{
    while (this->main_process_can_run)
    {
        terminal_namesp::updateConsoleStatusInfo();
        view_manager.processInput();
        view_manager.draw();
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
        top_screen->draw();
    }

    // If use printf, force console to show, do not be lazy.
    flushOutputToConsole();

    return *this;
}


ViewManager& ViewManager::pushScreen(Screen* s)
{
    this->screens->push_back(s);
    s->addSubscriber(this);
    this->top_screen = s;
    return *this;
}


ViewManager& ViewManager::popScreen()
{
    this->top_screen->removeSubscriber(this);
    this->screens->pop_back();
    this->top_screen = this->screens->at(len(*this->screens) - 1);
    return *this;
}


ViewManager& ViewManager::start()
{
    changeToAlternativeScreen();
    // Make the current console non-blocking and non-echo-input
    prepareConsole();
    moveCursorTo(0, 0);

    return *this;
}


ViewManager& ViewManager::end()
{
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

    // Else, send it to active screen.

    return *this;
}


/* virtual */ void ViewManager::updateFromNotification(NotificationDict info)
{
    if (info.contains("redraw") and info["redraw"] == "true") { this->need_to_draw = true; }
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
    this->screens = new vector<Screen*>();
    // Push a default screen in
    this->pushScreen(new Screen());

    this->key_input_buffer = new KeyInputBuffer();
}


ViewManager::destructor()
{
    delete this->screens;
}