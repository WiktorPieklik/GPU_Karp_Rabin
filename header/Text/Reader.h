#ifndef GPU_KARP_RABIN_READER_H
#define GPU_KARP_RABIN_READER_H

#include <vector>
#include <string>

class Reader
{
protected:
    std::vector<std::string> textVector;
public:
    virtual std::vector<std::string> read() = 0;

};

#endif //GPU_KARP_RABIN_READER_H
