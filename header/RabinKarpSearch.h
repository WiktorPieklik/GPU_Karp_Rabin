#ifndef GPU_KARP_RABIN_RABINKARPSEARCH_H
#define GPU_KARP_RABIN_RABINKARPSEARCH_H

#include "Hash/Hash.h"
#include "Text/Reader.h"
#include "Text/TextReaderFactory.h"

template <typename Hash>
class RabinKarpSearch
{
private:
    const std::string& file;
    const std::string& pattern;
    std::vector<std::string> text;

    std::vector<int> matches;
    long long int patternHash;
    long long int windowHash; //moving window's hash
    int currentWindowPosition = 0; //starting lineNo
    int lineNo = 0; //line's number in input file (file is read line by line)
    const int prime = 23;
    const int base = 36; //input alphabet's length
    long long int mostSignificantWeight = 1;

    void calculateHashes();
    void init();
    void moveWindow();
    void calculateRollingHash();
    long long int calculateHash(const std::string& text);
    std::vector<std::string>& readText();

public:
    RabinKarpSearch(const std::string& file, const std::string& pattern);
    std::vector<int> search();

};


#endif //GPU_KARP_RABIN_RABINKARPSEARCH_H
