#pragma once

#include "../../head.h"


struct WindowFrameStyle
{
    /**
     * There is a icon showing the current states of the window.
     */
    bool has_brief_icon = true;

    bool has_title = true;

    bool has_frame = true;
};