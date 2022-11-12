#include "ViewManager.h"



ViewManager& ViewManager::draw()
{
    // Check if no screen, give error
    if (len(this->screens) <= 0)
    {
        throw NoScreenToShowError();
    }

    // Get last screen
    let& screen_to_draw = **(this->screens.end().base());
    screen_to_draw.draw();

    return *this;
}



ViewManager& ViewManager::pushScreen(Screen* s)
{
    this->screens.push_back(s);
    return *this;
}


ViewManager& ViewManager::popScreen()
{
    return *this;
}


ViewManager& ViewManager::start()
{
    //  Main Process
    while (this->should_run)
    {
    }

    return *this;
}


ViewManager& ViewManager::end()
{
    return *this;
}


void ViewManager::checkAndUpdateConsoleInfo()
{
}

void ViewManager::handleSignal()
{
}
