#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <string>
#include <iostream>

// Node structure of Splay Tree
template<typename K, typename V>
struct Node {
    K key;
    V value;
    Node<K, V>* left, * right, * parent;

    Node(const K& key, const V& value) : key(key), value(value), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Splay Tree based associative array class
template<typename K, typename V>
class SplayTree {
public:
    SplayTree() : root(nullptr) {}
    ~SplayTree() {
        destroyTree(root);
    }

    void add(K& key, const V& value) {
        Node<K, V>* z = root;
        Node<K, V>* p = nullptr;

        while (z != nullptr) {
            p = z;
            if (z->key > key) z = z->left;
            else if (z->key < key) z = z->right;
            else {
                z->value = value;
                return;
            }
        }

        z = new Node<K, V>(key, value);
        z->parent = p;

        if (p == nullptr) root = z;
        else if (p->key > z->key) p->left = z;
        else p->right = z;

        splay(z);
    }

    K find(const K& key) {
        Node<K, V>* res = findNode(root, key);
        if (res != nullptr) {
            splay(res);
            return res->value;
        }
        else {
            return "";
        }
    }

    void remove(const K& key) {
        Node<K, V>* z = findNode(root, key);
        if (z == nullptr) return;

        splay(z);

        Node<K, V>* leftSubtree = z->left;
        Node<K, V>* rightSubtree = z->right;

        if (leftSubtree != nullptr) leftSubtree->parent = nullptr;
        if (rightSubtree != nullptr) rightSubtree->parent = nullptr;

        if (leftSubtree != nullptr) {
            root = leftSubtree;

            Node<K, V>* maxNode = root;
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
    Node<K, V>* root;

    void splay(Node<K, V>* node) {
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

    Node<K, V>* rotateLeft(Node<K, V>* x) {
        Node<K, V>* y = x->right;
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

    Node<K, V>* rotateRight(Node<K, V>* x) {
        Node<K, V>* y = x->left;
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

    Node<K, V>* findNode(Node<K, V>* node, const std::string& key) {
        while (node != nullptr) {
            if (node->key > key) node = node->left;
            else if (node->key < key) node = node->right;
            else return node;
        }
        return nullptr;
    }

    void replaceNode(Node<K, V>* oldNode, Node<K, V>* newNode) {
        if (oldNode->parent == nullptr) root = newNode;
        else if (oldNode == oldNode->parent->left) oldNode->parent->left = newNode;
        else oldNode->parent->right = newNode;
        if (newNode != nullptr) newNode->parent = oldNode->parent;
    }

    void destroyTree(Node<K, V>* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
};

#endif // SPLAYTREE_H