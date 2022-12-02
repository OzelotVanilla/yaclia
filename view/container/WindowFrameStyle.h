#pragma once

#include "../../head.h"


struct WindowFrameStyle
{
    /**
     * There is a icon showing the current states of the window.
     */
    bool has_status_icon = true;

    /**
     * Until user set a title.
     */
    bool has_title = false;

    bool has_frame = true;

    bool has_focus_frame_shadow = true;

    string upper_left_char = "┌";

    string upper_right_char = "┐";

    string lower_left_char = "└";

    string lower_right_char = "┘";

    string horizontal_line_char = "─";

    string vertical_line_char = "│";
};