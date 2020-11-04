#include "StandardHash.h"

long long StandardHash::getPolyValue(const std::string& pattern)
{
    long long result = static_cast<int>(pattern[0]);
    for(size_t i = 1; i<pattern.size(); ++i)
    {
        result = result * base + static_cast<int>(pattern[i]);
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
 * @return long long int[]
 */
std::tuple<long long, long long> StandardHash::getPolyValues(const std::string &pattern1, const std::string &pattern2)
{
    long long result1 = static_cast<int>(pattern1[0]);
    long long result2 = static_cast<int>(pattern2[0]);

    for(size_t i = 1; i < pattern1.size(); ++i)
    {
        result1 = result1 * base + pattern1[i];
        result2 = result2 * base + pattern2[i];
    }

    return std::make_tuple(result1, result2);
}
