#include "TextSplitter.h"

int TextSplitter::numOfWindows(long long int textLength, int patternLength) {
    return textLength - patternLength + 1;
}

std::pair<int, int> TextSplitter::lenOfChain(int windows) {
    int rangeWidth = windows / numOfThreads;
    int rangesWithBonus = windows % numOfThreads;
    return std::make_pair(rangeWidth, rangesWithBonus - 1);
}

std::vector<std::pair<size_t, size_t>> TextSplitter::splitText(long long int textLength, int patternLength) {
    std::vector<std::pair<size_t, size_t>> ranges;
    int windows = numOfWindows(textLength, patternLength);
    std::pair<int, int> chains = lenOfChain(windows);
    int currenPosition = 0;
    for(int i = 0; i < numOfThreads; i++) {
        if(windows > i) {
            if (chains.second >= 0) {
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
