#ifndef SLLIST_H
#define SLLIST_H

#include "SLLNode.h"

template <typename T>
class SLList {
    public:
        // friend class SLLNode<T>;

        SLList();
        void push_back(T info);
        void out();
    private:
        SLLNode<T> *head, *tail;
};

#include "SLList.cpp"
#endif