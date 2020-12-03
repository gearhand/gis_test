#pragma once

#include <tclap/ValueArg.h>
#include <tclap/SwitchArg.h>
#include <tclap/CmdLine.h>
#include <unordered_map>
class Arguments {
public:
    Arguments();
    void process(int argc, char** argv);
private:
    void process_words();
    void process_checksum();

    TCLAP::CmdLine parser;
    TCLAP::SwitchArg case_insensitive;
    TCLAP::SwitchArg stand_alone;
    TCLAP::ValueArg<std::string> needle_arg;
    TCLAP::ValueArg<std::string> filename;
    TCLAP::ValueArg<std::string> mode;
    std::unordered_map<std::string, void (Arguments::*)()> modes;
};

