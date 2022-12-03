#include "../../head.h"
#include "../container/VerticalScrollSelectField.h"
#include "../container/Window.h"

static VerticalScrollSelectField view_manager_menu_items =
    VerticalScrollSelectField::createSized(terminal_namesp::current_console_status.height - 6);

static Window view_manager_menu =
    Window::createSized(
        terminal_namesp::current_console_status.width - 8,
        terminal_namesp::current_console_status.height - 4
    )
        .setTitle("Yaclia Menu")
        .setId("view_manager_menu")
        .moveTo(4, 1);