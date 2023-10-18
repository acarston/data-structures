#ifndef SLLNODE_H
#define SLLNODE_H

template <typename T>
class SLLNode {
    public:
        // SLList, Stack can access info, next
        template <typename U> friend class SLList;
        template <typename V> friend class Stack;

        SLLNode(T info, SLLNode* next = nullptr) {
            this->info = info;
            this->next = next;
        };
        
        // return a reference to info
        T& getInfo() { return this->info; };
    private:
        T info;
        SLLNode* next = nullptr;
};

#endif