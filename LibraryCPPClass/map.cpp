#include "map.h"

Map::Map() : root(nullptr), sz(0) {}

Map::Map(const Map& a) : root(nullptr), sz(0) {
    if (a.root) {
        root = cpy_tree(a.root, nullptr);
        sz = a.sz;
    }
}

Map& Map::operator=(const Map& a) {
    if (this != &a) {
        clear();
        if (a.root) {
            root = cpy_tree(a.root, nullptr);
            sz = a.sz;
        }
    }
    return *this;
}

Map::~Map() {
    clear();
}

Map::Node* Map::cpy_tree(Node* node, Node* parent) {
    if (!node) return nullptr;
    
    Node* new_node = new Node(node->key, node->value);
    new_node->parent = parent;
    new_node->left = cpy_tree(node->left, new_node);
    new_node->right = cpy_tree(node->right, new_node);
    return new_node;
}

void Map::rotate_left(Node* x) {
    Node* y = x->right;
    if (!y) return;

    x->right = y->left;
    if (y->left) y->left->parent = x;

    y->parent = x->parent;
    if (!x->parent) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void Map::rotate_right(Node* x) {
    Node* y = x->left;
    if (!y) return;

    x->left = y->right;
    if (y->right) y->right->parent = x;

    y->parent = x->parent;
    if (!x->parent) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

void Map::splay(Node* x) {
    if (!x) return;

    while (x->parent) {
        Node* p = x->parent;
        Node* g = p->parent;
        if (!g) {
            if (p->left == x) rotate_right(p);
            else rotate_left(p);
        } else {
            if (p->left == x && g->left == p) {
                rotate_right(g);
                rotate_right(p);
            } else if (p->right == x && g->right == p) {
                rotate_left(g);
                rotate_left(p);
            } else if (p->left == x && g->right == p) {
                rotate_right(p);
                rotate_left(g);
            } else {
                rotate_left(p);
                rotate_right(g);
            }
        }
    }
}

Map::Node* Map::find_node(const std::string& key) {
    Node* cur = root;
    Node* prev = nullptr;
    
    while (cur) {
        prev = cur;
        if (key < cur->key) {
            cur = cur->left;
        } else if (key > cur->key) {
            cur = cur->right;
        } else {
            splay(cur);
            return cur;
        }
    }
    
    if (prev) {
        splay(prev);
    }
    return nullptr;
}

void Map::insert(const std::string& key, const std::string& value) {
    if (!root) {
        root = new Node(key, value);
        sz = 1;
        return;
    }
    
    Node* cur = root;
    Node* parent = nullptr;
    
    while (cur) {
        parent = cur;
        if (key < cur->key) {
            cur = cur->left;
        } else if (key > cur->key) {
            cur = cur->right;
        } else {
            cur->value = value;
            splay(cur);
            return;
        }
    }
    
    Node* new_node = new Node(key, value);
    new_node->parent = parent;
    
    if (key < parent->key) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    
    splay(new_node);
    sz++;
}

bool Map::find(const std::string& key, std::string& value) {
    const Node* node = find_node(key);
    
    if (node && node->key == key) {
        value = node->value;
        return true;
    }
    return false;
}

bool Map::remove(const std::string& key) {
    Node* node = find_node(key);
    if (!node || node->key != key) {
        return false;
    }

    Node* left_tree = root->left;
    Node* right_tree = root->right;

    if (left_tree) left_tree->parent = nullptr;
    if (right_tree) right_tree->parent = nullptr;

    delete root;
    --sz;

    if (!left_tree && !right_tree) {
        root = nullptr;
    } else if (!left_tree) {
        root = right_tree;
    } else if (!right_tree) {
        root = left_tree;
    } else {
        root = left_tree;
        Node* max_left = left_tree;
        while (max_left->right) max_left = max_left->right;

        splay(max_left); 
        root->right = right_tree;
        right_tree->parent = root;
    }

    return true;
}

void Map::clear() {
    clear(root);
    root = nullptr;
    sz = 0;
}

void Map::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

size_t Map::size() const {
    return sz;
}

bool Map::empty() const {
    return sz == 0;
}
