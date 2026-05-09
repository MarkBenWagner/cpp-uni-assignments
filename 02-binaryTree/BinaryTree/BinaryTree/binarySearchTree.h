#pragma once
#include "customExceptions.h"
#include <ostream>


template<typename Key, typename Value>
struct Node {
	Key key;
	Value value;
	Node* left;
	Node* right;

	Node(const Key& key, const Value& value)
		: key(key), value(value), left(nullptr), right(nullptr)
	{
	}
};


template<typename T>
class Stack {
private:
	struct StackNode {
		T data;
		StackNode* next;
		StackNode(T data, StackNode* next)
			: data(data), next(next) {}
	};
	StackNode* top;

public:
	Stack() : top(nullptr) {}

	~Stack() {
		clear();
	}

	Stack(const Stack& other) : top(nullptr) {
		if (other.top == nullptr) return;
		top = new StackNode(other.top->data, nullptr);
		StackNode* current = top;
		StackNode* second = other.top->next;
		while (second != nullptr) {
			current->next = new StackNode(second->data, nullptr);
			current = current->next;
			second = second->next;
		}
	}

	Stack& operator=(const Stack& other) {
		if (this == &other) return *this;
		clear();
		if (other.top == nullptr) return *this;
		top = new StackNode(other.top->data, nullptr);
		StackNode* current = top;
		StackNode* second = other.top->next;
		while (second != nullptr) {
			current->next = new StackNode(second->data, nullptr);
			current = current->next;
			second = second->next;
		}
		return *this;
	}

	void push(T value) {
		top = new StackNode(value, top);
	}

	T pop() {
		StackNode* temp = top;
		T value = temp->data;
		top = top->next;
		delete temp;
		return value;
	}

	bool empty() const {
		return top == nullptr;
	}

	void clear() {
		while (!empty()) {
			pop();
		}
	}
};



template<typename Key, typename Value>
class BinarySearchTree {
private:
	Node<Key, Value>* root;

public:
	BinarySearchTree() : root(nullptr) {}

	~BinarySearchTree() {
		clear();
	}

	BinarySearchTree(const BinarySearchTree& other) {
		root = copyNodes(other.root);
	}

	BinarySearchTree(BinarySearchTree&& other) noexcept : root(other.root) {
		other.root = nullptr;
	}

	BinarySearchTree& operator=(const BinarySearchTree& other) {
		if (this == &other) {
			return *this;
		}
		clear();
		root = copyNodes(other.root);
		return *this;
	}

	BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
		if (this == &other) {
			return *this;
		}

		clear();
		root = other.root;
		other.root = nullptr;
		return *this;
	}

private:
	Node<Key, Value>* copyNodes(Node<Key, Value>* p) {
		if (p == nullptr) {
			return nullptr;
		}
		Node<Key, Value>* newNode = new Node<Key, Value>(p->key, p->value);

		newNode->left = copyNodes(p->left);
		newNode->right = copyNodes(p->right);
		return newNode;
	}


public:
	void clear() 
	{
		PostOrder(root);
		root = nullptr;
	}
private:
	void PostOrder(Node<Key, Value>* p) {
		if (p != nullptr) {
			PostOrder(p->left);
			PostOrder(p->right);
			delete p;
		}
	}

public:
	bool contains(const Key& key) const {

		Node<Key, Value>* current = root;

		while (current != nullptr) {
			if (key == current->key) {
				return true;
			} 
			else {
				if (key < current->key) {
					current = current->left;
				}
				else {
					current = current->right;
				}
			}
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
			if (key == current->key) {
				return false;
			}

			if (key < current->key) {
				if (current->left == nullptr) {
					current->left = new Node<Key, Value>(key, value);
					return true;
				}
				else {
					current = current->left;
				}
			}
			else {
				if (current->right == nullptr) {
					current->right = new Node<Key, Value>(key, value);
					return true;
				}
				else {
					current = current->right;
				}
			}
		}
		return false;
	}

	Value& operator[](const Key& key) 
	{
		Node<Key, Value>* current = root;

		if (current == nullptr) {
			root = new Node<Key, Value>(key, Value());
			return root->value;
		}

		while (true) {
			if (current->key == key) {
				return current->value;
			}
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
			if (key == current->key) {
				return current->value;
			}
			if (key < current->key) {
				current = current->left;
			}
			else {
				current = current->right;
			}
		}
		throw KeyNotFoundException();
	}
private:
	Node<Key, Value>* removeHelper(Node<Key, Value>* node, const Key& key, bool& isDone) {
		if (node == nullptr) {
			isDone = false;
			return nullptr;
		}

		if (key == node->key) {
			isDone = true;

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

			node->right = removeHelper(node->right, temp->key, isDone);
		}
		else if (key < node->key) {
			node->left = removeHelper(node->left, key, isDone);
		}
		else {
			node->right = removeHelper(node->right, key, isDone);
		}

		return node;
	}

public:
	bool remove(const Key& key) {
		bool isDone = false;
		root = removeHelper(root, key, isDone);
		return isDone;
	}

	bool empty() const {
		return root == nullptr;
	}

	friend std::ostream& operator<<(std::ostream& os, BinarySearchTree& bst) {
		os << "{ ";
		for (auto node : bst) {
			os << "[" << node.key << ": " << node.value << "] ";
		}
		os << "}";
		return os;
	}


public:
	class Iterator {
	private:
		Stack<Node<Key, Value>*> stack;
		Node<Key, Value>* current;

		void pushLeft(Node<Key, Value>* node) {
			while (node != nullptr) {
				stack.push(node);
				node = node->left;
			}
		}

	public:
		Iterator(Node<Key, Value>* root)
			: current(nullptr) {
			pushLeft(root);
			if (!stack.empty()) {
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
				pushLeft(current->right);
			}

			if (!stack.empty()) {
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

		bool operator==(const Iterator& other) const {
			return current == other.current;
		}

		bool operator!=(const Iterator& other) const {
			return current != other.current;
		}

	};

	Iterator begin() {
		return Iterator(root);
	}
	Iterator end() {
		return Iterator();
	}

};

