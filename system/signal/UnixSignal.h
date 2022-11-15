#pragma once
#include "../../head.h"


namespace signal_unix_namesp
{

#include <signal.h>
#include <stdlib.h>


enum class UnixSignal
{
    /**
     * Hang up found, or solving dead process.
     */
    hang_up = SIGHUP,

    /**
     * Keyboard interrupt required (Ctrl + C).
     */
    interrupt = SIGINT,

    /**
     * Keyboard quit required (Ctrl + Q).
     */
    quit = SIGQUIT,

    ill_instruction     = SIGILL,
    trap                = SIGTRAP,
    abort               = SIGABRT,
    bus_error           = SIGBUS,
    math_error          = SIGFPE,
    kill                = SIGKILL,
    user_defined_1      = SIGUSR1,
    memory_ill_access   = SIGSEGV,
    user_defined_2      = SIGUSR2,
    no_read_pipe        = SIGPIPE,
    alarm               = SIGALRM,
    termination         = SIGTERM,
    stack_fault         = SIGSTKFLT,
    child_stop          = SIGCHLD,
    resume              = SIGCONT,
    pause               = SIGSTOP,
    keyboard_pause      = SIGTSTP,
    background_input    = SIGTTIN,
    background_output   = SIGTTOU,
    urgent              = SIGURG,
    cpu_exceed_time     = SIGXCPU,
    file_size_exceed    = SIGXFSZ,
    virtual_time_expire = SIGVTALRM,
    profil_time_expire  = SIGPROF,
    window_resize       = SIGWINCH,
    io_possible         = SIGIO,
    power_failure       = SIGPWR,
    bad_sys_call        = SIGSYS
};

} // namespace signal_unix_namesp


using signal_unix_namesp::UnixSignal;