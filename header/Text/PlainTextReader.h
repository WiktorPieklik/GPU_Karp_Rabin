#ifndef GPU_KARP_RABIN_PLAINTEXTREADER_H
#define GPU_KARP_RABIN_PLAINTEXTREADER_H

#include "Reader.h"

class PlainTextReader: public Reader
{
public:
    explicit PlainTextReader(const std::string& text);
    std::vector<std::string> read() override;
};

#endif //GPU_KARP_RABIN_PLAINTEXTREADER_H
