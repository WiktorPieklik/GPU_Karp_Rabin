//
// Created by Wiktor Pieklik on 16/10/2020.
//

#include "../header/Hash.h"

Hash& Hash::forBase(const int& base)
{
    this->base = base;

    return *this;
}
