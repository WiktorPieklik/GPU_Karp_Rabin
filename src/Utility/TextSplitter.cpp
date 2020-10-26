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
    std::pair<int, int> _lenOfChain = lenOfChain(_numOfWindows);
    int currentPosition = 0;
    for(int i = 0; i < numOfThreads; i++) {
        if(_numOfWindows > i) {
            if (_lenOfChain.second > 0) {
                ranges.emplace_back(std::make_pair(currentPosition, currentPosition + _lenOfChain.first));
                currentPosition = currentPosition + _lenOfChain.first + 1;
                _lenOfChain.second--;
            } else {
                ranges.emplace_back(std::make_pair(currentPosition, currentPosition + _lenOfChain.first - 1));
                currentPosition = currentPosition + _lenOfChain.first;
            }
        } else {
            break;
        }
    }
    return std::move(ranges);
}
