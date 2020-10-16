//
// Created by Wiktor Pieklik on 16/10/2020.
//

#include "../header/StandardHash.h"

int StandardHash::getPolyValue(const std::vector<int> &coefficients)
{
    int result = coefficients[0];
    for(size_t i = 1; i<coefficients.size(); ++i)
    {
        result = result * this->x + coefficients[i];
    }

    return result;
}
