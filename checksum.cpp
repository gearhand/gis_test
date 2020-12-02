
#include "checksum.h"
#include <fstream>
#include <cstring>
#include <netinet/in.h> // TODO: seems not portable
#include <iostream>

uint64_t ChecksumMode::process(std::istream& input) {
    // process checksum
    //std::ifstream file (filename, std::ios::in | std::ios::binary);
    char buffer[4];
    auto size = sizeof buffer;
    std::memset(buffer, 0, size);
    std::streamsize chars_read = 0;
    uint64_t checksum = 0;
    while (chars_read = input.readsome(buffer, size), chars_read == size) {
        std::cout << "Chars read in cycle: " << chars_read << std::endl;
        checksum += ntohl(*reinterpret_cast<uint32_t const*>(buffer));
    }
    if (chars_read > 0) {
        std::cout << "Chars read after cycle: " << chars_read << std::endl;
        std::memset(buffer + chars_read, 0 , size - chars_read);
        checksum += ntohl(*reinterpret_cast<uint32_t const*>(buffer));
    }
    //std::cout << std::hex << "0x" << checksum << std::dec << " : " << checksum << std::endl;
    return checksum;
}
