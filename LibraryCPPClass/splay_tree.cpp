#include "splay_tree.h"

SplayTree::SplayTree() : root_(nullptr) {}

SplayTree::~SplayTree() {
    delete_tree(root_);
}

void SplayTree::delete_tree(Node* node) {
    while (node) {
        if (node->left) {
            Node* left = node->left;
            node->left = left->right;
            left->right = node;
            node = left;
        } else {
            Node* right = node->right;
            delete node;
            node = right;
        }
    }
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
    if (!root) return;

    Node header("");
    Node* leftTreeMax = &header;
    Node* rightTreeMin = &header;
        
    Node* t = root;
    header.left = header.right = nullptr;
    
    while (true) {
        if (key < t->key) {
            if (!t->left) break;
            if (key < t->left->key) {
                // Zig-Zig: Rotate right first
                rotate_right(t);
                if (!t->left) break;
            }
            // Link to Right Tree
            rightTreeMin->left = t;
            rightTreeMin = t;
            t = t->left;
        } else if (key > t->key) {
            if (!t->right) break;
            if (key > t->right->key) {
                // Zig-Zig: Rotate left first
                rotate_left(t);
                if (!t->right) break;
            }
            // Link to Left Tree
            leftTreeMax->right = t;
            leftTreeMax = t;
            t = t->right;
        } else {
            break; // Found
        }
    }
    
    // Assemble
    leftTreeMax->right = t->left;
    rightTreeMin->left = t->right;
    t->left = header.right;
    t->right = header.left;
    
    root = t;
}

void SplayTree::insert(const std::string& key) {
    if (!root_) {
        root_ = new Node(key);
        return;
    }

    splay(root_, key);

    if (root_->key == key) return; // Уже есть

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
    
    splay(root_, key); // Если элемент есть, он теперь в корне

    if (root_->key != key) return;

    Node* temp = root_;
    if (!root_->left) {
        root_ = root_->right;
    } else {
        // Splay max element in left subtree
        Node* left_root = root_->left;
        splay(left_root, key); // Ключ key гарантированно больше всех в левом поддереве, поэтому splay поднимет MAX
        left_root->right = root_->right;
        root_ = left_root;
    }
    delete temp;
}
