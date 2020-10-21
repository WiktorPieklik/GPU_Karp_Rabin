#include <iostream>
#include "Hash/StandardHash.h"
#include "header/RabinKarpSearch.h"
#include "Text/FileNotFoundException.h"

int main()
{
    try
    {
        auto textProcessor = RabinKarpSearch<StandardHash>("../test.txt", "ipsum");
        std::vector<int> matches = textProcessor.search();

        for (const int &i : matches) {
            std::cout << i << std::endl;
        }
    }
    catch(FileNotFoundException &e)
    {
        std::cout<< e.what()<<std::endl;
    }

    return 0;
}
