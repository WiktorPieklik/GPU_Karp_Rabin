#ifndef GPU_KARP_RABIN_TEXTSPLITTER_H
#define GPU_KARP_RABIN_TEXTSPLITTER_H

#include <cmath>
#include <tuple>
#include <vector>

class TextSplitter {

private:
    static const int numOfThreads = 32;

    int numOfWindows(long long int textLength, int patternLength);
    std::pair<int, int> lenOfChain(int windows);
public:
    std::vector<std::tuple<size_t, size_t>> splitText(long long int textLength, int patternLength);

};


#endif //GPU_KARP_RABIN_TEXTSPLITTER_H
