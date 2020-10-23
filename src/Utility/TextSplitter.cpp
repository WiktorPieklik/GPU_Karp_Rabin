//
// Created by dawid on 23.10.2020.
//

#include "TextSplitter.h"

int TextSplitter::rangeWidth(long long int textLength) {
    return ceil((double) textLength / (double) numOfThreads);
}

// It's hard cut the text into substrings of equal size without getting out of range sometimes,
// so when we get out of range a <-1, -1> is pushed back to indicate that this tuple is wrong and thread should not process it

std::vector<std::tuple<long long int, long long int>>& TextSplitter::splitText(long long int textLength, int patternLength) {
    int width = rangeWidth(textLength);

    for(int i = 0; i < textLength; i += width) {
        if((i + patternLength - 1) < textLength && (i + width - 1 + patternLength - 1) < textLength) {
            ranges.push_back(std::make_tuple(i, i + width - 1));
        }
        else if((i + patternLength - 1) < textLength && ((i + width - 1 + patternLength - 1) >= textLength)) {
            ranges.push_back(std::make_tuple(i, textLength - patternLength));
        } else if((i + patternLength - 1) >= textLength) {
            ranges.push_back(std::make_tuple(-1, -1));
        }
    }

    return ranges;
}
