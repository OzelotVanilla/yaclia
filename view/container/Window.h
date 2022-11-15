#pragma once

#include "../../head.h"
#include "ViewContainer.h"
#include "WindowFrameStyle.h"
#include "Layout.h"

#ifdef constructor
#undef constructor
#endif

#define constructor Window


class Window : public ViewContainer
{
  public:
    /* virtual */ void draw();
    /* virtual */ void updateConsoleRelatedInfo();

    Window& move(int to_left, int to_up);
    Window& putInPlace(int from_left, int from_up);


  public:
    constructor();
    Window createSized(int width, int height);
    constructor(int width, int height, int from_left, int from_top);

  private:
    WindowFrameStyle window_style;
    vector<Layout>*  layouts = nullptr;
};