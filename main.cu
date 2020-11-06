#include <iostream>
#include "Hash/StandardHash.cuh"
#include "header/RabinKarpSearch.cuh"
#include "Text/FileNotFoundException.cuh"

int main()
{
    try
    {
        auto textProcessor = RabinKarpSearch("../test.txt", "ipsum", std::make_unique<StandardHash>());
        std::vector<size_t> matches = textProcessor.search();


        for (auto i : matches) {
            std::cout << i << std::endl;
        }
    }
    catch(FileNotFoundException &e)
    {
        std::cout<< e.what()<<std::endl;
    }

    return 0;
}