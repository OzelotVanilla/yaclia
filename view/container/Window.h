#pragma once

#include "../../head.h"
#include "../../util/terminal.h"
#include "../../util/observer_pattern/Publisher.trait.h"
#include "ViewContainer.h"
#include "WindowStatusIcon.h"
#include "WindowFrameStyle.h"
#include "Field.h"

#ifdef constructor
#undef constructor
#endif

#define constructor Window


class Window : public ViewContainer, public Publisher
{
  public:
    /* virtual */ void draw();
    /* virtual */ void updateCharView();
    /* virtual */ void updateConsoleRelatedInfo();

    /* virtual */ void notifySubsriber(const NotificationDict& info);

    Window&        moveTo(int from_left, int from_top);
    inline Window& putInPlace(int from_left, int from_top);

    Window& setTitle(string title);

    Window& setId(string new_id)
    {
        this->id = new_id;
        return *this;
    }

    const string& getId()
    {
        return this->id;
    }

    void close()
    {
    }

  public:
    WindowStatus window_status = WindowStatus::none;

  private:
    string drawTitleLine() const;
    string drawBottomLine() const;

  private:
    WindowFrameStyle window_style;
    vector<Field*>*  layouts = nullptr;

    string title       = "";
    string status_icon = " ";

    /**
     * Whether user is using a interactive mode of moving/resizing window.
     */
    bool is_setting_layout = false;

  public:
    constructor();
    static Window createSized(int width, int height);
    constructor(int width, int height, int from_left, int from_top);
};