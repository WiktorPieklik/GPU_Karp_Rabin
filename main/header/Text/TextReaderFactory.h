#ifndef GPU_KARP_RABIN_TEXTREADERFACTORY_H
#define GPU_KARP_RABIN_TEXTREADERFACTORY_H

#include <memory>
#include "Reader.h"

class TextReaderFactory
{
public:
    TextReaderFactory() = default;
    static std::unique_ptr<Reader> forText(const std::string& text);
};

#endif //GPU_KARP_RABIN_TEXTREADERFACTORY_H
