#pragma once

#include "../../head.h"
#include "../../system/signal/UnixSignal.h"
#include "ConsoleConfig.h"
#include "ViewInfo.h"

#ifdef constructor
#undef constructor
#endif

#define constructor ViewContainer

/**
 * Abstract class of View
 */
/* abstract */ class ViewContainer
{
  public:
    /**
     * @brief
     * Let the view container draw itself.
     * Implement it only draw the container it belongs to.
     *
     * @details
     * It will draw itself according to what it has.
     *
     * Notice that this draw function should:
     * 1. Draw itself regardless to what element it contains.
     * 2. Call the inside view containers' draw function.
     */
    virtual void draw() = 0;

  private:
    virtual void updateConsoleRelatedInfo() = 0;

  protected:
    /**
     * The info about position that is used to draw.
     */
    ViewDrawInfo draw_info;

    /**
     * A shared config of current console.
     */
    ConsoleConfig* console_config;
};