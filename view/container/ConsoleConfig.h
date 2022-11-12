#pragma once

#include "../../head.h"
#include "../../util/sys_call.h"

#ifdef constructor
#undef constructor
#endif

#define constructor ConsoleConfig

class ConsoleConfig;

static ConsoleConfig main_console_config = ConsoleConfig();


class ConsoleConfig
{
  private:
    /**
     * The width of the actual console.
     */
    int width;

    /**
     * The height of the actual console.
     */
    int height;

  public:
    int getHeight();
    int getWidth();

    void update();

  private:
    static int fetchConsoleHeightFromSys();
    static int fetchConsoleWidthFromSys();

  public:
    constructor();
};