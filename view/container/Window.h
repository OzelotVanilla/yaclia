#pragma once

#include "../../head.h"
#include "../../util/terminal.h"
#include "../../util/observer_pattern/Publisher.trait.h"
#include "ViewContainer.h"
#include "WindowStatusIcon.h"
#include "WindowFrameStyle.h"
#include "Field.h"
#include "FieldContainer.h"

#ifdef constructor
#undef constructor
#endif

#define constructor Window


class Window : public ViewContainer, virtual public Publisher, virtual public Subscriber
{
  public:
    virtual void draw();
    virtual void updateCharView();
    virtual void updateConsoleRelatedInfo();

    virtual NotificationDict handleInput(const ProcessedKeyInput& key_input);

    Window& addField(Field* f);

    // /* This use the simple iter version */ virtual void notifySubsriber(const NotificationDict& info);
    virtual void updateFromNotification(const NotificationDict& info);

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

    Window& refresh()
    {
        this->need_to_update_char_view = true;
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

    FieldContainer* field_container;

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