#include <iostream>

namespace iohelpers {
    template <typename T>
    T get_input(const std::string& prompt) {
        std::cout << prompt;
        T temp;
        std::cin >> temp;
        return temp;
    };

    std::string get_line(const std::string& prompt) {
        std::cout << prompt;
        std::string in;
        std::getline(std::cin, in);
        return in;
    }
};
