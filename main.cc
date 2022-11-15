#include "main.h"

bool main_process_can_run = true;

int main(int argc, char const* argv[])
{
    // Create main screen
    let main_screen = new Screen();
    main_screen->setBackgroundChar('.');
    view_manager.pushScreen(main_screen);
    view_manager.start();

    registerAllSignalHandler();

    //  Main Process
    // while (main_process_can_run)
    // {
    //     view_manager.draw();
    // }
    let pos = getCursorPosition();


    view_manager.end();
    return 0;
}


void registerAllSignalHandler()
{
    registerSignalHandler(UnixSignal::interrupt, onInterrupt);
}

void onInterrupt(int sig)
{
    main_process_can_run = false;
    view_manager.end();
}