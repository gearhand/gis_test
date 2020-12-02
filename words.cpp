#include "words.h"
#include <fstream>
#include <algorithm>
#include <iostream>

uint64_t WordsMode::process(std::istream& input, std::string needle, bool case_insensitive) {
    // process words
    // We can search for a substring, we can search for separate words
    // if substring, we can use boyer-moore-horspool
    if (!needle.empty()) {
        //std::ifstream file (filename, std::ios::in | std::ios::binary);
        //std::string needle = needle_arg.getValue();
        //std::boyer_moore_horspool_searcher searcher (needle.begin(), needle.end());
        auto comparator = case_insensitive ? [] (char lhs, char rhs) -> bool {
                lhs = std::tolower(lhs, std::locale("en_US.UTF-8"));
                rhs = std::tolower(rhs, std::locale("en_US.UTF-8"));
                return lhs == rhs; }
                : [] (char lhs, char rhs) -> bool { return lhs == rhs; };
        std::boyer_moore_horspool_searcher searcher (
            needle.begin()
            , needle.end()
            , std::hash<std::string::iterator::value_type>()
            , comparator
        );
        auto size = needle.size();
        std::string line;
        uint64_t counter = 0;
        //std::getline(file, line, '\n'); // We assume, that 'needle' is alphanum
        while (std::getline(input, line, '\n'), (!line.empty() && !input.eof())) {
            if (line.size() < needle.size()) continue;
            auto found = std::search(line.begin(), line.end(), searcher);
            while (found != line.end()) {
                counter += 1;
                found = std::search(found + size, line.end(), searcher);
            }
        }
        return counter;
    } else {
        std::cout << "No substring to search was provided, exiting." << std::endl;
        return 0;
    }
    // if separate word, we at least can use regex: problem is, there must be only letters and numbers
}
