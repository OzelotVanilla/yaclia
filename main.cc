#include "main.h"

bool main_process_can_run = true;

int main(int argc, char const* argv[])
{
    registerAllSignalHandler();

    // Start view manager
    view_manager.start();

    //  Main Process
    view_manager.run();

    // char buffer[6];

    // bool      can_run       = true;
    // const let terminate_key = ProcessedKeyInput(KbdChar::q, KbdModifier::none);
    // while (can_run)
    // {
    //     KeyInputBuffer buffer;
    //     bool           is_success = getAndWriteConsoleInput(buffer);
    //     if (not buffer.empty())
    //     {
    //         ProcessedKeyInput key_input = buffer.front();
    //         printf("%s\r\n", str(key_input).c_str());
    //         buffer.pop();

    //         if (key_input == terminate_key)
    //         {
    //             printf("%s\r\n", "Should terminate when 'q' pressed.");
    //             can_run = false;
    //         }

    //         printf("----\r\n");
    //     }
    // }



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