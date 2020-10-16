//
// Created by Wiktor Pieklik on 16/10/2020.
//

#ifndef GPU_KARP_RABIN_RABINKARPSEARCH_H
#define GPU_KARP_RABIN_RABINKARPSEARCH_H

#include "Hash.h"
#include "Reader.h"
#include "TextReaderFactory.h"

template <typename Hash>
class RabinKarpSearch
{
private:
    const std::string file;
    const std::string pattern;
    const int prime = 23;
    const int base = 36; //input alphabet's length

    int calculateHash();
    int calculateRollingHash();
    Reader readText();

public:
    RabinKarpSearch(std::string file, std::string pattern);
    std::vector<int> search();

};


#endif //GPU_KARP_RABIN_RABINKARPSEARCH_H
