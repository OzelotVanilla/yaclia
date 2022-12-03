#pragma once

#include "../../head.h"

#include "Field.h"

#ifdef constructor
#undef constructor
#endif

#define constructor FieldLayout

enum class FieldLayoutDirection;

class FieldLayout
{
  public:
    FieldLayoutDirection direction;


  public:
    constructor();
    constructor(FieldLayoutDirection d);
};

enum class FieldLayoutDirection
{
    vertical,
    vertical_reverse,
    horizontal,
    horizontal_reverse
};