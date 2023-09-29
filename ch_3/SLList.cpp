#include "SLList.h"

template <typename T>
SLList<T>::SLList() {
    head = nullptr;
    tail = nullptr;
};

template <typename T>
void SLList<T>::push_back(T info) {
    if (head == nullptr) {
        head = new SLLNode(info);
        return;
    }
    if (tail == nullptr) {
        tail = new SLLNode(info);
        head->next = tail;
        return;
    }
    tail->next = new SLLNode(info);
    tail = tail->next;
    return;
    
    // // swap 
    // IntSLLNode *tmp = tail; // tmp->next = nullptr;
    // tail = tail->next;
    // tail->next = tmp;
    // tail->next->next = nullptr;
};

template <typename T>
void SLList<T>::out() {
    SLLNode<T> *current = head;
    while (current != nullptr) {
        std::cout << current->info << "\n";
        current = current->next;
    }
    std::cout << std::endl;
};