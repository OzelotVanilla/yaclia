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
  private:
    FieldLayoutDirection direction;

    vector<Field*>* fields;

    vector<FieldLayout>* sub_layouts;

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