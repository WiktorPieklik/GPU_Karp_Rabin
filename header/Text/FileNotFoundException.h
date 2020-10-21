#ifndef GPU_KARP_RABIN_FILENOTFOUNDEXCEPTION_H
#define GPU_KARP_RABIN_FILENOTFOUNDEXCEPTION_H

#include <stdexcept>

class FileNotFoundException : public std::runtime_error
{
public:
    explicit FileNotFoundException(const std::string& message) : runtime_error(message){};

};


#endif //GPU_KARP_RABIN_FILENOTFOUNDEXCEPTION_H
