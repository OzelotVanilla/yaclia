#pragma once

#include "../../head.h"
#include "ViewContainer.h"

#ifdef constructor
#undef constructor
#endif

#define constructor Focusable

/**
 * Abstract class for all views can be focused (selected).
 * A focused view may able to do more action, for example, a focused text field accesses keyboard inputs and put them into itself.
 * At begining, the first newed Focusable will be on focus.
 * To swith focus to other Focusable ViewContainers, call the method "switchFocus".
 * "switchFocus" switches the focus on the specified level to a peer of the current Focusable ViewContainer at the specified level.
 * When a Focusable ViewContainer becomes the focus, its method "onEnterFocus" will be invoked;
 * When a Focusable ViewContainer becomes no more the focus, its method "onExitFocus" will be invoked.
 */
class Focusable : public ViewContainer
{
  private:
    int focusLevel;

    bool focused;

    vector<Focusable*>* peers;

    Focusable* currentFocusedSubFocusable;

    Focusable* parent;

  public:
    constructor(Focusable* peer, char placeholder);

    constructor(char placeholder, Focusable* parent);

    virtual Focusable* switchFocus(int focusLevel);

    virtual void onEnterFocus();

    virtual void onExitFocus();

    virtual NotificationDict handleInput(const ProcessedKeyInput& key_input) = 0;

    ~constructor();
};