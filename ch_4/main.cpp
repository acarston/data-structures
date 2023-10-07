#include "../utils/Stack.h"

int main() {
    Stack<int> stack;
    stack.push(4);
    stack.push(5);

    stack.pop();
    stack.pop();
    return 0;
}