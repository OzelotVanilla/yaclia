#include "ViewManager.h"



ViewManager& ViewManager::run()
{
    while (this->main_process_can_run)
    {
        // Get input
        let first_input = ncurses::wgetch(ncurses::stdscr);
        let input_data  = ProcessedKeyInput();
        // If need to check whether `alt` or `esc`
        if (first_input == int(NcursesKey::alt_or_esc))
        {
            // If `ESC` is pressed, then there will be no secondary input
            let second_input = ncurses::wgetch(ncurses::stdscr);
            if (second_input == -1) // That means this is a esc
            {
                ncurses::ungetch(second_input);
                input_data.key      = '\033';
                input_data.modifier = ProcessedKeyInput::Modifier::none;
            }
            else // That means an alt
            {
                input_data.key      = second_input;
                input_data.modifier = ProcessedKeyInput::Modifier::alt;
            }
        }
        else // Not `alt` or `esc`
        {
            input_data.key = first_input;
        }

        // Send input to screen, and it may also send to active window


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
    // system("tput smcup");
    ncurses::initscr();
    ncurses::keypad(ncurses::stdscr, true);
    ncurses::wtimeout(ncurses::stdscr, 0); // Input should not be blocked (?)
    // setCurrentConsoleNonBlocking();
    return *this;
}


ViewManager& ViewManager::end()
{
    ncurses::clear();
    ncurses::endwin();
    // setCurrentConsoleDefault();
    // system("tput rmcup");
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