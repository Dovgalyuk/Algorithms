#include "Set.h"

// Insert value to Red-Black Tree
void Set::insert(const std::string &key)
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
    balance_after_insert(node);
}

// Find Node with specified value
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

// Remove value from Red-Black Tree
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
        throw std::out_of_range("Key node was not found");
    }

    y = z;
    Color y_color = y->color;
    if (z->left == nullptr) {
        x = z->right;
        transplant(root, z, z->right);
    }
    else if (z->right == nullptr) {
        x = z->left;
        transplant(root, z, z->left);
    }
    else {
        y = min_node(z->right);
        y_color = y->color;
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
    if (y_color == BLACK) {
        balance_after_delete(x);
    }
}

// Left Rotate
void Set::rotate_left(Node* node)
{
    Node* son = node->right;
    node->right = son->left;
    if (node->right != nullptr)
        node->right->parent = node;
    son->parent = node->parent;
    if (node->parent == nullptr)
        root = son;
    else if (node == node->parent->left)
        node->parent->left = son;
    else
        node->parent->right = son;
    son->left = node;
    node->parent = son;
}

// Right Rotate
void Set::rotate_right(Node* node)
{
    Node* son = node->left;
    node->left = son->right;
    if (node->left != nullptr)
        node->left->parent = node;
    son->parent = node->parent;
    if (node->parent == nullptr)
        root = son;
    else if (node == node->parent->left)
        node->parent->left = son;
    else
        node->parent->right = son;
    son->right = node;
    node->parent = son;
}

// Balance after insertion
void Set::balance_after_insert(Node* node)
{
    Node* parent = nullptr;
    Node* granddad = nullptr;
    while (node != root && node->color == RED && node->parent->color == RED) {
        parent = node->parent;
        granddad = parent->parent;
        if (parent == granddad->left) {
            Node* uncle = granddad->right;
            if (uncle != nullptr
                && uncle->color == RED) {
                granddad->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = granddad;
            }
            else {
                if (node == parent->right) {
                    rotate_left(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotate_right(granddad);
                std::swap(parent->color, granddad->color);
                node = parent;
            }
        }
        else {
            Node* uncle = granddad->left;
            if (uncle != nullptr
                && uncle->color == RED) {
                granddad->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = granddad;
            }
            else {
                if (node == parent->left) {
                    rotate_right(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotate_left(granddad);
                std::swap(parent->color, granddad->color);
                node = parent;
            }
        }
    }
    root->color = BLACK;
}

// Balance after removing
void Set::balance_after_delete(Node* node)
{
    while (node != root && node != nullptr && node->color == BLACK) {
        if (node == node->parent->left) {
            Node* brother = node->parent->right;
            if (brother->color == RED) {
                brother->color = BLACK;
                node->parent->color = RED;
                rotate_left(node->parent);
                brother = node->parent->right;
            }
            if ((brother->left == nullptr || brother->left->color == BLACK) && (brother->right == nullptr || brother->right->color == BLACK)) {
                brother->color = RED;
                node = node->parent;
            }
            else {
                if (brother->right == nullptr || brother->right->color == BLACK) {
                    if (brother->left != nullptr)
                        brother->left->color = BLACK;
                    brother->color = RED;
                    rotate_right(brother);
                    brother = node->parent->right;
                }
                brother->color = node->parent->color;
                node->parent->color = BLACK;
                if (brother->right != nullptr)
                    brother->right->color = BLACK;
                rotate_left(node->parent);
                node = root;
            }
        }
        else {
            Node* brother = node->parent->left;
            if (brother != nullptr && brother->color == RED) {
                brother->color = BLACK;
                node->parent->color = RED;
                rotate_right(node->parent);
                brother = node->parent->left;
            }
            if (brother != nullptr && (brother->left == nullptr || brother->left->color == BLACK) && (brother->right == nullptr || brother->right->color == BLACK)) {
                brother->color = RED;
                node = node->parent;
            }
            else if (brother != nullptr) {
                if (brother->left == nullptr || brother->left->color == BLACK) {
                    if (brother->right != nullptr)
                        brother->right->color = BLACK;
                    brother->color = RED;
                    rotate_left(brother);
                    brother = node->parent->left;
                }
                brother->color = node->parent->color;
                node->parent->color = BLACK;
                if (brother->left != nullptr)
                    brother->left->color = BLACK;
                rotate_right(node->parent);
                node = root;
            }
        }
    }
    if(node != nullptr)
        node->color = BLACK;
}

// Find Node with min value
Node* Set::min_node(Node* node)
{
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

void Set::transplant(Node*& root, Node* u, Node* v)
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

// Remove all nodes from Red-Black Tree
void Set::delete_tree(Node* node)
{
    if (node != nullptr) {
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
    }
}
