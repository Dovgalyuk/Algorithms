#include <stdlib.h>
#include "splay_tree.h"

struct Node
{
    Node* left, *right;
    Node* parent;
    Key key;
};

Node* splay_create(const Key data) 
{
    Node* tree = new Node;
    tree->left = NULL;
    tree->right = NULL;
    tree->parent = NULL;
    tree->key = data;
    return tree;
}

void left_rotate(Node* root, Node* node)
{
    Node* y = node->right;
    if (y) 
    {
        node->right = y->left;
        if (y->left)
        {
            y->left->parent = node;
        }
        y->parent = node->parent;
    }

    if (!node->parent) root = y;
    else if (node == node->parent->left) node->parent->left = y;
    else node->parent->right = y;
    if (y) y->left = node;
    node->parent = y;
}

void right_rotate(Node* root, Node* node)
{
    Node* y = node->left;
    if (y) 
    {
        node->left = y->right;
        if (y->right) y->right->parent = node;
        y->parent = node->parent;
    }

    if (!node->parent)
    {
        root = y;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = y;
    }
    else
    {
        node->parent->right = y;
    }
    if (y)  
    {
        y->right;
    }
}

void splay(Node* root, Node* node)
{
    while (node->parent) 
    {
        if (!node->parent->parent) 
        {
            if (node->parent->left == node) right_rotate(root, node->parent);
            else left_rotate(root, node->parent);
        }
        else if (node->parent->left == node && node->parent->parent->left == node->parent) 
        {
            right_rotate(root, node->parent->parent);
            right_rotate(root, node->parent);
        }
        else if (node->parent->right == node && node->parent->parent->right == node->parent) 
        {
            left_rotate(root, node->parent->parent);
            left_rotate(root, node->parent);
        }
        else if (node->parent->left == node && node->parent->parent->right == node->parent) 
        {
            right_rotate(root, node->parent);
            left_rotate(root, node->parent);
        }
        else 
        {
            left_rotate(root, node->parent);
            right_rotate(root, node->parent);
        }
    }
}

void replace(Node* root, Node* u, Node* v)
{
    if (!u->parent)
    {
        root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    if (v)
    {
        v->parent = u->parent;
    }
}

Node* subtree_minimum(Node* u)
{
    while (u->left)
    {
        u = u->left;
    }
    return u;
}

Node* subtree_maximum(Node* u)
{
    while (u->right)
    {
        u = u->right;
    }
    return u;
}

void insert(Node* root, const Key key)
{
    Node* z = root;
    Node* p = nullptr;

    while(z) 
    {
        p = z;
        if (z->key < key)
        {
            z = z->right;
        }
        else
        {
            z = z->left;
        }
    }
}

Node* find(Node* root,  const Key key)
{
    Node* z = root;
    while(z) 
    {
        if (z->key < key) z = z->right;
        else if (key < z->key) z = z->left;
        else return z;
    }
    return nullptr;
}

void erase(Node* root, const Key key)
{
    Node* z = find(root, key);
    if (!z) return;

    splay(root, z);

    if (!z->left)
    {
        replace(root, z, z->right);
    }
    else if (!z->right)
    {
        replace(root, z, z->left);
    }
    else 
    {
        Node* y = subtree_minimum(z->right);
        if (y->parent != z) {
            replace(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        replace(root, z, y);
        y->left = z->left;
        y->left->parent = y;
    }

    delete z;
}

Node* splay_delete(Node* root) 
{
    if (root)
    {
        splay_delete(root->left);
        splay_delete(root->right);
        delete root;
    }
    return NULL;
}