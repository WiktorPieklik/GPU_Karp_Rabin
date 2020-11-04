#include "Hash.h"

Hash& Hash::forBase(const int& base)
{
    this->base = base;

    return *this;
}
