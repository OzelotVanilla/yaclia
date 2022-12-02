#pragma once

#include "../../head.h"
#include "Field.h"

#ifdef constructor
#undef constructor
#endif

#define constructor VerticalScrollSelectLayout

class VerticalScrollSelectField : public Field
{
  public:
    /* virtual */ void draw();
    /* virtual */ void updateCharView();

  protected:
    vector<string> items;

    size_t num_selected = 0;
};