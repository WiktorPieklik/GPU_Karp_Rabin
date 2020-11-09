#include <iostream>
#include "Hash/StandardHash.cuh"
#include "header/RabinKarpSearch.cuh"
#include "Text/FileNotFoundException.cuh"

// Function that takes two char arrays and compares them
__host__ __device__ bool compareCharArrays(const char *first, const char *second, int length) {
    int currentChar = 0;
    while(currentChar < length) {
        if(first[currentChar] != second[currentChar]) {
            return false;
        }
        currentChar++;
    }
    return true;

}

// GPU karp rabin search
__global__ void searchForMatches(std::pair<int, int>* ranges, char* text, char* pattern) {\
    // Calculate unique index of a thread
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    for(int i = ranges[idx].first; i <= ranges[idx].second; i++) {
        char* substr = (char*)malloc(6 * sizeof(char));
        memcpy(substr, &text[i], 5);
        substr[6] = '\0';
        if(compareCharArrays(pattern, substr, 6)) {
            printf("%s %d\n", substr, i);
        }
        free(substr);
    }
}

int main()
{
    // Unified memory
    std::pair<int, int>* umRanges;
    char* umPattern;
    char* umText;

    // Create TextSplitter object
    TextSplitter textSplitter = TextSplitter();
    auto textProcessor = RabinKarpSearch("../test.txt", "lorem", std::make_unique<StandardHash>());
    std::vector<size_t> matchess = textProcessor.search();
    for (auto i : matchess) {
        std::cout << i << std::endl;
    }
    std::vector<size_t> matches = textProcessor.search();
    std::string text = textProcessor.getText();
    std::string pattern = textProcessor.getPattern();

    // Allocate unified memory for ranges
    std::vector<std::pair<size_t, size_t>> ranges = textSplitter.splitText(text.length(), pattern.length());
    cudaMallocManaged(&umRanges, ranges.size() * sizeof(std::pair<int, int>));
    for(int i = 0; i < ranges.size(); i++) {
        umRanges[i] = std::make_pair(ranges[i].first, ranges[i].second);
    }

    // Allocate unified memory for text
    umText = new char[text.length() * sizeof(char)];
    cudaMallocManaged(&umText, text.length() * sizeof(char));
    for(int i = 0; i < text.length(); i++) {
        umText[i] = text[i];
    }

    // Allocate unified memory for pattern
    cudaMallocManaged(&umPattern, pattern.length() * sizeof(char));
    for(int i = 0; i < pattern.length(); i++) {
        umPattern[i] = pattern[i];
    }

    // Set heap size (128mb). It's a random size, probably much to big :D
    cudaDeviceSetLimit(cudaLimitMallocHeapSize, 128*1024*1024);

    // Invoke kernel function
    searchForMatches<<<1, 32>>>(umRanges, umText, umPattern);

    // Make CPU wait for kernel to finish before go further
    cudaDeviceSynchronize();

    // Free the allocated resources
    cudaFree(umRanges);
    cudaFree(umText);
    cudaFree(umPattern);

    return 0;
}
