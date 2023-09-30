#ifndef SLLIST_H
#define SLLIST_H

#include "SLLNode.h"

template <typename T>
class SLList {
    public:
        SLList();

        void out();
        unsigned int length();
        int find(T item);

        SLLNode<T>* iterate(int index = -1, bool orLast = false);

        void push_back(T info);
        void push_forward(T info);
        void removeAt(unsigned int index);
        void removeFirst(T info);
        void insert(T info, int index = -1);

        void orderInsert(T info);
    private:
        SLLNode<T> *head, *tail;
};

#include "SLList.cpp"
#endif