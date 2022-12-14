#include "../../head.h"
#include "../container/VerticalScrollSelectField.h"
#include "../container/Window.h"

static VerticalScrollSelectField view_manager_menu_items =
    VerticalScrollSelectField::createSized(
        terminal_namesp::current_console_status.height - 6
    )
        .addItem("Item 0")
        .addItem("Item 1")
        .addItem("Item 2")
        .addItem("Item 3")
        .addItem("Item 4")
        .addItem("Item 5")
        .addItem("Item 6")
        .addItem("Item 7")
        .addItem("Item 8")
        .addItem("Quit Menu", new string("window_close"))
        .addItem("Exit Yaclia", new string("main_process_stop"))
        .addItem("Item 11")
        .addItem("Item 12")
        .addItem("Item 13")
        .addItem("Item 14")
        .addItem("Item 15")
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

static Window* view_manager_text_field =
    &((new Window(
           terminal_namesp::current_console_status.width - 8,
           terminal_namesp::current_console_status.height - 4,
           1,
           1
       ))
          ->setTitle("Field"));