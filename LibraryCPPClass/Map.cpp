#include "Map.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>


int AssociativeArray::height(Node* node) {
    return node ? node->height : 0;
}

int AssociativeArray::balanceFactor(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

void AssociativeArray::fixHeight(Node* node) {
    int hLeft = height(node->left);
    int hRight = height(node->right);
    node->height = std::max(hLeft, hRight) + 1;
}

AssociativeArray::Node* AssociativeArray::rotateRight(Node* node) {
    if (node == nullptr || node->left == nullptr) {
        throw std::runtime_error("Cannot perform right rotation");
    }

    Node* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;

    fixHeight(node);
    fixHeight(leftChild);

    return leftChild; 
}

AssociativeArray::Node* AssociativeArray::rotateLeft(Node* node) {
    if (node == nullptr || node->right == nullptr) {
        throw std::runtime_error("Cannot perform left rotation");
    }

    Node* rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;

    fixHeight(node);
    fixHeight(rightChild);

    return rightChild;
}


AssociativeArray::Node* AssociativeArray::balance(Node* node) {
    fixHeight(node);
    int balance = balanceFactor(node);

    if (balance > 1 && balanceFactor(node->left) >= 0) {
        return rotateRight(node);
    }
   
    if (balance < -1 && balanceFactor(node->right) <= 0) {
        return rotateLeft(node);
    }

    if (balance > 1 && balanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

 
    if (balance < -1 && balanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node; 
}


AssociativeArray::Node* AssociativeArray::insert(Node* node, const std::string& key, const std::string& value) {
    if (!node) {
        return new Node(key, value);
    }

    if (key < node->key) {
        node->left = insert(node->left, key, value);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key, value);
    }
    else {
        node->value = value; 
    }

    return balance(node);
}

AssociativeArray::Node* AssociativeArray::find(Node* node, const std::string& key) const {
    if (!node) {
        throw std::runtime_error("this node does not exist");
    }

    if (key == node->key) {
        return node;
    }

    else if (key < node->key) {
        return find(node->left, key);
    }

    else {
        return find(node->right, key);
    }
}

AssociativeArray::Node* AssociativeArray::remove(Node* node, const std::string& key) {
    if (node == nullptr) {
        return nullptr;
    }

    if (key < node->key) {
        node->left = remove(node->left, key);
    }
    else if (key > node->key) {
        node->right = remove(node->right, key);
    }
    else {
       
        Node* leftChild = node->left;
        Node* rightChild = node->right;

        delete node; 

        if (rightChild == nullptr) {
            return leftChild;
        }

        if (leftChild == nullptr) {
            return rightChild;
        }

        Node* minNode = rightChild;
        while (minNode->left != nullptr) {
            minNode = minNode->left;
        }

        node->key = minNode->key;
        node->value = minNode->value;

        node->right = remove(node->right, minNode->key);
    }

    fixHeight(node);
    return balance(node);
}


int AssociativeArray::countNodes(Node* node) const {
    if (node == nullptr) {
        return 0;
    }
    return 1 + countNodes(node->left) + countNodes(node->right); 
}

AssociativeArray::AssociativeArray() : root(nullptr) {}

AssociativeArray::~AssociativeArray() {
    clear(root); 
}


void AssociativeArray::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node; 
    }
}

void AssociativeArray::insert(const std::string& key, const std::string& value) {
    root = insert(root, key, value);
}

std::string AssociativeArray::find(const std::string& key) const {
    Node* result = find(root, key);
    return result ? result->value : "";
}

void AssociativeArray::remove(const std::string& key) {
    root = remove(root, key);
}

int AssociativeArray::countNodes() const {
    return countNodes(root); 
}

