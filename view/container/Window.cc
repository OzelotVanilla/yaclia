#include "Window.h"

/* virtual */ void Window::draw()
{
    // Draw the frame

    // Draw the layout inside
}


/* virtual */ void Window::updateConsoleRelatedInfo()
{
}


void Window::updateCharView()
{
}


Window::constructor()
{
    delegate(40, 20, 1, 1);
}

Window Window::createSized(int width, int height)
{
    return constructor(width, height, 1, 1);
}

Window::constructor(int width, int height, int top_offset, int left_offset)
{
    this->draw_info.position_from_top  = top_offset;
    this->draw_info.position_from_left = left_offset;
    this->draw_info.size_horizontal    = width;
    this->draw_info.size_vertical      = height;
}