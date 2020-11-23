#include "RabinKarpSearchGPU.cuh"

#include "Utility/TextSplitter.cuh"
#include "Text/TextFileReader.cuh"

#include "thrust/device_vector.h"

namespace {
    constexpr auto PRIME = 23;
    constexpr auto BASE = 36; //input alphabet's length
}

// Unified memory
std::pair<int, int>* umRanges;
int* umMatches;
char* umPattern;
char* umText;

// Variables
TextFileReader reader = TextFileReader("../test.txt");
std::string text = reader.read();
std::string pattern = "lorem";
int mostSignificantWeight = 1;
TextSplitter textSplitter = TextSplitter();
std::vector<std::pair<size_t, size_t>> ranges = textSplitter.splitText(text.length(), pattern.length());

// Allocate needed resources in unified memory
__host__ void initUnifiedMemory() {
    // Calculate most significant weight
    for(size_t i = 1; i < pattern.length(); ++i)
    {
        mostSignificantWeight *= BASE;
    }

    // Allocate unified memory for matches
    cudaMallocManaged(&umMatches, (text.size() - pattern.length() + 1) * sizeof(int));
    for(int i = 0; i < (text.size() - pattern.length() + 1); i++) {
        umMatches[i] = 0;
    }

    // Allocate unified memory for ranges
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

__host__ __device__ long long getPolyValue(char* pattern, int pos, int len)
{
    long long result = static_cast<int>(pattern[pos]);
    for(size_t i = pos + 1; i < pos + len; ++i)
    {
        result = result * BASE + static_cast<int>(pattern[i]);
    }

    return result % PRIME;
}

__device__ long long calculateRollingHash(long long mostSignificantWeight, char* text, long long windowHash, int currentPos, int patternLen)
{
    long long hash = (windowHash - mostSignificantWeight * text[currentPos - 1]) * BASE + text[currentPos + patternLen - 1];
    hash = hash % PRIME;

    if(hash >= 0) {
        return hash;
    } else {
        return hash + PRIME;
    }
}

// Function that takes two char arrays and compares them
__device__ bool compareCharArrays(const char *first, const char *second, int pos, int length) {
    int currentChar = 0;
    while(currentChar < length) {
        if(first[currentChar] != second[pos + currentChar]) {
            return false;
        }
        currentChar++;
    }
    return true;
}

// GPU karp rabin search
__global__ void search(std::pair<int, int>* ranges, int* matches, char* text, char* pattern, int patternLen, long long patternHash, int mostSignificantWeight) {
    // Calculate unique index of a thread
    int threadId = blockIdx.x * blockDim.x + threadIdx.x;

    // Variable for storing hash of the window
    long long windowHash;

    for(int i = ranges[threadId].first; i <= ranges[threadId].second; i++) {
        // Hash of first window
        if (i == ranges[threadId].first) {
            windowHash = getPolyValue(text, i, patternLen);
        }
        else {
            windowHash = calculateRollingHash(mostSignificantWeight, text, windowHash, i, patternLen);
        }

        if(windowHash == patternHash) {
            if (compareCharArrays(pattern, text, i, patternLen)) {
                matches[i]++;
            }
        }
    }
}

__host__ void printMatches() {
    for(int i = 0; i < (text.size() - pattern.length() + 1); i++) {
        // Print only indexes of matches
        if(umMatches[i] == 1) {
            std::cout<< i <<std::endl;
        }
    }
}

// Wrapper of kernel function to make it possible to use it with benchmark class
__host__ void searchWrapper() {
    // Calculate pattern hash value
    long long patternHash = getPolyValue(umPattern, 0, pattern.length());

    // Invoke kernel function
    search<<<1, 32>>>(umRanges, umMatches, umText, umPattern, pattern.length(), patternHash, mostSignificantWeight);

    // Make CPU wait for kernel to finish before go further
    cudaDeviceSynchronize();
}

// Free the allocated resources
__host__ void freeUnifiedMemory() {
    cudaFree(umRanges);
    cudaFree(umText);
    cudaFree(umPattern);
}
