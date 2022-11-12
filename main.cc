#include "main.h"

int main(int argc, char const* argv[])
{
    // Create main screen
    let main_screen = new Screen();
    view_manager.pushScreen(main_screen);
    view_manager.start();
    view_manager.end();
    return 0;
}
