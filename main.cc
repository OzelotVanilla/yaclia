#include "main.h"

bool main_process_can_run = true;

int main(int argc, char const* argv[])
{
    registerAllSignalHandler();

    // Start view manager
    view_manager.start();

    //  Main Process
    // view_manager.run();
    for (size_t i = 0; i < 20; i++)
    {
        moveCursorTo(i, i);
        putchar('.');
    }


    view_manager.end();
    return 0;
}


void registerAllSignalHandler()
{
    registerSignalHandler(UnixSignal::interrupt, onInterrupt);
}


void onInterrupt(int sig)
{
    view_manager.handleInterrupt();
}