//
// Created by Wiktor Pieklik on 16/10/2020.
//

#ifndef GPU_KARP_RABIN_HASH_H
#define GPU_KARP_RABIN_HASH_H

#include <vector>
#include <string>
#include <tuple>

/**
 * Base class for any hashing related class.
 * Used in RabinKarpSearch class.
 *
 * @see RabinKarpSearch
 */
class Hash
{
protected:
    int base; //counting system base (e.g binary system base=2)
public:
    Hash() = default;
    Hash& forBase(const int& base);
    virtual long long int getPolyValue(const std::string& pattern) = 0;
    virtual std::tuple<long long int, long long int> getPolyValues(const std::string& pattern1, const std::string& pattern2) = 0;
};
#endif //GPU_KARP_RABIN_HASH_H
