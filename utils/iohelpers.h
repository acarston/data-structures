#ifndef IOHELPERS_H
#define IOHELPERS_H

#include <iostream>
#include <string>

namespace iohelpers {
    template <typename T>
    T get_input(const std::string& prompt) {
        std::cout << prompt;
        T temp;
        std::cin >> temp;
        return temp;
    }

    std::string get_line(const std::string& prompt) {
        std::cout << prompt;
        std::string in;
        std::getline(std::cin, in);
        return in;
    }

    void check_args(int argc, int lowerBound, int upperBound) {
        if (argc < lowerBound) {
            std::cout << "FATAL: too few arguments";
            exit(-1);
        }
        else if (argc > upperBound) {
            std::cout << "FATAL: too many arguments";
            exit(-1);
        }
    }
};

#endif