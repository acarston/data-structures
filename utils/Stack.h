#ifndef STACK_H
#define STACK_H

#include "SLLNode.h"

template <typename T>
class Stack {
    public:
        void push(T info);
        void pop();
        T top();
    private:
        SLLNode<T>* head = nullptr;
};

#include "Stack.cpp"
#endif