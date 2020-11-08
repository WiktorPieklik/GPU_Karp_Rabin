#ifndef GPU_KARP_RABIN_TEXTSPLITTER_H
#define GPU_KARP_RABIN_TEXTSPLITTER_H

#include <vector>

class TextSplitter {

private:
    static const int numOfThreads = 32;

    static size_t numOfWindows(size_t textLength, size_t patternLength);
    static std::pair<size_t, size_t> lenOfChains(size_t numOfWindows);
public:
    static std::vector<std::pair<size_t, size_t>> splitText(size_t textLength, size_t patternLength);

};


#endif //GPU_KARP_RABIN_TEXTSPLITTER_H
