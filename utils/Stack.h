#ifndef STACK_H
#define STACK_H

#include "SLLNode.h"

/* since this is a template class, everything is in the dot h file. 
according to _The C++ standard library: a tutorial and handbook_: 
"the only portable way of using templates at the moment is to implement 
them in header files by using inline functions." also, there is no error
handling for calling the functions when the stack is empty. it is up to 
the programmer to avoid seg faults using the 'empty' function. this is a 
performance choice, similar to how arrays don't throw 'index out of 
bounds' errors. */

template <typename T>
class Stack {
    public:
        void push(T info) {
            if (head == nullptr) {
                head = new SLLNode<T>(info);
            }
            else {
                head = new SLLNode<T>(info, head);
            }
        };

        void pop() {
            SLLNode<T>* temp = head->next;
            delete head; 
            head = temp;
        };

        T top() {
            return head->info;
        };

        bool empty() {
            return head == nullptr;
        };

    private:
        SLLNode<T>* head = nullptr;
};

#endif