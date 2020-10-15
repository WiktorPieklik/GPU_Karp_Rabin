#include <iostream>
#include "header/TextReaderFactory.h"
#include "header/Reader.h"

int main()
{
    Reader* reader = TextReaderFactory::forText("../test.txt");
    for(const std::string& text : reader->read())
    {
        std::cout << text << std::endl;
    }

    return 0;
}
