//
// Created by dawid on 23.10.2020.
//

#ifndef GPU_KARP_RABIN_TEXTSPLITTER_H
#define GPU_KARP_RABIN_TEXTSPLITTER_H

#include <cmath>
#include <tuple>
#include <vector>

class TextSplitter {

private:
    std::vector<std::tuple<long long int, long long int>> ranges;
    static const int numOfThreads = 32;

    int rangeWidth(long long int textLength);
public:
    std::vector<std::tuple<long long int, long long int>>& splitText(long long int textLength, int patternLength);

};


#endif //GPU_KARP_RABIN_TEXTSPLITTER_H
