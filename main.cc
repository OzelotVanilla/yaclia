#include "main.h"

bool main_process_can_run = true;

int main(int argc, char const* argv[])
{
    registerAllSignalHandler();

    // Start view manager
    view_manager.start();

    //  Main Process
    view_manager.run();

    // Restore
    view_manager.end();
    return 0;
}


#ifdef _env_linux
void registerAllSignalHandler()
{
    registerSignalHandler(UnixSignal::interrupt, onInterrupt);
}


void onInterrupt(int sig)
{
    view_manager.handleInterrupt();
}
#elif _env_windows
void registerAllSignalHandler()
{
}
#endif