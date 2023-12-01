#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <string>
#include <iostream>

// Node structure of Splay Tree
struct Node {
    std::string key;
    std::string value;
    Node* left, * right, * parent;

    Node(const std::string& key, const std::string& value) : key(key), value(value), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Splay Tree based associative array class
class SplayTree {
public:
    SplayTree() : root(nullptr) {}
    ~SplayTree() {
        destroyTree(root);
    }

    void add(const std::string& key, const std::string& value) {
        Node* z = root;
        Node* p = nullptr;

        while (z != nullptr) {
            p = z;
            if (z->key > key) z = z->left;
            else if (z->key < key) z = z->right;
            else {
                z->value = value;
                return;
            }
        }

        z = new Node(key, value);
        z->parent = p;

        if (p == nullptr) root = z;
        else if (p->key > z->key) p->left = z;
        else p->right = z;

        splay(z);
    }

    std::string find(const std::string& key) {
        Node* res = findNode(root, key);
        if (res != nullptr) {
            splay(res);
            return res->value;
        }
        else {
            return "";
        }
    }

    void remove(const std::string& key) {
        Node* z = findNode(root, key);
        if (z == nullptr) return;

        splay(z);

        Node* leftSubtree = z->left;
        Node* rightSubtree = z->right;

        if (leftSubtree != nullptr) leftSubtree->parent = nullptr;
        if (rightSubtree != nullptr) rightSubtree->parent = nullptr;

        if (leftSubtree != nullptr) {
            root = leftSubtree;

            Node* maxNode = root;
            while (maxNode->right != nullptr) maxNode = maxNode->right;

            splay(maxNode);
            maxNode->right = rightSubtree;
            if (rightSubtree != nullptr) rightSubtree->parent = maxNode;
        }
        else {
            root = rightSubtree;
        }

        delete z;
    }

private:
    Node* root;

    void splay(Node* node) {
        while (node->parent != nullptr) {
            if (node->parent->parent == nullptr) {
                if (node->parent->left == node) rotateRight(node->parent);
                else rotateLeft(node->parent);
            }
            else if (node->parent->left == node && node->parent->parent->left == node->parent) {
                rotateRight(node->parent->parent);
                rotateRight(node->parent);
            }
            else if (node->parent->right == node && node->parent->parent->right == node->parent) {
                rotateLeft(node->parent->parent);
                rotateLeft(node->parent);
            }
            else if (node->parent->left == node && node->parent->parent->right == node->parent) {
                rotateRight(node->parent);
                rotateLeft(node->parent);
            }
            else {
                rotateLeft(node->parent);
                rotateRight(node->parent);
            }
        }
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
        return y;
    }

    Node* rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nullptr) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
        return y;
    }

    Node* findNode(Node* node, const std::string& key) {
        while (node != nullptr) {
            if (node->key > key) node = node->left;
            else if (node->key < key) node = node->right;
            else return node;
        }
        return nullptr;
    }

    void replaceNode(Node* oldNode, Node* newNode) {
        if (oldNode->parent == nullptr) root = newNode;
        else if (oldNode == oldNode->parent->left) oldNode->parent->left = newNode;
        else oldNode->parent->right = newNode;
        if (newNode != nullptr) newNode->parent = oldNode->parent;
    }

    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
};

#endif // SPLAYTREE_H