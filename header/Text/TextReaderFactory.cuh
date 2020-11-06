#ifndef GPU_KARP_RABIN_TEXTREADERFACTORY_CUH
#define GPU_KARP_RABIN_TEXTREADERFACTORY_CUH

#include <memory>
#include "Reader.cuh"

class TextReaderFactory
{
public:
    TextReaderFactory() = default;
    static std::unique_ptr<Reader> forText(const std::string& text);
};

#endif //GPU_KARP_RABIN_TEXTREADERFACTORY_CUH
