#include "RBTree.h"
#include <iostream>

RBTree::Node::Node(const string& k, const string& v)
    : key(k), value(v), red(true), left(0), right(0), parent(0) {}

RBTree::RBTree() : root(0), treeSize(0) {}

RBTree::~RBTree() {
    clear(root);
}

void RBTree::clear(Node* n) {
    if (n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

void RBTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == 0)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void RBTree::rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;

    if (y->right)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == 0)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

void RBTree::insert(const string& k, const string& v) {
    Node* n = new Node(k, v);

    if (root == 0) {
        root = n;
        root->red = false;
        treeSize++;
        return;
    }

    Node* cur = root;
    Node* par = 0;

    while (cur) {
        par = cur;

        if (k < cur->key)
            cur = cur->left;
        else if (k > cur->key)
            cur = cur->right;
        else {
            cur->value = v;
            delete n;
            return;
        }
    }

    n->parent = par;

    if (k < par->key)
        par->left = n;
    else
        par->right = n;

    treeSize++;
    fixAdd(n);
}

void RBTree::fixAdd(Node* k) {
    while (k->parent && k->parent->red) {
        if (k->parent == k->parent->parent->left) {
            Node* u = k->parent->parent->right;

            if (u && u->red) {
                k->parent->red = false;
                u->red = false;
                k->parent->parent->red = true;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }

                k->parent->red = false;
                k->parent->parent->red = true;
                rightRotate(k->parent->parent);
            }
        }
        else {
            Node* u = k->parent->parent->left;

            if (u && u->red) {
                k->parent->red = false;
                u->red = false;
                k->parent->parent->red = true;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }

                k->parent->red = false;
                k->parent->parent->red = true;
                leftRotate(k->parent->parent);
            }
        }

        if (k == root) break;
    }

    root->red = false;
}

RBTree::Node* RBTree::find(const string& k) {
    Node* cur = root;

    while (cur) {
        if (k < cur->key)
            cur = cur->left;
        else if (k > cur->key)
            cur = cur->right;
        else
            return cur;
    }

    return 0;
}

bool RBTree::find(const string& k, string& v) {
    Node* n = find(k);

    if (n) {
        v = n->value;
        return true;
    }

    return false;
}

void RBTree::replace(Node* u, Node* v) {
    if (u->parent == 0)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v)
        v->parent = u->parent;
}

RBTree::Node* RBTree::minNode(Node* n) {
    while (n && n->left)
        n = n->left;

    return n;
}

void RBTree::remove(const string& k) {
    Node* z = find(k);
    if (z == 0) return;

    Node* y = z;
    Node* x = 0;
    bool yRed = y->red;

    if (z->left == 0) {
        x = z->right;
        replace(z, z->right);
    }
    else if (z->right == 0) {
        x = z->left;
        replace(z, z->left);
    }
    else {
        y = minNode(z->right);
        yRed = y->red;
        x = y->right;

        if (y->parent == z) {
            if (x)
                x->parent = y;
        }
        else {
            replace(y, y->right);
            y->right = z->right;

            if (y->right)
                y->right->parent = y;
        }

        replace(z, y);
        y->left = z->left;

        if (y->left)
            y->left->parent = y;

        y->red = z->red;
    }

    delete z;
    treeSize--;

    if (yRed == false && x)
        fixDel(x);
}

void RBTree::fixDel(Node* x) {
    while (x != root && x && x->red == false) {
        if (x == x->parent->left) {
            Node* s = x->parent->right;

            if (s && s->red) {
                s->red = false;
                x->parent->red = true;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (s && (s->left == 0 || s->left->red == false) && (s->right == 0 || s->right->red == false)) {
                s->red = true;
                x = x->parent;
            }
            else {
                if (s && (s->right == 0 || s->right->red == false)) {
                    if (s->left)
                        s->left->red = false;

                    s->red = true;
                    rightRotate(s);
                    s = x->parent->right;
                }

                if (s) {
                    s->red = x->parent->red;

                    if (s->right)
                        s->right->red = false;
                }

                x->parent->red = false;
                leftRotate(x->parent);
                x = root;
            }
        }
        else {
            Node* s = x->parent->left;

            if (s && s->red) {
                s->red = false;
                x->parent->red = true;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s && (s->right == 0 || s->right->red == false) && (s->left == 0 || s->left->red == false)) {
                s->red = true;
                x = x->parent;
            }
            else {
                if (s && (s->left == 0 || s->left->red == false)) {
                    if (s->right)
                        s->right->red = false;

                    s->red = true;
                    leftRotate(s);
                    s = x->parent->left;
                }

                if (s) {
                    s->red = x->parent->red;

                    if (s->left)
                        s->left->red = false;
                }

                x->parent->red = false;
                rightRotate(x->parent);
                x = root;
            }
        }
    }

    if (x)
        x->red = false;
}

int RBTree::size() const {
    return treeSize;
}