//
// Created by Wiktor Pieklik on 16/10/2020.
//

#ifndef GPU_KARP_RABIN_HASH_H
#define GPU_KARP_RABIN_HASH_H

#include <vector>
class Hash
{
protected:
    int x;
public:
    Hash() = default;
    Hash& forX(const int& x);
    virtual int getPolyValue(const std::vector<int>& coefficients) = 0;
};
#endif //GPU_KARP_RABIN_HASH_H
