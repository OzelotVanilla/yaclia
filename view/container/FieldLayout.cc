#include "FieldLayout.h"


FieldLayout::constructor()
{
    delegate(FieldLayoutDirection::vertical);
}


FieldLayout::constructor(FieldLayoutDirection d)
{
    this->direction = d;
}
