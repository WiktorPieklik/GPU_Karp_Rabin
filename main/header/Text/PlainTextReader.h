#ifndef GPU_KARP_RABIN_PLAINTEXTREADER_H
#define GPU_KARP_RABIN_PLAINTEXTREADER_H

#include "Reader.h"

class PlainTextReader: public Reader
{
private:
    std::string text;
public:
    explicit PlainTextReader(std::string text);
    std::string read() override;
};

#endif //GPU_KARP_RABIN_PLAINTEXTREADER_H
