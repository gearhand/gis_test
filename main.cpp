#include <iostream>

#include <tclap/CmdLine.h>
#include <tclap/ValueArg.h>
#include <unordered_map>
#include <fstream>
#include <cstring>
#include <netinet/in.h>
#include <algorithm>
#include <cctype>
#include <locale>

//enum class OperationMode {
//    WORDS,
//    CHECKSUM,
//    NONE,
//};

int main(int argc, char** argv) {
    TCLAP::CmdLine parser ("This is program for 2GIS test");
    TCLAP::ValueArg<std::string> mode (
            "m"
            , "mode"
            , "Operation mode, one of <words|checksum>" // TODO: make automatic
            , true
            , ""
            , "mode"
    );
    TCLAP::ValueArg<std::string> filename (
            "f"
            , "filename"
            , "File to process"
            , true
            , ""
            , "filename"
    );
    TCLAP::ValueArg<std::string> needle_arg (
        "w"
        , "word"
        , "Substring to count"
        , false
        , ""
        , "substr"
    );
    TCLAP::SwitchArg case_sensitive (
        "i"
        , "insensitive"
        , "Set this flag, if you need case insensitive search"
    );
    parser.add(mode);
    parser.add(filename);
    parser.add(needle_arg);
    std::cout << "Hello, World!" << std::endl;
    parser.parse(argc, argv);
    //std::unordered_map<char const*, int> modes {{"word", 1}};
    auto const& mode_name = mode.getValue();
    if (mode_name == "words") {
        // process words
        // We can search for a substring, we can search for separate words
        // if substring, we can use boyer-moore-horspool
        if (!needle_arg.getValue().empty()) {
            std::ifstream file (filename.getValue(), std::ios::in | std::ios::binary);
            std::string needle = needle_arg.getValue();
            std::boyer_moore_horspool_searcher searcher (needle.begin(), needle.end());
            auto size = needle.size();
            std::string line;
            uint64_t counter = 0;
            //std::getline(file, line, '\n'); // We assume, that 'needle' is alphanum
            while (std::getline(file, line, '\n'), !line.empty()) {
                if (case_sensitive.getValue()) {
                    for (auto& ch : line) {
                        ch = std::tolower(ch, std::locale("en_US.UTF-8"));
                    }
                    for (auto& ch : needle) {
                        ch = std::tolower(ch, std::locale("en_US.UTF-8"));
                    }
                }
                auto found = std::search(line.begin(), line.end(), searcher);
                while (found != line.end()) {
                    counter += 1;
                    found = std::search(found + size, line.end(), searcher);
                }
            }
            std::cout << "File contains " << counter << " substrings \"" << needle << '\"' << std::endl;
        } else {
            std::cout << "No substring to search was provided, exiting." << std::endl;
        }
        // if separate word, we at least can use regex: problem is, there must be only letters and numbers
    }
    else if (mode_name == "checksum") {
        // process checksum
        std::ifstream file (filename.getValue(), std::ios::in | std::ios::binary);
        char buffer[4];
        auto size = sizeof buffer;
        std::memset(buffer, 0, size);
        std::streamsize chars_read = 0;
        uint64_t checksum = 0;
        while (chars_read = file.readsome(buffer, size), chars_read == size) {
            std::cout << "Chars read in cycle: " << chars_read << std::endl;
            checksum += ntohl(*reinterpret_cast<uint32_t const*>(buffer));
        }
        if (chars_read > 0) {
            std::cout << "Chars read after cycle: " << chars_read << std::endl;
            std::memset(buffer + chars_read, 0 , size - chars_read);
            checksum += ntohl(*reinterpret_cast<uint32_t const*>(buffer));
        }
        std::cout << std::hex << "0x" << checksum << std::dec << " : " << checksum << std::endl;
    }
    else {
        std::cout << "No valid mode was provided, exiting." << std::endl;
    }
    return 0;
}
