#ifndef GPU_KARP_RABIN_READER_CUH
#define GPU_KARP_RABIN_READER_CUH

#include <string>

class Reader
{
public:
    virtual std::string read() = 0;
};

#endif //GPU_KARP_RABIN_READER_CUH
