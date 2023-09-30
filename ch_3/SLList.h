#ifndef SLLIST_H
#define SLLIST_H

#include "SLLNode.h"

template <typename T>
class SLList {
    public:
        // friend class SLLNode<T>;

        SLList();
        void push_back(T info);
        void push_forward(T info);
        void remove(unsigned int index); //TODO
        void remove(T info); //TODO
        void out();
        SLLNode<T>* iterate(unsigned int index, bool orLast = false);
        void insert(T info, unsigned int index);
        unsigned int length();
        int find(T item);
    private:
        SLLNode<T> *head, *tail;
};

#include "SLList.cpp"
#endif