#pragma once

#include <string>

enum Colour { BLACK, RED };

struct Node {
	Node(std::string str, Node* nullNode) : left(nullNode), right(nullNode), parent(nullptr), colour(RED), value(str) {};
	Node() : left(nullptr), right(nullptr), parent(nullptr), colour(BLACK) {};

	~Node() {
		delete left;
		delete right;
	}

	Node* left;
	Node* right;
	Node* parent;
	Colour colour;
	std::string value;
};

class Set {
public:
	Set() : nullNode(new Node()), root(nullptr) {};
	~Set() {}

	// Interface of inserting a new node
	void insert(std::string);

	// Interface of searching a new node with a specified value
	const Node* find(std::string);

	// Interface of removing a node with a specified value
	void remove(std::string);

	// Getting const ref to the root
	const Node* get_root();

	// Retrieves nullNode pointer
	Node* get_null();

private:
	Node* nullNode;
	Node* root;

	// Inserting a new node
	Node* insert_(Node*, Node*);

	// Finds a node by value
	const Node* find_(const Node*, std::string);

	// Removes a node by value
	void remove_(Node*);

	// Balances the red-black tree
	void balance();
};