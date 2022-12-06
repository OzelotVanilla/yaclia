#include "../../head.h"
#include "../container/VerticalScrollSelectField.h"
#include "../container/Window.h"

Window createViewManagerMenu();

static VerticalScrollSelectField view_manager_menu_items =
    VerticalScrollSelectField::createSized(
        terminal_namesp::current_console_status.height - 6
    )
        .addItem("Item 1")
        .addItem("Item 2")
        .addItem("Item 3")
        .addItem("Item 4")
        .addItem("Item 5")
        .addItem("Quit Menu", new string("window_close"))
        .addItem("Exit Yaclia", new string("main_process_stop"))
        .setId("view_manager_menu_items");

static Window* view_manager_menu =
    &((new Window(
           terminal_namesp::current_console_status.width - 8,
           terminal_namesp::current_console_status.height - 4,
           1,
           1
       ))
          ->setTitle("Yaclia Menu")
          .setId("view_manager_menu")
          .moveTo(4, 1)
          .addField(&view_manager_menu_items));
