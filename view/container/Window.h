#pragma once

#include "../../head.h"
#include "../../util/terminal.h"
#include "../../util/observer_pattern/Publisher.trait.h"
#include "ViewContainer.h"
#include "WindowStatusIcon.h"
#include "WindowFrameStyle.h"
#include "Field.h"
#include "FieldLayout.h"

#ifdef constructor
#undef constructor
#endif

#define constructor Window


class Window : public ViewContainer, public Publisher
{
  public:
    virtual void draw();
    virtual void updateCharView();
    virtual void updateConsoleRelatedInfo();

    virtual void handleInput(const ProcessedKeyInput& key_input);

    virtual void notifySubsriber(const NotificationDict& info);

    Window&        moveTo(int from_left, int from_top);
    inline Window& putInPlace(int from_left, int from_top)
    {
        return this->moveTo(from_left, from_top);
    }

    Window& setTitle(string title);

    Window& setId(string new_id)
    {
        this->id = new_id;
        return *this;
    }

    const string& getId() const
    {
        return this->id;
    }

    void close()
    {
        this->notifySubsriber({ { "window_close", this->id } });
    }

  public:
    WindowStatus window_status = WindowStatus::none;

  private:
    string drawTitleLine() const;
    string drawBottomLine() const;

  private:
    WindowFrameStyle window_style;

    FieldLayout main_layout;

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