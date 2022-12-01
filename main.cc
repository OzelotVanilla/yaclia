#include "main.h"


int main(int argc, char const* argv[])
{
    registerAllSignalHandler();

    // Start view manager
    view_manager.start();

    // Give screen
    let* s = new Screen();
    let  w = Window::createSized(50, 12).setTitle("Too long string");
    s->setBackgroundChar('.');
    s->pushInWindow(&w);
    view_manager.pushScreen(s);

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