#include "splay_tree.h"

SplayTree::SplayTree() : root_(nullptr) {}

SplayTree::~SplayTree() {
    delete_tree(root_);
}

void SplayTree::delete_tree(Node* node) {
    if (!node) return;
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
}

void SplayTree::rotate_right(Node*& node) {
    Node* left_child = node->left;
    node->left = left_child->right;
    left_child->right = node;
    node = left_child;
}

void SplayTree::rotate_left(Node*& node) {
    Node* right_child = node->right;
    node->right = right_child->left;
    right_child->left = node;
    node = right_child;
}

void SplayTree::splay(Node*& root, const std::string& key) {
    if (!root || root->key == key) return;

    if (key < root->key) {
        if (!root->left) return;
        // Zig-Zig (Left Left)
        if (key < root->left->key) {
            splay(root->left->left, key);
            rotate_right(root);
        }
        // Zig-Zag (Left Right)
        else if (key > root->left->key) {
            splay(root->left->right, key);
            if (root->left->right) rotate_left(root->left);
        }
        if (root->left) rotate_right(root);
    } else {
        if (!root->right) return;
        // Zag-Zag (Right Right)
        if (key > root->right->key) {
            splay(root->right->right, key);
            rotate_left(root);
        }
        // Zag-Zig (Right Left)
        else if (key < root->right->key) {
            splay(root->right->left, key);
            if (root->right->left) rotate_right(root->right);
        }
        if (root->right) rotate_left(root);
    }
}

void SplayTree::insert(const std::string& key) {
    if (!root_) {
        root_ = new Node(key);
        return;
    }
    splay(root_, key);
    if (root_->key == key) return; // Элемент уже есть

    Node* new_node = new Node(key);
    if (key < root_->key) {
        new_node->right = root_;
        new_node->left = root_->left;
        root_->left = nullptr;
    } else {
        new_node->left = root_;
        new_node->right = root_->right;
        root_->right = nullptr;
    }
    root_ = new_node;
}

bool SplayTree::contains(const std::string& key) {
    if (!root_) return false;
    splay(root_, key);
    return root_->key == key;
}

void SplayTree::remove(const std::string& key) {
    if (!root_) return;
    splay(root_, key);
    if (root_->key != key) return;

    Node* temp = root_;
    if (!root_->left) {
        root_ = root_->right;
    } else {
        Node* left_max = root_->left;
        splay(left_max, key);
        left_max->right = root_->right;
        root_ = left_max;
    }
    delete temp;
}
