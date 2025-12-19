#include "avltree.h"
#include <algorithm>
#include <iostream>
#include <cassert>

AVLTree::AVLTree() : root(nullptr), size_(0) {}

AVLTree::~AVLTree() {
    clear();
}

int AVLTree::height(const Node* node) const {
    return node ? node->height : 0;
}

int AVLTree::balanceFactor(const Node* node) const {
    return node ? height(node->left) - height(node->right) : 0;
}

void AVLTree::updateHeight(Node* node) {
    if (node) {
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }
}

AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

AVLTree::Node* AVLTree::balance(Node* node) {
    if (!node) return nullptr;

    updateHeight(node);

    int bf = balanceFactor(node);

    if (bf > 1 && balanceFactor(node->left) >= 0) {
        return rotateRight(node);
    }

    if (bf < -1 && balanceFactor(node->right) <= 0) {
        return rotateLeft(node);
    }

    if (bf > 1 && balanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (bf < -1 && balanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

bool AVLTree::insert(const std::string& key) {
    if (contains(key)) {
        return false;
    }

    size_++;
    root = insert(root, key);
    return true;
}

AVLTree::Node* AVLTree::insert(Node* node, const std::string& key) {
    if (!node) {
        return new Node(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key);
    }
    else {
        return node;
    }

    return balance(node);
}

bool AVLTree::remove(const std::string& key) {
    if (!contains(key)) {
        return false;
    }

    size_--;
    root = remove(root, key);
    return true;
}

AVLTree::Node* AVLTree::remove(Node* node, const std::string& key) {
    if (!node) {
        return nullptr;
    }

    if (key < node->key) {
        node->left = remove(node->left, key);
    }
    else if (key > node->key) {
        node->right = remove(node->right, key);
    }
    else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            node = temp;
        }
        else {
            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }
    }

    if (!node) {
        return nullptr;
    }

    return balance(node);
}

AVLTree::Node* AVLTree::findMin(Node* node) {
    return node->left ? findMin(node->left) : node;
}

AVLTree::Node* AVLTree::removeMin(Node* node) {
    if (!node->left) {
        Node* temp = node->right;
        delete node;
        return temp;
    }

    node->left = removeMin(node->left);
    return balance(node);
}

bool AVLTree::contains(const std::string& key) const {
    return contains(root, key);
}

bool AVLTree::contains(const Node* node, const std::string& key) const {
    if (!node) {
        return false;
    }

    if (key < node->key) {
        return contains(node->left, key);
    }
    else if (key > node->key) {
        return contains(node->right, key);
    }
    else {
        return true;
    }
}

size_t AVLTree::size() const {
    return size_;
}

bool AVLTree::empty() const {
    return size_ == 0;
}

void AVLTree::clear() {
    clear(root);
    root = nullptr;
    size_ = 0;
}

void AVLTree::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

std::vector<std::string> AVLTree::getAllElements() const {
    std::vector<std::string> result;
    result.reserve(size_);
    inOrderTraversal(root, result);
    return result;
}

void AVLTree::inOrderTraversal(const Node* node, std::vector<std::string>& result) const {
    if (node) {
        inOrderTraversal(node->left, result);
        result.push_back(node->key);
        inOrderTraversal(node->right, result);
    }
}

int AVLTree::getHeight() const {
    return height(root);
}

bool AVLTree::isBalanced() const {
    return isBalancedRecursive(root);
}

bool AVLTree::isBalancedRecursive(const Node* node) const {
    if (!node) {
        return true;
    }

    int bf = balanceFactor(node);
    if (bf < -1 || bf > 1) {
        return false;
    }

    return isBalancedRecursive(node->left) && isBalancedRecursive(node->right);
}

bool AVLTree::isBST() const {
    return isBSTRecursive(root, "", "");
}

bool AVLTree::isBSTRecursive(const Node* node, const std::string& min, const std::string& max) const {
    if (!node) {
        return true;
    }

    if ((!min.empty() && node->key <= min) || (!max.empty() && node->key >= max)) {
        return false;
    }

    return isBSTRecursive(node->left, min, node->key) && isBSTRecursive(node->right, node->key, max);
}