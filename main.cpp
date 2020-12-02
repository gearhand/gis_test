#include <iostream>

#include <tclap/CmdLine.h>
#include <tclap/ValueArg.h>
#include <unordered_map>
#include <fstream>
#include "arguments.h"

//enum class OperationMode {
//    WORDS,
//    CHECKSUM,
//    NONE,
//};

int main(int argc, char** argv) {
    try {
        Arguments arguments;
        arguments.process(argc, argv);
    } catch (TCLAP::ArgException& e) {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
        return -1;
    }
    return 0;
}
