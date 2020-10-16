//
// Created by Wiktor Pieklik on 15/10/2020.
//

#ifndef GPU_KARP_RABIN_FILENOTFOUNDEXCEPTION_H
#define GPU_KARP_RABIN_FILENOTFOUNDEXCEPTION_H

#include <stdexcept>

class FileNotFoundException : public std::runtime_error
{
public:
    FileNotFoundException(const std::string& message) : runtime_error(message){};

};


#endif //GPU_KARP_RABIN_FILENOTFOUNDEXCEPTION_H
