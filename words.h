#pragma once

#include <string>

/**
 * Class for searching for words or substrings in input
 */
class WordsMode {
public:
    static uint64_t process(
            std::istream& input
            , std::string const& needle
            , bool case_insensitive
            , bool stand_alone
    );

private:
    /**
     * Tries to search for word, separated from other text by
     * punctuation, spaces, newlines. Works with ascii alphanumeric patterns only
     * @param needle must be ASCII alphanumeric string
     * @return number of matched words
     */
    static uint64_t process_standalone(std::istream& input, std::string const& needle, bool case_insensitive);

    /**
     * Simply search for substring *needle* in input
     * @return number of matched substrings
     */
    static uint64_t process_substrings(std::istream& input, std::string const& needle, bool case_insensitive);
};
