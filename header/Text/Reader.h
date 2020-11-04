#ifndef GPU_KARP_RABIN_READER_H
#define GPU_KARP_RABIN_READER_H

#include <string>

class Reader
{
public:
    virtual std::string read() = 0;
};

#endif //GPU_KARP_RABIN_READER_H
