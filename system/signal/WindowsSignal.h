#pragma once

#include "../../head.h"


namespace signal_windows_namesp
{

#include <signal.h>

enum class WindowsSignal
{
    /**
     * Keyboard interrupt required (Ctrl + C).
     */
    interrupt = SIGINT,

    ill_instruction   = SIGILL,
    abort             = SIGABRT,
    math_error        = SIGFPE,
    memory_ill_access = SIGSEGV,
    termination       = SIGTERM,
};

} // namespace signal_windows_namesp


using signal_windows_namesp::WindowsSignal;