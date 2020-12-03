#pragma once

#include <tclap/ValueArg.h>
#include <tclap/CmdLineInterface.h>

/**
 * Counts checksum for input
 * Treats each 4-byte sequence as big-endian
 */
class ChecksumMode {
public:
    ChecksumMode() = default;
    //~ChecksumMode() = default;
    static uint64_t process(std::istream& input);
};
