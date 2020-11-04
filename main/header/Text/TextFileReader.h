#ifndef GPU_KARP_RABIN_TEXTFILEREADER_H
#define GPU_KARP_RABIN_TEXTFILEREADER_H

#include "Reader.h"
#include <fstream>
#include <filesystem>

class TextFileReader: public Reader
{
private:
    std::ifstream file;
public:
    explicit TextFileReader(const std::filesystem::path& path);
    std::vector<std::string> read() override;
};

#endif //GPU_KARP_RABIN_TEXTFILEREADER_H
