//
// Created by igor on 02.12.2020.
//

#include "arguments.h"
#include "checksum.h"
#include "words.h"
#include <fstream>

Arguments::Arguments()
    : parser ("This is program for 2GIS test")
    , mode (
        "m"
        , "mode"
        , "Operation mode, one of <words|checksum>" // TODO: make automatic
        , true
        , ""
        , "mode"
        , parser
    )
    , filename (
        "f"
        , "filename"
        , "File to process"
        , true
        , ""
        , "filename"
        , parser
    )
    , needle_arg (
        "w"
        , "word"
        , "Substring to count"
        , false
        , ""
        , "substr"
        , parser
    )
    , case_insensitive (
        "i"
        , "insensitive"
        , "Set this flag, if you need case insensitive search"
        , parser
    )
{
    modes.emplace("words", &Arguments::process_words);
    modes.emplace("checksum", &Arguments::process_checksum);
}

void Arguments::process(int argc, char** argv) {
    parser.parse(argc, argv);
    auto const& mode_name = mode.getValue();
    auto mode_key = modes.find(mode_name);
    if (mode_key != modes.end()) {
        std::invoke(mode_key->second, this);
    }
    else {
        std::cout << "No valid mode was provided, exiting." << std::endl;
    }
}

void Arguments::process_checksum() {
    if (filename.getValue() == "-") {
        auto checksum = ChecksumMode::process(std::cin);
        std::cout << std::hex << "0x" << checksum << std::dec << " : " << checksum << std::endl;
    }
    else if (auto file = std::ifstream (filename.getValue()); file.is_open()) {
        auto checksum = ChecksumMode::process(file);
        std::cout << std::hex << "0x" << checksum << std::dec << " : " << checksum << std::endl;
    }
    else {
        std::cout << "File " << filename.getValue() << " does not exists" << std::endl;
    }
}

void Arguments::process_words() {
    auto& needle = needle_arg.getValue();
    if (filename.getValue() == "-") {
        auto counter = WordsMode::process(std::cin, needle, case_insensitive.getValue());
        std::cout << "File contains " << counter << " substrings \"" << needle << '\"' << std::endl;
    }
    else if (auto file = std::ifstream (filename.getValue()); file.is_open()) {
        auto counter = WordsMode::process(file, needle, case_insensitive.getValue());
        std::cout << "File contains " << counter << " substrings \"" << needle << '\"' << std::endl;
    }
    else {
        std::cout << "File " << filename.getValue() << " does not exists" << std::endl;
    }
}
