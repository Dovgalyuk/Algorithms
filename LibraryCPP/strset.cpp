#include "strset.h"
#include <string>

enum Color { RED, BLACK };

using namespace std;

struct Node {
    string key;
    Color color;
    Node* parent;
    Node* left;
    Node* right;
};

struct StringSet {
    Node* root;
};

static void destroy_tree(Node* node)
{
    if (!node) return;
    destroy_tree(node->left);
    destroy_tree(node->right);
    delete node;
}

static Node* tree_minimum(Node* x)
{
    if (!x) return nullptr;
    while (x->left)
        x = x->left;
    return x;
}

static void rotate_left(StringSet* set, Node* x)
{
    Node* y = x->right;
    if (!y) return;

    y->parent = x->parent;
    if (!x->parent) {
        set->root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    x->right = y->left;
    if (y->left)
        y->left->parent = x;

    y->left = x;
    x->parent = y;
}

static void rotate_right(StringSet* set, Node* x)
{
    Node* y = x->left;
    if (!y) return;

    y->parent = x->parent;
    if (!x->parent) {
        set->root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    x->left = y->right;
    if (y->right)
        y->right->parent = x;

    y->right = x;
    x->parent = y;
}

static void insert_fixup(StringSet* set, Node* x)
{
    while (x != set->root && x->parent->color == RED) {
        Node* parent = x->parent;
        Node* grand = parent->parent;
        if (parent == grand->left) {
            Node* uncle = grand->right;
            if (uncle && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grand->color = RED;
                x = grand;
            }
            else {
                if (x == parent->right) {
                    x = parent;
                    rotate_left(set, x);
                    parent = x->parent;
                    grand = parent->parent;
                }
                parent->color = BLACK;
                grand->color = RED;
                rotate_right(set, grand);
            }
        }
        else {
            Node* uncle = grand->left;
            if (uncle && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grand->color = RED;
                x = grand;
            }
            else {
                if (x == parent->left) {
                    x = parent;
                    rotate_right(set, x);
                    parent = x->parent;
                    grand = parent->parent;
                }
                parent->color = BLACK;
                grand->color = RED;
                rotate_left(set, grand);
            }
        }
    }
    set->root->color = BLACK;
}

static void rb_transplant(StringSet* set, Node* u, Node* v)
{
    if (!u->parent) {
        set->root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    if (v)
        v->parent = u->parent;
}

static void erase_fixup(StringSet* set, Node* x, Node* parent)
{
    while ((x != set->root) && (x == nullptr || x->color == BLACK)) {
        if (parent && x == parent->left) {
            Node* w = parent->right;
            if (w && w->color == RED) {
                w->color = BLACK;
                parent->color = RED;
                rotate_left(set, parent);
                w = parent->right;
            }
            bool w_left_black = !w || !w->left || w->left->color == BLACK;
            bool w_right_black = !w || !w->right || w->right->color == BLACK;

            if (w_left_black && w_right_black) {
                if (w)
                    w->color = RED;
                x = parent;
                parent = x ? x->parent : nullptr;
            }
            else {
                if (w && (!w->right || w->right->color == BLACK)) {
                    if (w->left)
                        w->left->color = BLACK;
                    if (w) {
                        w->color = RED;
                        rotate_right(set, w);
                    }
                    w = parent->right;
                }
                if (w)
                    w->color = parent->color;
                parent->color = BLACK;
                if (w && w->right)
                    w->right->color = BLACK;
                rotate_left(set, parent);
                x = set->root;
                parent = nullptr;
            }
        }
        else {
            Node* w = parent ? parent->left : nullptr;
            if (w && w->color == RED) {
                w->color = BLACK;
                parent->color = RED;
                rotate_right(set, parent);
                w = parent->left;
            }
            bool w_left_black = !w || !w->left || w->left->color == BLACK;
            bool w_right_black = !w || !w->right || w->right->color == BLACK;

            if (w_left_black && w_right_black) {
                if (w)
                    w->color = RED;
                x = parent;
                parent = x ? x->parent : nullptr;
            }
            else {
                if (w && (!w->left || w->left->color == BLACK)) {
                    if (w->right)
                        w->right->color = BLACK;
                    if (w) {
                        w->color = RED;
                        rotate_left(set, w);
                    }
                    w = parent->left;
                }
                if (w)
                    w->color = parent->color;
                parent->color = BLACK;
                if (w && w->left)
                    w->left->color = BLACK;
                rotate_right(set, parent);
                x = set->root;
                parent = nullptr;
            }
        }
    }
    if (x)
        x->color = BLACK;
}

StringSet* string_set_create()
{
    StringSet* set = new StringSet;
    set->root = nullptr;
    return set;
}

void string_set_delete(StringSet* set)
{
    if (!set) return;
    destroy_tree(set->root);
    delete set;
}

bool string_set_contains(const StringSet* set, const string& value)
{
    Node* cur = set->root;
    while (cur != nullptr) {
        if (value < cur->key) {
            cur = cur->left;
        }
        else if (cur->key < value) {
            cur = cur->right;
        }
        else {
            return true;
        }
    }
    return false;
}

bool string_set_insert(StringSet* set, const string& value)
{
    Node* parent = nullptr;
    Node* cur = set->root;

    while (cur != nullptr) {
        parent = cur;
        if (value < cur->key) {
            cur = cur->left;
        }
        else if (cur->key < value) {
            cur = cur->right;
        }
        else {
            return false;
        }
    }

    Node* z = new Node;
    z->key = value;
    z->color = RED;
    z->parent = parent;
    z->left = nullptr;
    z->right = nullptr;

    if (!parent) {
        set->root = z;
    }
    else if (value < parent->key) {
        parent->left = z;
    }
    else {
        parent->right = z;
    }

    insert_fixup(set, z);
    return true;
}

bool string_set_erase(StringSet* set, const string& value)
{
    Node* z = set->root;
    while (z != nullptr) {
        if (value < z->key) {
            z = z->left;
        }
        else if (z->key < value) {
            z = z->right;
        }
        else {
            break;
        }
    }
    if (!z)
        return false;

    Node* y = z;
    Color y_original_color = y->color;
    Node* x = nullptr;
    Node* parent_x = nullptr;

    if (z->left == nullptr) {
        x = z->right;
        parent_x = z->parent;
        rb_transplant(set, z, z->right);
    }
    else if (z->right == nullptr) {
        x = z->left;
        parent_x = z->parent;
        rb_transplant(set, z, z->left);
    }
    else {
        y = tree_minimum(z->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == z) {
            parent_x = y;
            if (x)
                x->parent = y;
        }
        else {
            parent_x = y->parent;
            rb_transplant(set, y, y->right);
            y->right = z->right;
            if (y->right)
                y->right->parent = y;
        }

        rb_transplant(set, z, y);
        y->left = z->left;
        if (y->left)
            y->left->parent = y;
        y->color = z->color;
    }

    delete z;

    if (y_original_color == BLACK) {
        erase_fixup(set, x, x ? x->parent : parent_x);
    }

    return true;
}
