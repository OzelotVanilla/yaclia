#pragma once

#include "../../head.h"
#include "../../system/signal/signal.h"
#include "ViewDrawInfo.h"
#include "../../util/key_input.h"

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

    virtual void updateCharView() = 0;

    virtual void handleInput(const ProcessedKeyInput& key_input) = 0;

    //   private:
    // virtual void updateConsoleRelatedInfo() = 0;

  protected:
    /**
     * The info about position that is used to draw.
     */
    ViewDrawInfo draw_info;

    string id;

    bool need_to_draw = true; // TODO What is the meaning of this ?

    bool need_to_update_char_view = true;
};