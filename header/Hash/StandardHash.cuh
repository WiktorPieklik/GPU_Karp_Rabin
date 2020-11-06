#ifndef GPU_KARP_RABIN_STANDARDHASH_H
#define GPU_KARP_RABIN_STANDARDHASH_H

#include "Hash.cuh"

class StandardHash: public Hash {
public:
    long long  getPolyValue(std::string_view pattern) override;
    std::tuple<long long, long long> getPolyValues(std::string_view pattern1, std::string_view pattern2) override;
};

#endif //GPU_KARP_RABIN_STANDARDHASH_H
