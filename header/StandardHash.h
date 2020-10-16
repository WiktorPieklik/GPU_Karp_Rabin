//
// Created by Wiktor Pieklik on 16/10/2020.
//

#ifndef GPU_KARP_RABIN_STANDARDHASH_H
#define GPU_KARP_RABIN_STANDARDHASH_H

#include "Hash.h"

class StandardHash: public Hash {
public:
    int getPolyValue(const std::string& pattern);
    int* getPolyValues(const std::string& pattern1, const std::string& pattern2);
};

#endif //GPU_KARP_RABIN_STANDARDHASH_H