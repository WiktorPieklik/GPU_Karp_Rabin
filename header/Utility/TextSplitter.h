#ifndef GPU_KARP_RABIN_TEXTSPLITTER_H
#define GPU_KARP_RABIN_TEXTSPLITTER_H

#include <cmath>
#include <vector>

class TextSplitter {

private:
    static const int numOfThreads = 32;

    size_t numOfWindows(size_t textLength, int patternLength);
    std::pair<int, int> lenOfChain(int numOfWindows);
public:
    std::vector<std::pair<size_t, size_t>> splitText(long long int textLength, int patternLength);

};


#endif //GPU_KARP_RABIN_TEXTSPLITTER_H
