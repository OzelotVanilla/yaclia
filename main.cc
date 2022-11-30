#include "main.h"


int main(int argc, char const* argv[])
{
    registerAllSignalHandler();

    // Start view manager
    view_manager.start();

    //  Main Process
    // view_manager.run();
    moveCursorTo(5, 5);
    printStdout("test");

    // Restore
    view_manager.end();
    return 0;
}


#ifdef _env_linux

void registerAllSignalHandler()
{
    registerSignalHandler(UnixSignal::interrupt, onInterrupt);
    registerSignalHandler(UnixSignal::termination, onTerminate);
}


void onInterrupt(int sig)
{
    view_manager.handleInterrupt();
}

void onTerminate(int sig)
{
    view_manager.end();
}

#elif _env_windows

void registerAllSignalHandler()
{
}

#endif