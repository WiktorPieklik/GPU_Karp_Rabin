#include <iostream>
#include "Hash/StandardHash.cuh"
#include "header/RabinKarpSearch.cuh"
#include "Text/FileNotFoundException.cuh"
#include "header/RabinKarpSearchGPU.cuh"
#include <chrono>
#include <string>

int main()
{
    initUnifiedMemory();
    printf("Plik: %s\n", "benchmark217MB.txt");
    printf("Szukana fraza: %s\n", "ipsum");
    printf("%s\n", "Start");

    searchWrapper();

    printMatches();
    freeUnifiedMemory();
    return 0;
}
