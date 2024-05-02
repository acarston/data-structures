#ifndef DELIMERR_H
#define DELIMERR_H

#include <stdexcept>
#include <iostream>

namespace delimerr {
    // restrict CLI arguments to an exact number
    void check_arguments(int argc, unsigned int limit) {
        if (argc < limit) throw std::invalid_argument("no input files");
        else if (argc > limit) throw std::invalid_argument("too many arguments");
    }

    // output a location
    void where(const std::string& filePath, const std::string& line, int lineNum) {
        std::cout << "file " << filePath << ", in line " << lineNum << ":\n";
        std::cout << line << "\n" << std::endl;
    }

    // isn't quite compatible with fstream's getline
    void where(const std::string& filePath, const std::string& line, int lineNum, int col) {
        std::cout << "file " << filePath << ", in line " << lineNum << ", column " << col + 1 << ":\n";
        std::cout << line << "\n";

        std::string whitespace = "";
        for (int i = 0; i < col; ++i) {
            whitespace += " ";
        }

        std::cout << whitespace << "^\n" << whitespace << "^ HERE" << std::endl;
    }

    // choose and output an error message
    void what(const std::string& delimiter, bool unexpected) {
        if (unexpected) std::cout << "unexpected token '" << delimiter << "'\n" << std::endl;
        else std::cout << "expected a '" << delimiter << "'" << std::endl;
    }

    void no_error(const std::string& filePath) {
        std::cout << "no errors detected in " << filePath << std::endl;
    }
}

#endif