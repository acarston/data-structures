#ifndef BSTREE_H
#define BSTREE_H

#include <cmath>
#include <stack>

template <typename T>
struct Node {
	T info;
	Node* left = nullptr;
	Node* right = nullptr;
	int height = 1;

	Node(T info): info(info) {};
};

template <typename T>
class BSTree {
	private:
		Node<T>* root = nullptr;
		int numNodes = 0;

		bool set_root(T& rootVal) { 
			if (root == nullptr) {
				root = new Node<T>(rootVal);
				return true;
			}
			return false;
		};

		int get_height(Node<T>* node) {
			if (node == nullptr) return 0;
			else return node->height;
		};

		int get_balfactor(Node<T>* node) {
			return get_height(node->right) - get_height(node->left);
		};

	public:
		BSTree() {};
		BSTree(T rootVal) { root = new Node<T>(rootVal); };

		// make an insertion with AVL self-balancing
		// implementation is original; everything is managed by a stack
		// which keeps track of the path taken by the new insert
		void avl_insert(T val) {
			if (set_root(val)) return;

			std::stack<Node<T>*> path;
			Node<T>* p = root;
			path.push(p);
			while (true) {
				if (val > p->info) {
					if (p->right == nullptr) {
						p->right = new Node<T>(val);
						// update heights, balance factor only if the tree has been skewed
						if (p->left == nullptr) break;
						else return;
					}
					p = p->right;
				}
				else if (val < p->info) {
					if (p->left == nullptr) {
						p->left = new Node<T>(val);
						if (p->right == nullptr) break;
						else return;
					}
					p = p->left;
				}
				else {
					return;
				}
				path.push(p);
			}

			while (true) {
				// update the heights in the path
				Node<T>* cur = path.top();
				cur->height = 1 + std::max(get_height(cur->right), get_height(cur->left));
				path.pop();
				
				// if cur is root
				if (path.empty()) break;

				Node<T>* par = path.top();
				int parBalFactor = get_balfactor(par);
				int curBalFactor = get_balfactor(cur);
				if (parBalFactor > 1) {
					if (curBalFactor > 0) rotate_left(par, cur)
					else rotate_rightleft(par, cur)
				}
				else if (parBalFactor < 1) {
					if (curBalFactor < 0) rotate_right(par, cur);
					else rotate_leftright(par, cur);
				}
			}
		};

		void insert(T val, void (*on_duplicate)(T& current, T& incoming) = nullptr) {
			if (set_root(val)) return;

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
					// skip duplicates if no handling is passed in
					if (on_duplicate != nullptr) on_duplicate(p->info, val);
					break;
				}
			}
		};
		
		// insert with custom comparison values
		template <typename U>
		void insert(T val, U& (*get_member)(T& info), void (*on_duplicate)(T& current, T& incoming) = nullptr) {
			if (set_root(val)) return;

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

		// insert with custom compare function
		void insert(T val, int (*compare)(T& current, T& incoming), void (*on_duplicate)(T& current, T& incoming)) {
			if (set_root(val)) return;

			Node<T>* p = root;
			while (true) {
				if (compare(p->info, val) > 0) {
					if (p->right == nullptr) {
						p->right = new Node<T>(val);
						break;
					}
					p = p->right;
				}
				else if (compare(p->info, val) < 0) {
					if (p->left == nullptr) {
						p->left = new Node<T>(val);
						break;
					}
					p = p->left;
				}
				else {
					on_duplicate(p->info, val);
					break;
				}
			}
		};

		// Morris inorder traversal algorithm. Adapted from 
		// https://takeuforward.org/data-structure/morris-inorder-traversal-of-a-binary-tree/
		void traverse_inorder(void (*visit)(T& info)) {
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
						// remove the new connection
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
};

#endif