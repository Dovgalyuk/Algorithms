#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdlib.h>
#include <iostream>
#include <cmath>

typedef std::string Data;
typedef std::string Key;

struct Node;

// Create new node
Node* node_create(const Data& data, const Key& key);

// Inserts a new node into the tree and balances the tree
// Uses recursion
Node* node_insert(Node* node, const Data& data, const Key& key);

// Balances each node using small and big rotations
Node* node_balance(Node* node);

// Returns true if the tree is balanced
bool node_isBalanced(Node* node);

// Corrects the height of the node
// Required for balancing the tree
void node_fixHeight(Node* node);

// Returns the difference between the left subtree and the right subtree
// Required for balancing the tree 
int8_t node_getBalance(Node* node);

// Returns the node height
// Required for balancing the tree
int8_t node_getHeight(Node* node);

// Returns the maximum height of the node
// Required for balancing the tree
int8_t node_getMaxHeight(const int8_t leftHeight, const int8_t rightHeight);

// Returns a pointer to a subtree balanced by a left small rotation
Node* node_smallLeftRotate(Node* aNode);

// Returns a pointer to a subtree balanced by a right small rotation
Node* node_smallRightRotate(Node* aNode);

// Returns a pointer to a subtree balanced by a left big rotation
Node* node_bigLeftRotate(Node* aNode);

// Returns a pointer to a subtree balanced by a right big rotation
Node* node_bigRightRotate(Node* aNode);

// Returns a pointer to the left node of the parent node
Node* node_getLeftChild(Node* node);

// Returns a pointer to the right node of the parent node
Node* node_getRightChild(Node* node);

// Returns the data of currect node
Data node_getData(Node* node);

// Returns a pointer to the node by key
// Uses recursion
Node* node_search(Node* node, const Key& key);

// Returns a pointer to the minimum node by key
// Uses recursion
Node* node_findMin(Node* node);

// Returns a pointer to the minimum parent node by key
// Uses recursion
Node* node_findMinParent(Node* fromNode, Node* toNode);

// Deletes a node by key
// Uses recursion
Node* node_remove(Node* node, const Key& key);

// Delete tree, free memory
// Uses recursion
Node* node_delete(Node* node);

// Outputs the value of tree nodes to the terminal
// Uses recursion
void node_printTree(Node* node, unsigned height);

#endif
