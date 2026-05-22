#pragma once
#include <ostream>
#include "customExceptions.h"

template<typename Key, typename Value>
struct Node {
	Key key;
	Value value;
	Node* left;
	Node* right;

	Node(const Key& key, const Value& value)
		: key(key), value(value), left(nullptr), right(nullptr) {
	}
};

template<typename Key, typename Value>
class BinarySearchTree {
private:
	Node<Key, Value>* root;

	Node<Key, Value>* copyHelper(Node<Key, Value>* node) {
		if (node == nullptr) return nullptr;
		Node<Key, Value>* newNode = new Node<Key, Value>(node->key, node->value);
		newNode->left = copyHelper(node->left);
		newNode->right = copyHelper(node->right);
		return newNode;
	}

	void PostOrder(Node<Key, Value>* p) {
		if (p != nullptr) {
			PostOrder(p.left);
			PostOrder(p.right);
			delete p;
		}
	}

	Node<Key, Value>* removeHelper(Node<Key, Value>* node, const Key& key, bool& success) {
		if (node == nullptr) {
			success = false;
			return nullptr;
		}

		if (key == node->key) {
			success = true;

			if (node->left == nullptr) {
				Node<Key, Value>* temp = node->right;
				delete node;
				return temp;
			}
			else if (node->right == nullptr) {
				Node<Key, Value>* temp = node->left;
				delete node;
				return temp;
			}

			Node<Key, Value>* temp = node->right;
			while (temp->left != nullptr) {
				temp = temp->left;
			}

			node->key = temp->key;
			node->value = temp->value;
			node->right = removeHelper(node->right, temp->key, success);
		}
		else if (key < node->key) {
			node->left = removeHelper(node->left, key, success);
		}
		else {
			node->right = removeHelper(node->right, key, success);
		}

		return node;
	}

	class Stack {
	private:
		struct StackNode {
			Node<Key, Value>* treeNode;
			StackNode* next;
			StackNode(Node<Key, Value>* tn, StackNode* n) : treeNode(tn), next(n) {}
		};
		StackNode* topNode;

	public:
		Stack() : topNode(nullptr) {}

		~Stack() {
			while (topNode != nullptr) {
				StackNode* temp = topNode;
				topNode = topNode->next;
				delete temp;
			}
		}

		Stack(const Stack& other) : topNode(nullptr) {
			if (other.topNode == nullptr) return;
			topNode = new StackNode(other.topNode->treeNode, nullptr);
			StackNode* current = topNode;
			StackNode* otherCurrent = other.topNode->next;
			while (otherCurrent != nullptr) {
				current->next = new StackNode(otherCurrent->treeNode, nullptr);
				current = current->next;
				otherCurrent = otherCurrent->next;
			}
		}

		Stack& operator=(const Stack& other) {
			if (this == &other) return *this;
			while (topNode != nullptr) {
				StackNode* temp = topNode;
				topNode = topNode->next;
				delete temp;
			}
			if (other.topNode != nullptr) {
				topNode = new StackNode(other.topNode->treeNode, nullptr);
				StackNode* current = topNode;
				StackNode* otherCurrent = other.topNode->next;
				while (otherCurrent != nullptr) {
					current->next = new StackNode(otherCurrent->treeNode, nullptr);
					current = current->next;
					otherCurrent = otherCurrent->next;
				}
			}
			return *this;
		}

		void push(Node<Key, Value>* node) {
			topNode = new StackNode(node, topNode);
		}

		Node<Key, Value>* pop() {
			if (topNode == nullptr) return nullptr;
			Node<Key, Value>* result = topNode->treeNode;
			StackNode* temp = topNode;
			topNode = topNode->next;
			delete temp;
			return result;
		}

		bool isEmpty() const {
			return topNode == nullptr;
		}
	};

public:
	// Rule of 5
	BinarySearchTree() : root(nullptr) {}

	~BinarySearchTree() {
		clear();
	}

