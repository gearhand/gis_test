
#include <gtest/gtest.h>
#include <words.h>
#include <checksum.h>

TEST(WORDS, ASCII_TEXT) {
    std::string data = "This is english text, which contains the word \"text\" 3 times.\n"
                       "The text is separated by newlines\n";
    std::stringstream input;
    input << data;
    uint64_t result = WordsMode::process(input, "text", false, false);
    ASSERT_EQ(result, 3);
    input.clear();
    input << data;
    result = WordsMode::process(input, "th", false, false);
    ASSERT_EQ(result, 1);
    input.clear();
    input << data;
    result = WordsMode::process(input, "Th", false, false);
    ASSERT_EQ(result, 2);
    input.clear();
    input << data;
    result = WordsMode::process(input, "Th", true, false);
    ASSERT_EQ(result, 3);
}

TEST(WORDS, UTF_TEXT) {
    std::string data = "This is mixed text, включающий в себя вставки на кириллице,\n"
                       "и закодированный в юникоде\n";
    std::stringstream input;
    input << data;
    uint64_t result = 0;
    result = WordsMode::process(input, "код", false, false);
    ASSERT_EQ(result, 2);
    input.clear();
    input << data;
    result = WordsMode::process(input, "is", false, false);
    ASSERT_EQ(result, 2);
    input.clear();
    input << data;
    result = WordsMode::process(input, "absent", false, false);
    ASSERT_EQ(result, 0);
}

TEST(WORDS, MANGLED) {
    std::string with_trailing_newline = {0x21, 0x22, 0x23, 0x01, 0x02, 0x00, 0x76, 0x78, 0x61, 0x28, 0x79, static_cast<char>(0x87), 0x74, 0x65, 0x78, 0x74, static_cast<char>(0x87), 0x48, 0x00, 0x0a};
    std::stringstream input;
    input << with_trailing_newline;
    uint64_t result = 0;
    result = WordsMode::process(input, "text", false, false);
    ASSERT_EQ(result, 1);
    input.clear();
    std::string no_trailing_newline = {0x21, 0x22, 0x23, 0x01, 0x02, 0x00, 0x76, 0x78, 0x61, 0x28, 0x79, static_cast<char>(0x87), 0x74, 0x65, 0x78, 0x74, static_cast<char>(0x87), 0x48, 0x00};
    input << no_trailing_newline;
    result = WordsMode::process(input, "text", false, false);
    ASSERT_EQ(result, 1);
}

TEST(CHECKSUM, SHORT) {
    std::string data = { 0x1, 0x2, 0x3}; // less than 32 bit
    std::stringstream input;
    input << data;
    uint64_t result = 0;
    result = ChecksumMode::process(input);
    ASSERT_EQ(result, 0x01020300); // zeros was appended to the end
}

TEST(WORDS, STANDALONE) {
    std::string data = "This text contains some substrings, which are part of\n"
                       "other words. Здесь также содержится кириллица, но искать\n"
                       "слова в кириллице мы не можем. Another string";
    std::stringstream input;
    input << data;
    uint64_t result = 0;
    result = WordsMode::process(input, "other", false, true);
    ASSERT_EQ(result, 1);
}

TEST(CHECKSUM, LONG) {
    std::string data = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA};
    std::stringstream input;
    input << data;
    uint64_t result = 0;
    result = ChecksumMode::process(input);
    ASSERT_EQ(result, 0x01020304 + 0x05060708 + 0x090A0000); // zeros was appended to the end
}
