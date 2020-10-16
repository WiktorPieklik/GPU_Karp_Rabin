//
// Created by Wiktor Pieklik on 16/10/2020.
//

#include "../header/Hash.h"

Hash& Hash::forX(const int& x)
{
    this->x = x;

    return *this;
}
