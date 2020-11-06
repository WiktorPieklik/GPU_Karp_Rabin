#ifndef GPU_KARP_RABIN_HASH_H
#define GPU_KARP_RABIN_HASH_H

#include <string_view>
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
    int base{2}; //counting system BASE (e.g binary system BASE=2)
public:
    Hash& forBase(int base);
    virtual long long getPolyValue(std::string_view pattern) = 0;
    virtual std::tuple<long long, long long> getPolyValues(std::string_view pattern1, std::string_view pattern2) = 0;
};
#endif //GPU_KARP_RABIN_HASH_H
