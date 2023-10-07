#include "Stack.h"

template <typename T>
void Stack<T>::push(T info) {
    if (head == nullptr) {
        head = new SLLNode<T>(info);
    }
    else {
        head = new SLLNode<T>(info, head);
    }
};

template <typename T>
void Stack<T>::pop() {
    SLLNode<T>* temp = head->next;
    delete head;
    head = temp;
};

template <typename T>
T Stack<T>::top() {
    return head->info;
};