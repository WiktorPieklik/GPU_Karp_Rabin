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
    std::unique_ptr<TextSplitter> textSplitter;

    // Unified memory
    std::pair<int, int>* umRanges;
    char* umPattern;
    char* umText;

    long long patternHash{};
    long long windowHash{}; //moving window's hash
    size_t currentWindowPosition = 0;

    long long  mostSignificantWeight = 1;

    void calculateHashes();
    void init();
    void initGPU();
    void moveWindow();
    void calculateRollingHash();
    __device__ bool compareCharArrays(const char* first, const char* second, int length);

        public:
    RabinKarpSearch(std::string file, std::string pattern, std::unique_ptr<Hash> hash, std::unique_ptr<TextSplitter> textSplitter);
    ~RabinKarpSearch();
    std::vector<size_t> search();
    std::vector<size_t> searchGPU();
};


#endif //GPU_KARP_RABIN_RABINKARPSEARCH_CUH
