#pragma once

#include "../../head.h"
#include "ViewContainer.h"

#ifdef constructor
#undef constructor
#endif

#define constructor Layout

class Field : public ViewContainer
{
};