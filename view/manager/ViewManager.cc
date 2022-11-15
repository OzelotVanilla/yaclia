#include "ViewManager.h"



ViewManager& ViewManager::draw()
{
    // Check if no screen, give error
    if (len(*this->screens) <= 0)
    {
        throw NoScreenToShowError();
    }

    // Get last screen
    let last_screen = this->screens->at(len(*this->screens) - 1);
    last_screen->draw();

    return *this;
}



ViewManager& ViewManager::pushScreen(Screen* s)
{
    this->screens->push_back(s);
    return *this;
}


ViewManager& ViewManager::popScreen()
{
    return *this;
}


ViewManager& ViewManager::start()
{
    system("tput smcup");
    return *this;
}


ViewManager& ViewManager::end()
{
    system("tput rmcup");
    return *this;
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
}
