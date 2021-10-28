//
// Created by KirilliriK on 21.10.2021.
//

#include "AVLTree.h"

AVLTree::AVLTree() {
    middle = nullptr;
}

void AVLTree::addNode(std::string &str) {
    middle = insert(middle, hash(str), str);
}

void AVLTree::addNode(size_t key) {
    std::string str;
    middle = insert(middle, key, str);
}

AVLTree::Node *AVLTree::findNode(std::string &str) {
    return find(middle, hash(str));
}

AVLTree::Node *AVLTree::findNode(size_t key) {
    return find(middle, key);
}

void AVLTree::removeNode(std::string &str) {
    middle = remove(middle, hash(str));
}

void AVLTree::removeNode(size_t key) {
    middle = remove(middle, key);
}

void AVLTree::clear() {
    delete middle;
    middle = nullptr;
}

int AVLTree::nodeHeight(AVLTree::Node *node) {
    return node != nullptr ? node->height : 0;
}

int AVLTree::balanceFactor(AVLTree::Node *node) {
    if (node == nullptr) return 0;

    return nodeHeight(node->right) - nodeHeight(node->left);
}

void AVLTree::updateHeight(AVLTree::Node *node) {
    int leftHeight = nodeHeight(node->left);
    int rightHeight = nodeHeight(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

AVLTree::Node *AVLTree::rotateLeft(AVLTree::Node *node) {
    Node *tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    updateHeight(node);
    updateHeight(tmp);
    return tmp;
}

AVLTree::Node *AVLTree::rotateRight(AVLTree::Node *node) {
    Node *tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    updateHeight(node);
    updateHeight(tmp);
    return tmp;
}

AVLTree::Node *AVLTree::balance(AVLTree::Node *node) {
    updateHeight(node);
    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->right) < 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    if (balanceFactor(node) == -2) {
        if (balanceFactor(node->left) > 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    return node; // Balance don't need
}

AVLTree::Node *AVLTree::insert(Node *node, size_t key, std::string &str) {
    if (node == nullptr) return new Node(key, str);

    if (key < node->key) {
        node->left = insert(node->left, key, str);
    } else {
        node->right = insert(node->right, key, str);
    }
    return balance(node);
}

AVLTree::Node *AVLTree::findMinimal(AVLTree::Node *node) {
    if (node->left == nullptr) return node;
    return findMinimal(node->left);
}

AVLTree::Node *AVLTree::setMinimal(AVLTree::Node *node) {
    if (node->left == nullptr)
        return node->right;
    node->left = setMinimal(node->left);
    return balance(node);
}

AVLTree::Node *AVLTree::remove(AVLTree::Node *node, size_t key) {
    if (node == nullptr) return nullptr;

    if (key < node->key) {
        node->left = remove(node->left, key);
    } else if (key > node->key) {
        node->right = remove(node->right, key);
    } else {
        Node *left = node->left;
        Node *right = node->right;
        delete node;
        if (right == nullptr) return left;

        Node *minNode = findMinimal(right);
        minNode->right = setMinimal(right);
        minNode->left = left;
        return balance(minNode);
    }

    return balance(node);
}

AVLTree::Node *AVLTree::find(AVLTree::Node *node, size_t key) {
    if (node == nullptr) return nullptr;

    if (key < node->key) {
        return find(node->left, key);
    } else if (key > node->key) {
        return find(node->right, key);
    } else return node;
}

size_t AVLTree::hash(std::string &str) {
    static std::hash<std::string> hasher;
    return hasher(str);
}
