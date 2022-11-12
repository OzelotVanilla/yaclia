#pragma once

#include "../../head.h"

#ifdef constructor
#undef constructor
#endif

#define constructor ViewDrawInfo


/**
 * A data structure that save the information for ViewManager to draw in the actual terminal.
 */
class ViewDrawInfo
{
  public:
    /**
     * Absolute vertical position,
     * counting from top in unit of actual console char.
     */
    int position_from_top = 0;

    /**
     * Absolute position to its parent,
     * counting from left in unit of actual console char.
     */
    int position_from_left = 0;

    /**
     * Horizontal size of current view container,
     * represented in unit of actual console char.
     */
    int size_horizontal = 0;

    /**
     * Vertical size of current view container,
     * represented in unit of actual console char.
     */
    int size_vertical = 0;
};
