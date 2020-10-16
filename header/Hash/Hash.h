//
// Created by Wiktor Pieklik on 16/10/2020.
//

#ifndef GPU_KARP_RABIN_HASH_H
#define GPU_KARP_RABIN_HASH_H

#include <vector>
#include <string>

class Hash
{
protected:
    int base;
public:
    Hash() = default;
    Hash& forBase(const int& base);
    virtual long long int getPolyValue(const std::string& pattern) = 0;
    virtual long long int* getPolyValues(const std::string& pattern1, const std::string& pattern2) = 0;
};
#endif //GPU_KARP_RABIN_HASH_H
