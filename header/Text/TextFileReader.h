#ifndef GPU_KARP_RABIN_TEXTFILEREADER_H
#define GPU_KARP_RABIN_TEXTFILEREADER_H

#include "Reader.h"
#include <fstream>

class TextFileReader: public Reader
{
private:
    std::ifstream file;
public:
    explicit TextFileReader(const std::string &text);
    std::vector<std::string>& read();
};

#endif //GPU_KARP_RABIN_TEXTFILEREADER_H
