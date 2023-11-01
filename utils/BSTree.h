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
        void set_root(T rootVal) { root = new Node<T>(rootVal); };

        // requires root to be set lol. Tim does not like
        void insert(T val, void (*on_duplicate)(Node<T>* node) = nullptr) {
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

        void traverse_inorder(void (*visit)(T info)) {
            Node<T>* cur = root;
            while (cur != nullptr) {
                if (cur->left == nullptr) {
                    visit(cur->info);
                    cur = cur->right;
                }
                else {
                    Node<T>* p = cur->left;
                    while (p->right != nullptr && p->right != cur) {
                        if (p->right == nullptr) {
                            p->right = cur;
                            cur = cur->left;
                            break;
                        }
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
};

#endif