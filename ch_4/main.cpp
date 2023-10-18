#include <unordered_map>
#include <fstream>

#include "../utils/Stack.h"
#include "../utils/iohelpers.h"
#include "delimerr.h"

void delimiter_matching(std::unordered_map<std::string, std::string>& delimiters, const std::string& filePath) {
    Stack<std::string> stack;
    int lineNum = 0, lineNumMarker = 0;
    std::string line, lineMarker;
    std::ifstream fin(filePath);

    while(std::getline(fin, line)) {
        lineNum ++;
        for (int i = 0; i < line.size(); ++i) {
            // assign 'current' to 2 characters if the delim is a long comment
            std::string current = ((i < line.size() - 1) && ((line[i] == '/' && line[i+1] == '*') || (line[i] == '*' && line[i+1] == '/')))
                ? std::string(1, line[i]) + std::string(1, line[i+1])
                : std::string(1, line[i]);

            // add to stack if opening delim
            if (delimiters.find(current) != delimiters.end()) {  
                stack.push(current);
                lineNumMarker = lineNum;
                lineMarker = line;
                continue;
            }
            // remove from stack if closing delim matches opening delim
            if (!stack.empty() && current == delimiters[stack.top()]) {
                stack.pop();
                continue;
            }
            // throw an error if unexpected closing delim
            for (auto it = delimiters.begin(); it != delimiters.end(); ++it) {
                if (current == it->second) {
                    delimerr::where(filePath, line, lineNum);
                    delimerr::what(current, true);
                    exit(0);
                }
            }
        }
    }

    if (stack.empty()) {
        delimerr::no_error(filePath);
    }
    else {
        // in the event that an opening delim(s) do not have closing delim(s)
        // location matches the most recent mismatched opening delim
        delimerr::where(filePath, lineMarker, lineNumMarker);
        delimerr::what(delimiters[stack.top()], false);
    }
};

int main(int argc, char* argv[]) {
    delimerr::check_arguments(argc, 2);
    std::cout << "\n";

    // a hash map allows for delimiter versatility (e.g. switching languages) and avoids verbose conditionals
    std::unordered_map<std::string, std::string> delimiters = {{"(", ")"}, {"[", "]"}, {"{", "}"}, {"/*", "*/"}};
    delimiter_matching(delimiters, argv[1]);

    std::cout << std::endl;
    return 0;
}