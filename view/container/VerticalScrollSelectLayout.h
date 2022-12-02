#pragma once

#include "../../head.h"
#include "Layout.h"

#ifdef constructor
#undef constructor
#endif

#define constructor VerticalScrollSelectLayout

class VerticalScrollSelectLayout : public Layout
{
};