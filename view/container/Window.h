#pragma once

#include "../../head.h"
#include "../../util/terminal.h"
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
    /* virtual */ void updateCharView();
    /* virtual */ void updateConsoleRelatedInfo();

    Window& move(int to_left, int to_up);
    Window& putInPlace(int from_left, int from_up);

    Window& setTitle(string title);

  private:
    string drawTitleLine() const;
    string drawBottomLine() const;

  private:
    string title       = "";
    string status_icon = " ";


  public:
    constructor();
    static Window createSized(int width, int height);
    constructor(int width, int height, int from_left, int from_top);

  private:
    WindowFrameStyle window_style;
    vector<Layout>*  layouts = nullptr;
};