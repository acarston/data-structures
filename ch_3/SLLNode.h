#ifndef SLLNODE_H
#define SLLNODE_H

#include "SLList.h"

template <typename T>
class SLLNode {
    public:
        // SLList can access info, next
        template<typename U> 
        friend class SLList;

        SLLNode(T info, SLLNode* next = nullptr) {
            this->info = info;
            this->next = next;
        };
    private:
        T info;
        SLLNode* next;
};

#include "SLLNode.cpp"
#endif