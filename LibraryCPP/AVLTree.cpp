//
// Created by KirilliriK on 21.10.2021.
//

#include "AVLTree.h"

AVLTree::AVLTree() {
    middle = nullptr;
}

void AVLTree::addNode(const std::string &str) {
    middle = insert(middle, str);
}

AVLTree::Node *AVLTree::findNode(const std::string &str) {
    if (middle == nullptr) return nullptr;

    return find(middle, str);
}

void AVLTree::removeNode(const std::string &str) {
    if (middle == nullptr) return;

    middle = remove(middle, str);
}

bool AVLTree::isCorrectTree() {
    return isCorrectNode(middle);
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
    if (node == nullptr) return nullptr;

    Node *tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    updateHeight(node);
    updateHeight(tmp);
    return tmp;
}

AVLTree::Node *AVLTree::rotateRight(AVLTree::Node *node) {
    if (node == nullptr) return nullptr;

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

AVLTree::Node *AVLTree::insert(Node *node, const std::string &str) {
    if (node == nullptr) return new Node(str);

    if (str.compare(node->str) < 0) {
        node->left = insert(node->left, str);
    } else {
        node->right = insert(node->right, str);
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

AVLTree::Node *AVLTree::remove(AVLTree::Node *node, const std::string &str) {
    if (node == nullptr) return nullptr;

    if (str.compare(node->str) < 0) {
        node->left = remove(node->left, str);
    } else if (str.compare(node->str) > 0) {
        node->right = remove(node->right, str);
    } else {
        Node *left = node->left;
        Node *right = node->right;
        node->preDelete();
        delete node;
        if (right == nullptr) return left;

        Node *minNode = findMinimal(right);
        minNode->right = setMinimal(right);
        minNode->left = left;
        return balance(minNode);
    }

    return balance(node);
}

AVLTree::Node *AVLTree::find(AVLTree::Node *node, const std::string &str) {
    if (node == nullptr) return nullptr;

    if (str.compare(node->str) < 0) {
        return find(node->left, str);
    } else if (str.compare(node->str) > 0) {
        return find(node->right, str);
    } else return node;
}

bool AVLTree::isCorrectNode(Node *node) {
    if (node == nullptr) return true;
    bool childrenCorrect = isCorrectNode(node->left) && isCorrectNode(node->right);
    updateHeight(node);
    bool correct = balanceFactor(node) != 2 && balanceFactor(node) != -2;
    return correct && childrenCorrect;
}