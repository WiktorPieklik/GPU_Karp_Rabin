#include <iostream>
#include "header/StandardHash.h"
#include "header/RabinKarpSearch.h"
#include "header/FileNotFoundException.h"

int main()
{
    try
    {
        RabinKarpSearch<StandardHash> textProcessor = RabinKarpSearch<StandardHash>("../small_test.txt", "Jesteś");
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
