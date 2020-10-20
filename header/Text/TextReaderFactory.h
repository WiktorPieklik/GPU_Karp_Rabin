#ifndef GPU_KARP_RABIN_TEXTREADERFACTORY_H
#define GPU_KARP_RABIN_TEXTREADERFACTORY_H

#include <fstream>
#include <sys/stat.h>
#include <regex>
#include "Reader.h"

class TextReaderFactory
{
private:
    static bool fileExists(std::string& text);
    static bool isTxtFile(std::string& text);

public:
    TextReaderFactory() = default;
    static Reader* forText(std::string text);
};

#endif //GPU_KARP_RABIN_TEXTREADERFACTORY_H
