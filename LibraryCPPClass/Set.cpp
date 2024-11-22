#include "Set.h"

// Interface of inserting a new node
void Set::insert(std::string str) {
	Node* newNode = new Node(str, nullNode);
	root = insert_(root, newNode);
	balance();
}

// Inserting a new node
Node* Set::insert_(Node* node, Node* newNode) {
	if (node == nullptr || node == nullNode)
		return newNode;

	if (node->value > newNode->value) {
		root->left = insert_(node->left, newNode);
		root->left->parent = root;
	}
	else if(node->value < newNode->value){
		root->right = insert_(node->right, newNode);
		root->right->parent = root;
	}

	return node;
}

// Interface of searching a new node with specified value
const Node* Set::find(std::string str) {
	return find_(root, str);
}

// Finds a node by value
const Node* Set::find_(const Node* node, std::string str) {
	if (node == nullNode)
		return nullptr;

	if (node->value == str)
		return node;

	const Node* temp = find_(node->left, str);
	if (temp != nullptr)
		return temp;

	return find_(node->right, str);
}

// Interface of removing a node with specified value
void Set::remove(std::string str) {
	remove_((Node*)find(str));
}

// Removes a node by value
void Set::remove_(Node* node) {

}

void Set::balance() {

}

// Getting const ref to the root
const Node* Set::get_root() {
	return root;
}

Node* Set::get_null() {
	return nullNode;
}
