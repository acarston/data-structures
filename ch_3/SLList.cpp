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
    return -1;
};


/* give the node at an index */
template <typename T>
SLLNode<T>* SLList<T>::iterate(int index) {
    SLLNode<T>* node = head;

    // for the case when attempting to access the first node
    if (index == -1) return head; 

    // iterate the list
    for (int i = 0; i < index; ++i) {
        if (node->next == nullptr) return nullptr; // index out of range gives null
        node = node->next;
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
        head = new SLLNode(info);
        return;
    }
    if (tail == nullptr) { // if the tail DNE
        tail = new SLLNode(info);
        head->next = tail;
        return;
    }
    tail->next = new SLLNode(info); // otherwise.
    tail = tail->next;
};

template <typename T>
void SLList<T>::pushForward(T info) {
    if (head == nullptr) { // avoid circular referencing
        head = new SLLNode<T>(info);
        return;
    }
    SLLNode<T>* newHead = new SLLNode<T>(info, head);
    head = newHead;
};

/* remove the node at index */
template <typename T>
void SLList<T>::removeAt(unsigned int index) {
    SLLNode<T>* toRemove = iterate(index);
    SLLNode<T>* before = iterate(index - 1);

    if (toRemove == nullptr) return; // sanity check
    if (before == nullptr || index < 1) {
        head = toRemove->next;
        delete before; // previous address of head
        return;
    }

    before->next = toRemove->next;
    delete toRemove;
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

    if (head == nullptr) { // prepend if list empty
        pushForward(info);
        delete toInsert;
    }
    else if (index == -1) { // prepend if inserting before head
        pushForward(info); 
    }
    else {
        toInsert->next = node->next;
        node->next = toInsert;
    }
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