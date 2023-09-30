#include "SLList.h"

template <typename T>
SLList<T>::SLList() {
    head = nullptr;
    tail = nullptr;
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

template <typename T>
unsigned int SLList<T>::length() {
    int i = 0;
    for (SLLNode<T>* node = head; node != nullptr; node = node->next, ++i);
    return i;
};

template <typename T>
int SLList<T>::find(T item) {
    int i = 0;
    for (SLLNode<T>* node = head; node != nullptr; node = node->next, ++i) {
        if (node->info == item) return i;
    }
    return -1;
};


template <typename T>
SLLNode<T>* SLList<T>::iterate(int index, bool orLast) {
    SLLNode<T>* node = head;
    if (index == -1) return node;

    for (int i = 0; i < index; ++i) {
        if (node->next == nullptr) return orLast ? node : nullptr;   // index out of range gives null or last node
        node = node->next;
    }
    return node;
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
void SLList<T>::push_forward(T info) {
    if (head == nullptr) {
        head = new SLLNode<T>(info);
        return;
    }
    SLLNode<T>* newHead = new SLLNode<T>(info, head);
    head = newHead;
};

template <typename T>
void SLList<T>::removeAt(unsigned int index) {
    SLLNode<T>* toRemove = iterate(index);
    SLLNode<T>* before = iterate(index - 1);

    if (toRemove == nullptr) return;
    if (before == nullptr) {
        delete head;
        head = nullptr;
        return;
    }

    before->next = toRemove->next;
    delete toRemove;
};

template <typename T>
void SLList<T>::removeFirst(T info) {
    int index = find(info);
    removeAt(index);
};

/* allocate a new node and insert after index */
template <typename T>
void SLList<T>::insert(T info, int index) {
    SLLNode<T>* toInsert = new SLLNode<T>(info);
    SLLNode<T>* node = iterate(index);   // get node at index

    if (head == nullptr) {    // prepend if list empty
        push_forward(info);
        delete toInsert;
    }
    else if (index == -1) {    // prepend if inserting before head
        push_forward(info); 
    }
    else {
        auto nextNode = node->next;
        toInsert->next = node->next;
        node->next = toInsert;
    }
};


template <typename T>
void SLList<T>::orderInsert(T info) {
    int length = this->length();

    if (length == 0) {
        insert(info);   // i.e. prepend
        return;
    }

    for (int i = 0; i < length; ++i) {
        T compareAgainst = iterate(i)->info;
        if (info < compareAgainst) {
            insert(info, i - 1);
            return;
        }
    }
    int index = length - 1;
    insert(info, index);
};