#ifndef SLLIST_H
#define SLLIST_H

#include "SLLNode.h"

/* many of the methods here can technically be private.
however, this class is a general SLL implementation,
so it is appropriate for the object to have the 
following functionality. i'm opting for 
lowerCamelCase to indicate generality */

template <typename T>
class SLList {
    public:
        SLList();

        void out();
        unsigned int length();
        int findFirst(T item);

        SLLNode<T>* iterate(int index = -1, bool headIfNeg = true);
        T& at(int index);

        void pushBack(T info);
        void pushForward(T info);
        void removeAt(int index);
        void removeFirst(T info);
        void insert(T info, int index = -1);

        void orderInsert(T info);
    private:
        SLLNode<T> *head, *tail;
};

#include "SLList.cpp"
#endif