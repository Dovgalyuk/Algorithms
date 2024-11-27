#include "Set.h"

// Insert a value into Red-Black Tree
void Set::insert(std::string key)
{
    Node* node = new Node(key);
    Node* parent = nullptr;
    Node* current = root;
    while (current != nullptr) {
        parent = current;
        if (node->data < current->data)
            current = current->left;
        else
            current = current->right;
    }
    node->parent = parent;
    if (parent == nullptr)
        root = node;
    else if (node->data < parent->data)
        parent->left = node;
    else
        parent->right = node;
    balanceAfterInsert(node);
}

// Find a Node with specified value
const Node* Set::find(std::string key) {
    Node* current = root;
    while (current != nullptr && current->data != key) {
        if (key < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return current;
}

// Remove a value from Red-Black Tree
void Set::remove(std::string key)
{
    Node* node = root;
    Node* z = nullptr;
    Node* x = nullptr;
    Node* y = nullptr;
    while (node != nullptr) {
        if (node->data == key) {
            z = node;
        }

        if (node->data <= key) {
            node = node->right;
        }
        else {
            node = node->left;
        }
    }

    if (z == nullptr) {
        std::cout << "Key not found in the tree" << std::endl;
        return;
    }

    y = z;
    Color yOriginalColor = y->color;
    if (z->left == nullptr) {
        x = z->right;
        transplant(root, z, z->right);
    }
    else if (z->right == nullptr) {
        x = z->left;
        transplant(root, z, z->left);
    }
    else {
        y = minValueNode(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != nullptr)
                x->parent = y;
        }
        else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (yOriginalColor == BLACK) {
        balanceAfterDelete(x);
    }
}

// Left Rotation
void Set::rotateLeft(Node*& node)
{
    Node* child = node->right;
    node->right = child->left;
    if (node->right != nullptr)
        node->right->parent = node;
    child->parent = node->parent;
    if (node->parent == nullptr)
        root = child;
    else if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;
    child->left = node;
    node->parent = child;
}

// Right Rotation
void Set::rotateRight(Node*& node)
{
    Node* child = node->left;
    node->left = child->right;
    if (node->left != nullptr)
        node->left->parent = node;
    child->parent = node->parent;
    if (node->parent == nullptr)
        root = child;
    else if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;
    child->right = node;
    node->parent = child;
}

// Fixing Insertion Violation
void Set::balanceAfterInsert(Node*& node)
{
    Node* parent = nullptr;
    Node* grandparent = nullptr;
    while (node != root && node->color == RED
        && node->parent->color == RED) {
        parent = node->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;
            if (uncle != nullptr
                && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            }
            else {
                if (node == parent->right) {
                    rotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateRight(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
        else {
            Node* uncle = grandparent->left;
            if (uncle != nullptr
                && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            }
            else {
                if (node == parent->left) {
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateLeft(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }
    root->color = BLACK;
}

// Fixing Deletion Violation
void Set::balanceAfterDelete(Node*& node)
{
    while (node != root && node != nullptr && node->color == BLACK) {
        if (node == node->parent->left) {
            Node* sibling = node->parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotateLeft(node->parent);
                sibling = node->parent->right;
            }
            if ((sibling->left == nullptr || sibling->left->color == BLACK) && (sibling->right == nullptr || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = node->parent;
            }
            else {
                if (sibling->right == nullptr || sibling->right->color == BLACK) {
                    if (sibling->left != nullptr)
                        sibling->left->color = BLACK;
                    sibling->color = RED;
                    rotateRight(sibling);
                    sibling = node->parent->right;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                if (sibling->right != nullptr)
                    sibling->right->color = BLACK;
                rotateLeft(node->parent);
                node = root;
            }
        }
        else {
            Node* sibling = node->parent->left;
            if (sibling != nullptr && sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotateRight(node->parent);
                sibling = node->parent->left;
            }
            if (sibling != nullptr && (sibling->left == nullptr || sibling->left->color == BLACK) && (sibling->right == nullptr || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = node->parent;
            }
            else if (sibling != nullptr) {
                if (sibling->left == nullptr || sibling->left->color == BLACK) {
                    if (sibling->right != nullptr)
                        sibling->right->color = BLACK;
                    sibling->color = RED;
                    rotateLeft(sibling);
                    sibling = node->parent->left;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                if (sibling->left != nullptr)
                    sibling->left->color = BLACK;
                rotateRight(node->parent);
                node = root;
            }
        }
    }
    if(node != nullptr)
        node->color = BLACK;
}

// Find Node with Minimum Value
Node* Set::minValueNode(Node*& node)
{
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Transplant nodes in Red-Black Tree
void Set::transplant(Node*& root, Node*& u, Node*& v)
{
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
}

// Delete all nodes in the Red-Black Tree
void Set::deleteTree(Node* node)
{
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}