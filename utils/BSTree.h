#ifndef BSTREE_H
#define BSTREE_H

#include <cmath>

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

		void insert(T val, void (*on_duplicate)(T& current, T& incoming) = nullptr) {
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

		void balance_dsw() {
			create_backbone();
			create_perfect_tree();
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


		void rotate_left(Node<T>*& gr, Node<T>*& par, Node<T>* ch) {
			par->right = ch->left;
			ch->left = par;
			if (par != root) gr->right = ch;
			else root = gr = ch;
		};

		void rotate_right(Node<T>*& gr, Node<T>*& par) {
			Node<T>* ch = par->left;
			if (par != root) gr->right = ch;
			else root = gr = ch;
			par->left = ch->right;
			ch->right = par;
		};

		void create_backbone() {
			Node<T>* gr = root, * par = root;
			while (par != nullptr) {
				if (par->left != nullptr) {
					rotate_right(gr, par);
					par = gr;
				}
				else {
					gr = par;
					par = par->right;
				}
			}
		};

		void create_perfect_tree() {
			Node<T>* gr = root, * par = root;
			int m = pow(2, std::log2(numNodes + 1)) - 1;
			for (int i = 0; i < numNodes - m; ++i) {
				rotate_left(gr, par, par->right);
				gr = par;
				par = par->right;
			}
			for (m = m / 2; m > 0; m /= 2) {
				gr = par = root;
				for (int i = 0; i < m; ++i) {
					rotate_left(gr, par, par->right);
					gr = par;
					par = par->right;
				}
			}
		};
};

#endif