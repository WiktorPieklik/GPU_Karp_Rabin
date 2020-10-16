//
// Created by Wiktor Pieklik on 16/10/2020.
//

#include "../header/StandardHash.h"

int StandardHash::getPolyValue(const std::string& pattern)
{
    int result = (int)pattern[0];
    for(size_t i = 1; i<pattern.size(); ++i)
    {
        result = result * this->base + (int)pattern[i];
    }

    return result;
}

/**
 * Return hash values for given patterns (in given order).
 * Patterns are considered to be the same length.
 *
 * @param pattern1
 * @param pattern2
 *
 * @return int[]
 */
int * StandardHash::getPolyValues(const std::string &pattern1, const std::string &pattern2)
{
    int result1 = (int)pattern1[0];
    int result2 = (int)pattern2[0];

    for(size_t i = 1; i < pattern1.size(); ++i)
    {
        result1 = result1 * this->base + pattern1[i];
        result2 = result2 * this->base + pattern2[i];
    }

    return new int[]{result1, result2};
}
