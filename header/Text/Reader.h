#ifndef GPU_KARP_RABIN_READER_H
#define GPU_KARP_RABIN_READER_H

#include <vector>
#include <string>

class Reader
{
protected:
    std::vector<std::string> textVector;
public:
    explicit Reader(const std::string& text){};
    virtual std::vector<std::string>& read() = 0;
    virtual ~Reader() = default;
};

#endif //GPU_KARP_RABIN_READER_H
