#ifndef GPU_KARP_RABIN_RABINKARPSEARCH_CUH
#define GPU_KARP_RABIN_RABINKARPSEARCH_CUH

#include "Hash/Hash.cuh"
#include "Text/Reader.cuh"
#include "Text/TextReaderFactory.cuh"
#include "Utility/TextSplitter.cuh"

#include <vector>

class RabinKarpSearch
{
private:
    std::string file;
    std::string pattern;
    std::string text;

    std::unique_ptr<Reader> reader;
    std::unique_ptr<Hash> hash;

    long long patternHash{};
    long long windowHash{}; //moving window's hash
    size_t currentWindowPosition = 0;

    long long  mostSignificantWeight = 1;

    void calculateHashes();
    void init();
    void moveWindow();
    void calculateRollingHash();

public:
    RabinKarpSearch(std::string file, std::string pattern, std::unique_ptr<Hash> hash);
    std::vector<size_t> search();
};


#endif //GPU_KARP_RABIN_RABINKARPSEARCH_CUH
