#include "Focusable.h"

Focusable::constructor(Focusable* peer, char placeholder)
{
    if (peer == NULL)
    {
        this->peers = new vector<Focusable*>();
        this->onEnterFocus();
        this->parent     = NULL;
        this->focusLevel = 0;
        this->onEnterFocus();
    }
    else
    {
        this->peers      = peer->peers;
        this->parent     = peer->parent;
        this->focusLevel = peer->focusLevel;
        this->focused    = false;
    }
    this->peers->push_back(this);
}

Focusable::constructor(char placeholder, Focusable* parent)
{
    if ((parent != NULL))
    {
        this->focusLevel = parent->focusLevel + 1;
        if (parent->currentFocusedSubFocusable == NULL)
        {
            parent->currentFocusedSubFocusable = this;
        }
    }
    else
    {
        this->focusLevel = 0;
    }
    this->parent = parent;
    this->peers  = new vector<Focusable*>();
    this->onEnterFocus();
    this->peers->push_back(this);
}

Focusable* Focusable::switchFocus(int focusLevel)
{
    if (focusLevel == this->focusLevel)
    {
        this->onExitFocus();

        Focusable* currentFocused = (*this->peers)[(indexOfFirst(*(this->peers), this) + 1) % this->peers->size()];

        currentFocused->onEnterFocus();

        return currentFocused;
    }
    else
    {
        this->currentFocusedSubFocusable = this->currentFocusedSubFocusable->switchFocus(focusLevel);
        return this;
    }
}

void Focusable::onEnterFocus()
{
    this->focused = true;
}

void Focusable::onExitFocus()
{
    this->focused = false;
}

NotificationDict Focusable::handleInput(const ProcessedKeyInput& key_input)
{
    if (this->currentFocusedSubFocusable != NULL)
    {
        this->currentFocusedSubFocusable->handleInput(key_input);
    }

    // TODO: Did you mean
    return {}; // ?
}

Focusable::~constructor()
{
    if (this->focusLevel != 0)
    {
        vector<Focusable*>* subFocusables = this->peers;

        {
            isize i    = 0;
            isize size = subFocusables->size();

            if (size == 1)
            {
                delete subFocusables;
                this->parent->currentFocusedSubFocusable = NULL;
            }
            else
            {
                if (this->focused)
                {
                    this->switchFocus(this->focusLevel);
                }
            }

            for (; i < size; i++)
            {
                if (this == (*subFocusables)[i])
                {
                    break;
                }
            }

            i++;

            for (; i < size; i++)
            {
                subFocusables[i - 1] = subFocusables[i];
            }

            subFocusables->pop_back();
        }
    }
}