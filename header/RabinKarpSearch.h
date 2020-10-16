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
    const std::string& file;
    const std::string& pattern;
    std::vector<std::string> text;

    int patternHash;
    int tmpHash; //moving window's hash
    int currentWindowPosition = 0; //starting index
    int index = 0;
    const int prime = 23;
    const int base = 36; //input alphabet's length

    void calculateHashes();
    void init();
    void moveWindow();
    int calculateRollingHash();
    int calculateHash(const std::string& text);
    int getWindowEnd();
    std::vector<std::string>& readText();

public:
    RabinKarpSearch(const std::string& file, const std::string& pattern);
    std::vector<int> search();

};


#endif //GPU_KARP_RABIN_RABINKARPSEARCH_H
