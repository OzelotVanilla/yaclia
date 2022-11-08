#pragma once
#include "../head.h"
#include "../util/sys_call.h"

#ifdef constructor
#undef constructor
#endif

#define constructor ConsoleConfig

class ConsoleConfig
{
  public:
    /**
     * The width of the actual console.
     */
    int console_width = -1;

    /**
     * The height of the actual console.
     */
    int console_height = -1;


  public:
    static int getConsoleHeight();
    static int getConsoleWidth();

    constructor();
};