#include "Hash.h"

Hash& Hash::forBase(int base)
{
    this->base = base;

    return *this;
}
