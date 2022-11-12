#pragma once

#include "../../head.h"
#include "ViewContainer.h"

#ifdef constructor
#undef constructor
#endif

#define constructor Window


class Window : public ViewContainer
{
  public:
    /* virtual */ void draw();
    /* virtual */ void updateConsoleRelatedInfo();

  public:
    constructor();

  private:
    bool has_frame = true;
};