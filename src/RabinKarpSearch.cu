#include "RabinKarpSearch.cuh"
#include "StandardHash.cuh"

#include <tuple>
#include "stdio.h"
#include <iostream>

namespace {
    constexpr auto PRIME = 23;
    constexpr auto BASE = 36; //input alphabet's length
}

RabinKarpSearch::RabinKarpSearch(std::string file, std::string pattern, std::unique_ptr<Hash> hash, std::unique_ptr<TextSplitter> textSplitter): file(std::move(file)), pattern(std::move(pattern)), hash(std::move(hash)), textSplitter(std::move(textSplitter))
{
    init();
    initGPU();
}

RabinKarpSearch::~RabinKarpSearch() {
    cudaFree(umRanges);
    cudaFree(umText);
    cudaFree(umPattern);
}

void RabinKarpSearch::init()
{
    reader = TextReaderFactory::forText(file);
    if(!reader)
        throw std::runtime_error("Couldn't create a reader!");
    text = reader->read();
    calculateHashes();
    for(size_t i = 1; i < pattern.length(); ++i)
    {
        mostSignificantWeight *= BASE;
    }
}

void RabinKarpSearch::initGPU() {
    // Allocate unified memory for ranges
    std::vector<std::pair<size_t, size_t>> ranges = textSplitter->splitText(text.length(), pattern.length());
    cudaMallocManaged(&umRanges, ranges.size() * sizeof(std::pair<int, int>));
    for(int i = 0; i < ranges.size(); i++) {
        umRanges[i] = std::make_pair(ranges[i].first, ranges[i].second);
    }

    // Allocate unified memory for text
    cudaMallocManaged(&umText, text.length() * sizeof(char));
    for(int i = 0; i < text.length(); i++) {
        umText[i] = text[i];
    }

    // Allocate unified memory for pattern
    cudaMallocManaged(&umPattern, pattern.length() * sizeof(char));
    for(int i = 0; i < pattern.length(); i++) {
        umPattern[i] = pattern[i];
    }
}

void RabinKarpSearch::calculateHashes()
{
    if(!hash)
        throw std::runtime_error("Hash not initialized.");

    std::tuple<long long, long long> hashes = hash
            ->forBase(BASE)
            .getPolyValues(pattern, text.substr(currentWindowPosition, pattern.length()));
    patternHash = std::get<0>(hashes) % PRIME;
    windowHash = std::get<1>(hashes) % PRIME;
}

void RabinKarpSearch::calculateRollingHash()
{
    windowHash = (windowHash - mostSignificantWeight * text[currentWindowPosition - 1]) * BASE + text[currentWindowPosition + pattern.length() - 1];
    windowHash = windowHash % PRIME;

    if(windowHash < 0)
    {
        windowHash = windowHash + PRIME;
    }
}

void RabinKarpSearch::moveWindow()
{
    ++currentWindowPosition;
}

std::vector<size_t> RabinKarpSearch::search()
{
    std::vector<size_t> matches;
    auto windows_count = text.length() - pattern.length();
    while(currentWindowPosition <= windows_count)
    {
        if(windowHash == patternHash)
        {
            if(pattern == text.substr(currentWindowPosition, pattern.length()))
            {
                //match found
                matches.push_back(currentWindowPosition);
            }
        }
        moveWindow();
        calculateRollingHash();
    }
    return matches;
}

__device__ bool RabinKarpSearch::compareCharArrays(const char *first, const char *second, int length) {
    int currentChar = 0;
    while(currentChar < length) {
        if(first[currentChar] != second[currentChar]) {
            return false;
        }
        return true;
    }
}

__global__ void searchForMatches(std::pair<int, int>* ranges, char* text, char* pattern) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    for(int i = ranges[idx].first; i <= ranges[idx].first; i++) {
        char* buff;

        free(buff);
    }
}

std::vector<size_t> RabinKarpSearch::searchGPU()
{
    searchForMatches<<<1, 32>>>(umRanges, umText, umPattern);
    cudaDeviceSynchronize();
}