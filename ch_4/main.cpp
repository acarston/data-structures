#include <unordered_map>
#include <stdexcept>
#include <fstream>

#include "../utils/Stack.h"
#include "../utils/iohelpers.h"

void check_arguments(int argc) {
    if (argc < 2) throw std::invalid_argument("no input files");
    else if (argc > 2) throw std::invalid_argument("too many arguments");
};

void where(const std::string& line, int lineNum, int col) {
    std::cout << "in line " << lineNum << ", column " << col + 1 << ":\n";
    std::cout << line << "\n";

    std::string whitespace = "";
    for (int i = 0; i < col; ++i) {
        whitespace += " ";
    }

    std::cout << whitespace << "^\n" << whitespace << "^ HERE" << std::endl;
};

void where(const std::string& line, int lineNum) {
    std::cout << "in line " << lineNum << ":\n";
    std::cout << line << "\n\n";
};

// void what(const std::string& delimiter, std::unordered_map<std::string, std::string>& delimiters, bool isBeginDelim) {
//     if (isBeginDelim) std::cout << "expected a '" << delimiters[delimiter] << "'\n";
//     else std::cout 
// };

int main(int argc, char* argv[]) {
    check_arguments(argc);
    
    // to avoid verbose conditionals, I have opted for a hash map with delimiter-delimiter key-value pairs
    std::unordered_map<std::string, std::string> delimiters = {{"(", ")"}, {"[", "]"}, {"{", "}"}, {"/*", "*/"}};
    Stack<std::string> stack;

    int lineNum = 0;
    std::string line;
    std::string filePath = argv[1];
    std::ifstream fin(filePath);

    while(std::getline(fin, line)) {
        lineNum ++;

        for (int i = 0; i < line.size(); ++i) {
            // assign the current string to either 1 or 2 characters, depending on the delimiter
            std::string current = ((i < line.size() - 1) && ((line[i] == '/' && line[i+1] == '*') || (line[i] == '*' && line[i+1] == '/')))
                ? std::string(1, line[i]) + std::string(1, line[i+1])
                : std::string(1, line[i]);

            if (delimiters.find(current) != delimiters.end()) {
                stack.push(current);
                continue;
                // TODO place a marker
            }
            if (!stack.empty() && current == delimiters[stack.top()]) {
                stack.pop();
                continue;
            }
            for (auto it = delimiters.begin(); it != delimiters.end(); ++it) {
                if (current == it->second) {
                    // std::cout << "nay" << std::endl; // placeholder
                    where(line, lineNum);
                    exit(0);
                }
            }
                // if current is an ending delimiter, place a marker, then throw an error at marker
        }
    }

    if (stack.empty()) std::cout << "yay";
    else std::cout << "nay"; // throw an error at marker

    std::cout << std::endl;
    return 0;
}