#pragma once

#include "../../head.h"

enum class WindowStatus
{
    none,

    /**
     * Ready to be used.
     */
    ready,

    /**
     * Process running inside.
     */
    running,

    /**
     * Will not respond to input.
     */
    busy,

    /**
     * Show there is notification.
     */
    notifying,

    not_ready_to_close
};