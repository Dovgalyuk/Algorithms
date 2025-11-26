#include "rbtree.h"
#include <iostream>

RBTree::RBTree() : root(nullptr), cnt(0) {}

RBTree::~RBTree() {
    clear(root);
}

void RBTree::clear(Node* n) {
    if (n) {
        clear(n->l);
        clear(n->r);
        delete n;
    }
}

void RBTree::leftRotate(Node* x) {
    Node* y = x->r;
    x->r = y->l;

    if (y->l)
        y->l->p = x;

    y->p = x->p;

    if (!x->p)
        root = y;
    else if (x == x->p->l)
        x->p->l = y;
    else
        x->p->r = y;

    y->l = x;
    x->p = y;
}

void RBTree::rightRotate(Node* x) {
    Node* y = x->l;
    x->l = y->r;

    if (y->r)
        y->r->p = x;

    y->p = x->p;

    if (!x->p)
        root = y;
    else if (x == x->p->r)
        x->p->r = y;
    else
        x->p->l = y;

    y->r = x;
    x->p = y;
}

void RBTree::add(const std::string& k, const std::string& v) {
    Node* n = new Node(k, v);

    if (!root) {
        root = n;
        root->red = false;
        cnt++;
        return;
    }

    Node* cur = root;
    Node* par = nullptr;

    while (cur) {
        par = cur;

        if (k < cur->key)
            cur = cur->l;
        else if (k > cur->key)
            cur = cur->r;
        else {
            cur->val = v;
            delete n;
            return;
        }
    }

    n->p = par;

    if (k < par->key)
        par->l = n;
    else
        par->r = n;

    cnt++;
    fixAdd(n);
}

void RBTree::fixAdd(Node* k) {
    while (k->p && k->p->red) {
        if (k->p == k->p->p->l) {
            Node* u = k->p->p->r;

            if (u && u->red) {
                k->p->red = false;
                u->red = false;
                k->p->p->red = true;
                k = k->p->p;
            }
            else {
                if (k == k->p->r) {
                    k = k->p;
                    leftRotate(k);
                }

                k->p->red = false;
                k->p->p->red = true;
                rightRotate(k->p->p);
            }
        }
        else {
            Node* u = k->p->p->l;

            if (u && u->red) {
                k->p->red = false;
                u->red = false;
                k->p->p->red = true;
                k = k->p->p;
            }
            else {
                if (k == k->p->l) {
                    k = k->p;
                    rightRotate(k);
                }

                k->p->red = false;
                k->p->p->red = true;
                leftRotate(k->p->p);
            }
        }

        if (k == root) break;
    }

    root->red = false;
}

RBTree::Node* RBTree::find(const std::string& k) {
    Node* cur = root;

    while (cur) {
        if (k < cur->key)
            cur = cur->l;
        else if (k > cur->key)
            cur = cur->r;
        else
            return cur;
    }

    return nullptr;
}

bool RBTree::get(const std::string& k, std::string& v) {
    Node* n = find(k);

    if (n) {
        v = n->val;
        return true;
    }

    return false;
}

void RBTree::replace(Node* u, Node* v) {
    if (!u->p)
        root = v;
    else if (u == u->p->l)
        u->p->l = v;
    else
        u->p->r = v;

    if (v)
        v->p = u->p;
}

RBTree::Node* RBTree::minNode(Node* n) {
    while (n && n->l)
        n = n->l;

    return n;
}

void RBTree::del(const std::string& k) {
    Node* z = find(k);
    if (!z) return;

    Node* y = z;
    Node* x = nullptr;
    bool yRed = y->red;

    if (!z->l) {
        x = z->r;
        replace(z, z->r);
    }
    else if (!z->r) {
        x = z->l;
        replace(z, z->l);
    }
    else {
        y = minNode(z->r);
        yRed = y->red;
        x = y->r;

        if (y->p == z) {
            if (x)
                x->p = y;
        }
        else {
            replace(y, y->r);
            y->r = z->r;

            if (y->r)
                y->r->p = y;
        }

        replace(z, y);
        y->l = z->l;

        if (y->l)
            y->l->p = y;

        y->red = z->red;
    }

    delete z;
    cnt--;

    if (!yRed && x)
        fixDel(x);
}

void RBTree::fixDel(Node* x) {
    while (x != root && x && !x->red) {
        if (x == x->p->l) {
            Node* s = x->p->r;

            if (s && s->red) {
                s->red = false;
                x->p->red = true;
                leftRotate(x->p);
                s = x->p->r;
            }

            if (s && (!s->l || !s->l->red) && (!s->r || !s->r->red)) {
                s->red = true;
                x = x->p;
            }
            else {
                if (s && (!s->r || !s->r->red)) {
                    if (s->l)
                        s->l->red = false;

                    s->red = true;
                    rightRotate(s);
                    s = x->p->r;
                }

                if (s) {
                    s->red = x->p->red;

                    if (s->r)
                        s->r->red = false;
                }

                x->p->red = false;
                leftRotate(x->p);
                x = root;
            }
        }
        else {
            Node* s = x->p->l;

            if (s && s->red) {
                s->red = false;
                x->p->red = true;
                rightRotate(x->p);
                s = x->p->l;
            }

            if (s && (!s->r || !s->r->red) && (!s->l || !s->l->red)) {
                s->red = true;
                x = x->p;
            }
            else {
                if (s && (!s->l || !s->l->red)) {
                    if (s->r)
                        s->r->red = false;

                    s->red = true;
                    leftRotate(s);
                    s = x->p->l;
                }

                if (s) {
                    s->red = x->p->red;

                    if (s->l)
                        s->l->red = false;
                }

                x->p->red = false;
                rightRotate(x->p);
                x = root;
            }
        }
    }

    if (x)
        x->red = false;
}

int RBTree::count() const {
    return cnt;
}