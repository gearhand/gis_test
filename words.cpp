#include "words.h"
#include <algorithm>
#include <iostream>
#include <regex>

uint64_t WordsMode::process(std::istream &input, std::string const& needle, bool case_insensitive, bool stand_alone) {
    if (stand_alone) {
        return process_standalone(input, needle, case_insensitive);
    }
    else {
        return process_substrings(input, needle, case_insensitive);
    }
}

uint64_t WordsMode::process_standalone(std::istream& input, std::string const& needle, bool case_insensitive) {
    // Use regex
    if (!needle.empty()) {
        std::stringstream builder;
        builder << R"(([^[:alnum:]]|^))" << needle << R"(([^[:alnum:]]|$))";
        using std::regex;
        auto pattern = case_insensitive ? regex( builder.str(), regex::extended | regex::optimize | regex::nosubs | regex::icase )
                                        : regex( builder.str(), regex::extended | regex::optimize | regex::nosubs );
        std::string line;
        uint64_t counter = 0;
        std::smatch matches;
        while (std::getline(input, line, '\n'), (!line.empty())) {
            if (line.size() < needle.size()) continue;
            std::regex_search(line, matches, pattern);
            counter += matches.size();
            line.erase();
        }
        return counter;
    } else {
        std::cout << "No substring to search was provided, exiting." << std::endl;
        return 0;
    }
    // if separate word, we at least can use regex: problem is, there must be only letters and numbers
}

uint64_t WordsMode::process_substrings(std::istream& input, std::string const& needle, bool case_insensitive) {
    // process words
    // We can search for a substring, we can search for separate words
    // if substring, we can use boyer-moore-horspool
    if (!needle.empty()) {
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
        while (std::getline(input, line, '\n'), (!line.empty())) {
            if (line.size() < needle.size()) continue;
            auto found = std::search(line.begin(), line.end(), searcher);
            while (found != line.end()) {
                counter += 1;
                found = std::search(found + size, line.end(), searcher);
            }
            line.erase();
        }
        return counter;
    } else {
        std::cout << "No substring to search was provided, exiting." << std::endl;
        return 0;
    }
    // if separate word, we at least can use regex: problem is, there must be only letters and numbers
}
