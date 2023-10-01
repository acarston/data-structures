#ifndef SLLIST_H
#define SLLIST_H

#include "SLLNode.h"

/* many of the methods here can technically be private.
however, this class is a general SLL implementation,
so it is appropriate for the object to have the 
following functionality. i'm following the vector
convention of lower-case methods, but opting for 
camelCase instead of underscores */

template <typename T>
class SLList {
    public:
        SLList();

        void out();
        unsigned int length();
        int findFirst(T item);

        SLLNode<T>* iterate(int index = -1);
        T at(int index);

        void pushBack(T info);
        void pushForward(T info);
        void removeAt(unsigned int index);
        void removeFirst(T info);
        void insert(T info, int index = -1);

        void orderInsert(T info);
    private:
        SLLNode<T> *head, *tail;
};

#endif