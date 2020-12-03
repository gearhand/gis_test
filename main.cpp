#include <iostream>

#include <tclap/ArgException.h>
#include "arguments.h"

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
