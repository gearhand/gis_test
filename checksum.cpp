
#include "checksum.h"
#include <cstring>
#ifdef __WIN64__
#include <winsock.h>
#elif __linux__
#include <netinet/in.h>
#endif
#include <iostream>

uint64_t ChecksumMode::process(std::istream& input) {
    char buffer[4];
    auto size = sizeof buffer;
    std::memset(buffer, 0, size);
    std::streamsize chars_read = 0;
    uint64_t checksum = 0;
    while (input.read(buffer, size), chars_read = input.gcount(), chars_read == size) {
        //std::cout << "Chars read in cycle: " << chars_read << std::endl;
        checksum += ntohl(*reinterpret_cast<uint32_t const*>(buffer));
    }
    if (chars_read > 0) {
        //std::cout << "Chars read after cycle: " << chars_read << std::endl;
        std::memset(buffer + chars_read, 0 , size - chars_read);
        checksum += ntohl(*reinterpret_cast<uint32_t const*>(buffer));
    }
    return checksum;
}
