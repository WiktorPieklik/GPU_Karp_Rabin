#include <iostream>
#include "Hash/StandardHash.h"
#include "main/header/RabinKarpSearch.h"
#include "Text/FileNotFoundException.h"

int main()
{
    try
    {
        auto textProcessor = RabinKarpSearch<StandardHash>("../test.txt", "ipsum");
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
