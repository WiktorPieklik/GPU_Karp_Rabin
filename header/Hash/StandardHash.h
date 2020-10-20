#ifndef GPU_KARP_RABIN_STANDARDHASH_H
#define GPU_KARP_RABIN_STANDARDHASH_H

#include "Hash.h"

class StandardHash: public Hash {
public:
    long long int getPolyValue(const std::string& pattern) override;
    long long int* getPolyValues(const std::string& pattern1, const std::string& pattern2) override;
};

#endif //GPU_KARP_RABIN_STANDARDHASH_H