	BinarySearchTree(const BinarySearchTree& other) : root(nullptr) {
		root = copyHelper(other.root);
	}

	BinarySearchTree& operator=(const BinarySearchTree& other) {
		if (this != &other) {
			clear();
			root = copyHelper(other.root);
		}
		return *this;
	}

	BinarySearchTree(BinarySearchTree&& other) noexcept : root(other.root) {
		other.root = nullptr;
	}

	BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
		if (this != &other) {
			clear();
			root = other.root;
			other.root = nullptr;
		}
		return *this;
	}

	// Alap interfész
	void clear() {
		PostOrder(root);
		root = nullptr;
	}

	bool contains(const Key& key) const {
		Node<Key, Value>* current = root;
		while (current != nullptr) {
			if (key == current->key) return true;
			if (key < current->key) current = current->left;
			else current = current->right;
		}
		return false;
	}

	bool insert(const Key& key, const Value& value) {
		if (root == nullptr) {
			root = new Node<Key, Value>(key, value);
			return true;
		}
		Node<Key, Value>* current = root;
		while (true) {
			if (key == current->key) return false;

			if (key < current->key) {
				if (current->left == nullptr) {
					current->left = new Node<Key, Value>(key, value);
					return true;
				}
				current = current->left;
			}
			else {
				if (current->right == nullptr) {
					current->right = new Node<Key, Value>(key, value);
					return true;
				}
				current = current->right;
			}
		}
	}

	bool remove(const Key& key) {
		bool success = false;
		root = removeHelper(root, key, success);
		return success;
	}

	Value& operator[](const Key& key) {
		Node<Key, Value>* current = root;
		if (current == nullptr) {
			root = new Node<Key, Value>(key, Value());
			return root->value;
		}
		while (true) {
			if (current->key == key) return current->value;
			if (key < current->key) {
				if (current->left == nullptr) {
					current->left = new Node<Key, Value>(key, Value());
					return current->left->value;
				}
				current = current->left;
			}
			else {
				if (current->right == nullptr) {
					current->right = new Node<Key, Value>(key, Value());
					return current->right->value;
				}
				current = current->right;
			}
		}
	}

	const Value& operator[](const Key& key) const {
		Node<Key, Value>* current = root;
		while (current != nullptr) {
			if (key == current->key) return current->value;
			if (key < current->key) current = current->left;
			else current = current->right;
		}
		throw KeyNotFoundException();
	}

	// Iterátor osztály
	class Iterator {
	private:
		Stack stack;
		Node<Key, Value>* current;

		void pushLeftBranch(Node<Key, Value>* node) {
			while (node != nullptr) {
				stack.push(node);
				node = node->left;
			}
		}

	public:
		Iterator(Node<Key, Value>* rootNode) : current(nullptr) {
			pushLeftBranch(rootNode);
			if (!stack.isEmpty()) {
				current = stack.pop();
			}
		}

		Iterator() : current(nullptr) {}

		Node<Key, Value>& operator*() {
			return *current;
		}

		Node<Key, Value>* operator->() {
			return current;
		}

		Iterator& operator++() {
			if (current == nullptr) return *this;

			if (current->right != nullptr) {
				pushLeftBranch(current->right);
			}

			if (!stack.isEmpty()) {
				current = stack.pop();
			}
			else {
				current = nullptr;
			}

			return *this;
		}

		Iterator operator++(int) {
			Iterator temp = *this;
			++(*this);
			return temp;
		}

		bool operator!=(const Iterator& other) const {
			return current != other.current;
		}

		bool operator==(const Iterator& other) const {
			return current == other.current;
		}
	};

	Iterator begin() {
		return Iterator(root);
	}

	Iterator end() {
		return Iterator();
	}

	friend std::ostream& operator<<(std::ostream& os, BinarySearchTree& tree) {
		for (auto it = tree.begin(); it != tree.end(); ++it) {
			os << "[" << it->key << ": " << it->value << "] ";
		}
		return os;
	}
};