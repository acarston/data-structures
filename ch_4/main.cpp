#include <unordered_map>

#include "../utils/Stack.h"
#include "../utils/iohelpers.h"

int main() {
    // to avoid verbose conditionals, I have opted for a hash map with delimiter-delimiter key-value pairs
    std::unordered_map<std::string, std::string> delimiters = {{"(", ")"}, {"[", "]"}, {"{", "}"}, {"/*", "*/"}};

    Stack<std::string> stack;
    std::string in = iohelpers::get_line("enter a statement:\n");
    for (int i = 0; i < in.size(); ++i) {
        // assign the current string to either 1 or 2 characters, depending on the delimiter
        std::string current = ((i < in.size() - 1) && ((in[i] == '/' && in[i+1] == '*') || (in[i] == '*' && in[i+1] == '/')))
            ? std::string(1, in[i]) + std::string(1, in[i+1])
            : std::string(1, in[i]);

        // add to stack if 'current' is a beginning delimiter; remove from stack if it is an ending delimiter
        if (delimiters.find(current) != delimiters.end()) stack.push(current);
        if (!stack.empty() && current == delimiters[stack.top()]) stack.pop();
    }

    if (stack.empty()) std::cout << "yay";
    else std::cout << "nay";

    std::cout << std::endl;
    return 0;
}