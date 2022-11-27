#pragma once

#include "../head.h"
#include "../system/sys_call.h"

#ifdef constructor
#undef constructor
#endif

#define constructor ConsoleStatus

#ifdef _env_linux
#elif _env_windows
#endif

struct ConsoleStatus
{
    /**
     * The width of the actual console.
     */
    int width;

    /**
     * The height of the actual console.
     */
    int height;
};