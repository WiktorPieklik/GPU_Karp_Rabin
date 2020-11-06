#include "TextSplitter.cuh"

size_t TextSplitter::numOfWindows(size_t textLength, size_t patternLength) {
    return textLength - patternLength + 1;
}

std::pair<size_t, size_t> TextSplitter::lenOfChains(size_t numOfWindows) {
    auto rangeWidth = numOfWindows / numOfThreads;
    auto rangesWithBonus = numOfWindows % numOfThreads;
    return std::make_pair(rangeWidth, rangesWithBonus);
}

// splitText method returns vector of std::pair where pair.first describes first index of first window and pair.second
// describes first index of last window. When number of windows returned from numOfWindows method is greater
// or equal than value of numOfThreads variable, it returns exactly numOfThreads pairs and when value returned from numOfWindows
// is lesser than numOfThreads it returns exactly numOfWindows pairs.
[[maybe_unused]] std::vector<std::pair<size_t, size_t>> TextSplitter::splitText(size_t textLength, size_t patternLength) {
    std::vector<std::pair<size_t, size_t>> ranges;
    size_t numberOfWindows = numOfWindows(textLength, patternLength);
    std::pair<size_t, size_t> chainsLength = lenOfChains(numberOfWindows);
    size_t currentPosition = 0;
    size_t i = 0;
    while(i < numOfThreads && numberOfWindows > i) {
            if (chainsLength.second > 0) {
                ranges.emplace_back(std::make_pair(currentPosition, currentPosition + chainsLength.first));
                currentPosition = currentPosition + chainsLength.first + 1;
                chainsLength.second--;
            } else {
                ranges.emplace_back(std::make_pair(currentPosition, currentPosition + chainsLength.first - 1));
                currentPosition = currentPosition + chainsLength.first;
            }
        i++;
    }
    return ranges;
}
