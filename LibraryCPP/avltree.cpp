#include "avltree.h"
#include <algorithm>
#include <iostream>

AVLTree::AVLTree() : root(nullptr), size_(0) {}

AVLTree::~AVLTree() {
    clear();
}

int AVLTree::height(const std::shared_ptr<Node>& node) const {
    return node ? node->height : 0;
}

int AVLTree::balanceFactor(const std::shared_ptr<Node>& node) const {
    return node ? height(node->left) - height(node->right) : 0;
}

void AVLTree::updateHeight(std::shared_ptr<Node>& node) {
    if (node) {
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }
}

std::shared_ptr<AVLTree::Node> AVLTree::rotateRight(std::shared_ptr<Node>& y) {
    std::shared_ptr<Node> x = y->left;
    std::shared_ptr<Node> T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

std::shared_ptr<AVLTree::Node> AVLTree::rotateLeft(std::shared_ptr<Node>& x) {
    std::shared_ptr<Node> y = x->right;
    std::shared_ptr<Node> T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

std::shared_ptr<AVLTree::Node> AVLTree::balance(std::shared_ptr<Node>& node) {
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
    size_t oldSize = size_;
    root = insert(root, key);
    return size_ > oldSize;
}

std::shared_ptr<AVLTree::Node> AVLTree::insert(std::shared_ptr<Node>& node, const std::string& key) {
    if (!node) {
        size_++;
        return std::make_shared<Node>(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key);
    }
    else {
        node->count++;
        size_++;
        return node;
    }

    return balance(node);
}

bool AVLTree::remove(const std::string& key) {
    if (!root) return false;

    size_t oldSize = size_;
    root = remove(root, key);
    return size_ < oldSize;
}

std::shared_ptr<AVLTree::Node> AVLTree::remove(std::shared_ptr<Node>& node, const std::string& key) {
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
        if (node->count > 1) {

            node->count--;
            size_--;
            return node;
        }

        if (!node->left || !node->right) {
            std::shared_ptr<Node> temp = node->left ? node->left : node->right;

            if (!temp) {
                node = nullptr;
            }
            else {
                node = temp;
            }
            size_--;
        }
        else {
            std::shared_ptr<Node> temp = findMin(node->right);
            node->key = temp->key;
            node->count = temp->count;

            node->right = remove(node->right, temp->key);
        }
    }

    if (!node) {
        return nullptr;
    }

    return balance(node);
}

std::shared_ptr<AVLTree::Node> AVLTree::findMin(std::shared_ptr<Node>& node) {
    return node->left ? findMin(node->left) : node;
}

std::shared_ptr<AVLTree::Node> AVLTree::removeMin(std::shared_ptr<Node>& node) {
    if (!node->left) {
        std::shared_ptr<Node> temp = node->right;
        node = nullptr;
        size_--;
        return temp;
    }

    node->left = removeMin(node->left);
    return balance(node);
}

bool AVLTree::contains(const std::string& key) const {
    return contains(root, key);
}

bool AVLTree::contains(const std::shared_ptr<Node>& node, const std::string& key) const {
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

void AVLTree::clear(std::shared_ptr<Node>& node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        node.reset();
    }
}

std::vector<std::string> AVLTree::getAllElements() const {
    std::vector<std::string> result;
    result.reserve(size_);
    inOrderTraversal(root, result);
    return result;
}

void AVLTree::inOrderTraversal(const std::shared_ptr<Node>& node, std::vector<std::string>& result) const {
    if (node) {
        inOrderTraversal(node->left, result);
        for (int i = 0; i < node->count; ++i) {
            result.push_back(node->key);
        }
        inOrderTraversal(node->right, result);
    }
}

int AVLTree::getHeight() const {
    return height(root);
}

bool AVLTree::isBalanced() const {
    return isBalanced(root);
}

bool AVLTree::isBalanced(const std::shared_ptr<Node>& node) const {
    if (!node) {
        return true;
    }

    int bf = balanceFactor(node);
    if (bf < -1 || bf > 1) {
        return false;
    }

    return isBalanced(node->left) && isBalanced(node->right);
}

bool AVLTree::isBST() const {
    return isBST(root, "", "");
}

bool AVLTree::isBST(const std::shared_ptr<Node>& node, const std::string& min, const std::string& max) const {
    if (!node) {
        return true;
    }

    if ((!min.empty() && node->key <= min) || (!max.empty() && node->key >= max)) {
        return false;
    }

    return isBST(node->left, min, node->key) && isBST(node->right, node->key, max);
}