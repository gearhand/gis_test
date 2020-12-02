#pragma once

#include <tclap/ValueArg.h>
#include <tclap/CmdLineInterface.h>

class ChecksumMode {
public:
    ChecksumMode() = default;
    //~ChecksumMode() = default;
    static uint64_t process(std::istream& input);
};
