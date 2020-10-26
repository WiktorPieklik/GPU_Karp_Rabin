#include "TextSplitter.h"

size_t TextSplitter::numOfWindows(size_t textLength, int patternLength) {
    return textLength - patternLength + 1;
}

std::pair<size_t, size_t> TextSplitter::lenOfChains(size_t numOfWindows) {
    int rangeWidth = numOfWindows / numOfThreads;
    int rangesWithBonus = numOfWindows % numOfThreads;
    return std::make_pair(rangeWidth, rangesWithBonus);
}

std::vector<std::pair<size_t, size_t>> TextSplitter::splitText(long long int textLength, int patternLength) {
    std::vector<std::pair<size_t, size_t>> ranges;
    int _numOfWindows = numOfWindows(textLength, patternLength);
    std::pair<int, int> _lenOfChains = lenOfChains(_numOfWindows);
    int currentPosition = 0;
    int i =0;
    while(i < numOfThreads && _numOfWindows > i) {
            if (_lenOfChains.second > 0) {
                ranges.emplace_back(std::make_pair(currentPosition, currentPosition + _lenOfChains.first));
                currentPosition = currentPosition + _lenOfChains.first + 1;
                _lenOfChains.second--;
            } else {
                ranges.emplace_back(std::make_pair(currentPosition, currentPosition + _lenOfChains.first - 1));
                currentPosition = currentPosition + _lenOfChains.first;
            }
        i++;
    }
    return std::move(ranges);
}
