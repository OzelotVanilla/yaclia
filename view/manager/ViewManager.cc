#include "ViewManager.h"



ViewManager& ViewManager::run()
{
    while (this->main_process_can_run)
    {
        view_manager.processInput();
        view_manager.draw();
    }

    return *this;
}

ViewManager& ViewManager::draw()
{
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

    return *this;
}



ViewManager& ViewManager::pushScreen(Screen* s)
{
    this->screens->push_back(s);
    this->top_screen = s;
    return *this;
}


ViewManager& ViewManager::popScreen()
{
    this->screens->pop_back();
    this->top_screen = this->screens->at(len(*this->screens) - 1);
    return *this;
}


ViewManager& ViewManager::start()
{
    changeToAlternativeScreen();
    // Make the current console non-blocking and non-echo-input
    setCurrentConsoleNonBlocking();
    return *this;
}


ViewManager& ViewManager::end()
{
    setCurrentConsoleDefaultState();
    backFromAlternativeScreen();
    return *this;
}


ViewManager& ViewManager::processInput()
{
    ProcessedKeyInput input_data;

    // Get input (at this time, console should be non-blocking and non-echo-input)
    bool is_read_valid = getConsoleInput(input_data);

    // Send input to screen, and it may also send to active window
    if (is_read_valid) { this->handleInput(input_data); }

    return *this;
}


ViewManager& ViewManager::handleInput(ProcessedKeyInput data)
{
    // If this is directly affecting view manager

    return *this;
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
}


ViewManager::destructor()
{
    delete this->screens;
}