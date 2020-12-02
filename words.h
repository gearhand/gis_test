#pragma once

#include <string>

class WordsMode {
public:
    static uint64_t process(std::istream& input, std::string needle, bool case_insensitive);
};
