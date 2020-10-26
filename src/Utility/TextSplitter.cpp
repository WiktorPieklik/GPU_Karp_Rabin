#include "TextSplitter.h"

size_t TextSplitter::numOfWindows(size_t textLength, int patternLength) {
    return textLength - patternLength + 1;
}

std::pair<int, int> TextSplitter::lenOfChain(int numOfWindows) {
    int rangeWidth = numOfWindows / numOfThreads;
    int rangesWithBonus = numOfWindows % numOfThreads;
    return std::make_pair(rangeWidth, rangesWithBonus);
}

std::vector<std::pair<size_t, size_t>> TextSplitter::splitText(long long int textLength, int patternLength) {
    std::vector<std::pair<size_t, size_t>> ranges;
    int _numOfWindows = numOfWindows(textLength, patternLength);
    std::pair<int, int> chains = lenOfChain(_numOfWindows);
    int currenPosition = 0;
    for(int i = 0; i < numOfThreads; i++) {
        if(_numOfWindows > i) {
            if (chains.second > 0) {
                ranges.emplace_back(std::make_pair(currenPosition, currenPosition + chains.first));
                currenPosition = currenPosition + chains.first + 1;
                chains.second--;
            } else {
                ranges.emplace_back(std::make_pair(currenPosition, currenPosition + chains.first - 1));
                currenPosition = currenPosition + chains.first;
            }
        } else {
            break;
        }
    }
    return std::move(ranges);
}
