#ifndef GPU_KARP_RABIN_TEXTFILEREADER_H
#define GPU_KARP_RABIN_TEXTFILEREADER_H

#include "Reader.cuh"
#include <filesystem>

class TextFileReader: public Reader
{
private:
    std::filesystem::path file_path;
public:
    explicit TextFileReader(std::filesystem::path  path);
    std::string read() override;
};

#endif //GPU_KARP_RABIN_TEXTFILEREADER_H
