#include "Hash.cuh"

Hash& Hash::forBase(int base)
{
    this->base = base;

    return *this;
}
