#include "avltree.h"
#include <iostream>
#include <algorithm>

AVLTree::AVLTree() : root(nullptr), cnt(0) {}

AVLTree::~AVLTree() {
    clear(root);
}

void AVLTree::clear(Node* n) {
    if (n) {
        clear(n->l);
        clear(n->r);
        delete n;
    }
}

int AVLTree::height(Node* n) {
    return n ? n->ht : 0;
}

int AVLTree::balance(Node* n) {
    return n ? height(n->l) - height(n->r) : 0;
}

AVLTree::Node* AVLTree::rightRotate(Node* y) {
    Node* x = y->l;
    Node* T2 = x->r;

    x->r = y;
    y->l = T2;

    y->ht = std::max(height(y->l), height(y->r)) + 1;
    x->ht = std::max(height(x->l), height(x->r)) + 1;

    return x;
}

AVLTree::Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->r;
    Node* T2 = y->l;

    y->l = x;
    x->r = T2;

    x->ht = std::max(height(x->l), height(x->r)) + 1;
    y->ht = std::max(height(y->l), height(y->r)) + 1;

    return y;
}

AVLTree::Node* AVLTree::add(Node* n, const std::string& k, const std::string& v) {
    if (!n) return new Node(k, v);

    if (k < n->key)
        n->l = add(n->l, k, v);
    else if (k > n->key)
        n->r = add(n->r, k, v);
    else {
        n->val = v;
        return n;
    }

    n->ht = 1 + std::max(height(n->l), height(n->r));
    int bal = balance(n);

    if (bal > 1 && k < n->l->key)
        return rightRotate(n);

    if (bal < -1 && k > n->r->key)
        return leftRotate(n);

    if (bal > 1 && k > n->l->key) {
        n->l = leftRotate(n->l);
        return rightRotate(n);
    }

    if (bal < -1 && k < n->r->key) {
        n->r = rightRotate(n->r);
        return leftRotate(n);
    }

    return n;
}

void AVLTree::add(const std::string& k, const std::string& v) {
    root = add(root, k, v);
    cnt++;
}

AVLTree::Node* AVLTree::minNode(Node* n) {
    Node* cur = n;
    while (cur && cur->l)
        cur = cur->l;
    return cur;
}

AVLTree::Node* AVLTree::del(Node* n, const std::string& k) {
    if (!n) return n;

    if (k < n->key)
        n->l = del(n->l, k);
    else if (k > n->key)
        n->r = del(n->r, k);
    else {
        if (!n->l || !n->r) {
            Node* tmp = n->l ? n->l : n->r;
            if (!tmp) {
                tmp = n;
                n = nullptr;
            }
            else {
                *n = *tmp;
            }
            delete tmp;
        }
        else {
            Node* tmp = minNode(n->r);
            n->key = tmp->key;
            n->val = tmp->val;
            n->r = del(n->r, tmp->key);
        }
    }

    if (!n) return n;

    n->ht = 1 + std::max(height(n->l), height(n->r));
    int bal = balance(n);

    if (bal > 1 && balance(n->l) >= 0)
        return rightRotate(n);

    if (bal > 1 && balance(n->l) < 0) {
        n->l = leftRotate(n->l);
        return rightRotate(n);
    }

    if (bal < -1 && balance(n->r) <= 0)
        return leftRotate(n);

    if (bal < -1 && balance(n->r) > 0) {
        n->r = rightRotate(n->r);
        return leftRotate(n);
    }

    return n;
}

void AVLTree::del(const std::string& k) {
    root = del(root, k);
    cnt--;
}

bool AVLTree::get(Node* n, const std::string& k, std::string& v) {
    if (!n) return false;

    if (k < n->key)
        return get(n->l, k, v);
    else if (k > n->key)
        return get(n->r, k, v);
    else {
        v = n->val;
        return true;
    }
}

bool AVLTree::get(const std::string& k, std::string& v) {
    return get(root, k, v);
}

int AVLTree::count() const {
    return cnt;
}