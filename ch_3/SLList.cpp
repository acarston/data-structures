#include <iostream>

#include "SLList.h"

template <typename T>
SLList<T>::SLList() {
    head = nullptr;
    tail = nullptr;
};


/* print each list element */
template <typename T>
void SLList<T>::out() {
    SLLNode<T> *current = head;
    while (current != nullptr) {
        std::cout << current->info << "\n";
        current = current->next;
    }
    std::cout << "\n";
};

/* return the length of the list */
template <typename T>
unsigned int SLList<T>::length() {
    int i = 0;
    for (SLLNode<T>* node = head; node != nullptr; node = node->next, ++i);
    return i;
};

/* find the index of a node's info */
template <typename T>
int SLList<T>::findFirst(T item) {
    int i = 0;
    for (SLLNode<T>* node = head; node != nullptr; node = node->next, ++i) {
        if (node->info == item) return i;
    }
    return -1; // not found gives negative index
};


/* give the node at an index */
template <typename T>
SLLNode<T>* SLList<T>::iterate(int index, bool headIfNeg) {
    SLLNode<T>* node = head;

    // give first node or give null if index is negative
    if (index < 0) {
        if (headIfNeg) return head; 
        else return nullptr;
    }

    // iterate the list
    for (int i = 0; i < index; ++i) {
        node = node->next;
        if (node == nullptr) return nullptr; // index out of range gives null
    }
    return node;
};

template <typename T>
T SLList<T>::at(int index) {
    return iterate(index)->info;
}


template <typename T>
void SLList<T>::pushBack(T info) {
    if (head == nullptr) { // if the list is empty
        head = new SLLNode<T>(info);
    }
    else if (tail == nullptr) { // if the tail DNE
        tail = new SLLNode<T>(info);
        head->next = tail;
    }
    else {
        tail->next = new SLLNode<T>(info); // otherwise.
        tail = tail->next;
    }
};

template <typename T>
void SLList<T>::pushForward(T info) {
    if (head == nullptr) { // avoid circular referencing
        head = new SLLNode<T>(info);
    }
    else if (tail == nullptr) {
        tail = head;
        head = new SLLNode<T>(info);
        head->next = tail;
    }
    else {
        SLLNode<T>* newHead = new SLLNode<T>(info, head);
        head = newHead;
        newHead = nullptr;
    }
};

/* remove the node at index */
template <typename T>
void SLList<T>::removeAt(int index) {
    SLLNode<T>* toRemove = iterate(index, false);
    SLLNode<T>* before = iterate(index - 1, false);

    if (toRemove == nullptr) { // sanity check
        return;
    }
    else if (before == nullptr || index < 1) {
        head = toRemove->next;
        delete before; // previous address of head
        before = nullptr;
    }
    else {
        before->next = toRemove->next;
        if (toRemove == tail) tail = before;
        delete toRemove;
        toRemove = nullptr;
    }

    if (head == tail) tail = nullptr; // list is two elements
};

/* remove the node containing info */
template <typename T>
void SLList<T>::removeFirst(T info) {
    int index = findFirst(info);
    if (index == -1) return; // do nothing if node DNE
    removeAt(index);
};

/* allocate a new node and insert after index */
template <typename T>
void SLList<T>::insert(T info, int index) {
    SLLNode<T>* toInsert = new SLLNode<T>(info);
    SLLNode<T>* node = iterate(index); // get node at index

    if (head == nullptr || index < 0) { // prepend if list empty or inserting before head
        pushForward(info);
        delete toInsert;
    }
    else if (node == tail) { // append if appending
        pushBack(info);
        delete toInsert;
    }
    else {
        toInsert->next = node->next;
        node->next = toInsert;
    }

    toInsert = nullptr;
};


/* insert info as a new node while keeping ascending order */
template <typename T>
void SLList<T>::orderInsert(T info) {
    int length = this->length();

    if (length == 0) {
        insert(info); // i.e. prepend if list empty
        return;
    }

    for (int i = 0; i < length; ++i) {
        T compareAgainst = at(i);
        if (info < compareAgainst) {
            insert(info, i - 1); // insert before compareAgainst
            return;
        }
    }

    int index = length - 1;
    insert(info, index); // i.e. append if largest
};