#ifndef BSTREE_H
#define BSTREE_H

template <typename T>
struct Node {
    T info;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(T info): info(info) {};
};

template <typename T>
class BSTree {
    public:
        BSTree() {};
        BSTree(T rootVal) { root = new Node<T>(rootVal); };

        void insert(T val, void (*on_duplicate)(Node<T>* node) = nullptr) {
            if (root == nullptr) {
                set_root(val);
                return;
            }

            Node<T>* p = root;
            while (true) {
                if (val > p->info) {
                    if (p->right == nullptr) {
                        p->right = new Node<T>(val);
                        break;
                    }
                    p = p->right;
                }
                else if (val < p->info) {
                    if (p->left == nullptr) {
                        p->left = new Node<T>(val);
                        break;
                    }
                    p = p->left;
                }
                else {
                    if (on_duplicate == nullptr) break;
                    else on_duplicate(p);
                }
            }
        };
        
        template <typename U>
        void insert(T val, U& (*get_member)(T info), void (*on_duplicate)(T current, T incoming) = nullptr) {
            if (root == nullptr) {
                set_root(val);
                return;
            }

            Node<T>* p = root;
            while (true) {
                if (get_member(val) > get_member(p->info)) {
                    if (p->right == nullptr) {
                        p->right = new Node<T>(val);
                        break;
                    }
                    p = p->right;
                }
                else if (get_member(val) < get_member(p->info)) {
                    if (p->left == nullptr) {
                        p->left = new Node<T>(val);
                        break;
                    }
                    p = p->left;
                }
                else {
                    if (on_duplicate != nullptr) on_duplicate(p->info, val);
                    break;
                }
            }
        };

        // Morris inorder traversal algorithm. Adapted from 
        // https://takeuforward.org/data-structure/morris-inorder-traversal-of-a-binary-tree/
        void traverse_inorder(void (*visit)(T info)) {
            Node<T>* cur = root;
            while (cur != nullptr) {
                // visit, move to the right if no left child
                if (cur->left == nullptr) {
                    visit(cur->info);
                    cur = cur->right;
                }
                else {
                    // look for the rightmost subtree node
                    Node<T>* p = cur->left; 
                    while (true) {
                        // make current the right child of this node
                        // point current to the new 'root'
                        if (p->right == nullptr) {
                            p->right = cur;
                            cur = cur->left;
                            break;
                        }
                        // visit, move to the right
                        if (p->right == cur) {
                            p->right = nullptr;
                            visit(cur->info);
                            cur = cur->right;
                            break;
                        }
                        p = p->right;
                    }
                }
            }
        };

    private:
        Node<T>* root = nullptr;

        void set_root(T rootVal) { root = new Node<T>(rootVal); };
};

#endif