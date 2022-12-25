#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <string>

using namespace std;

class Tree
{
    struct node
    {
        string key;
        string field;
        node* left;
        node* right;
        int height;
    };

    node* root;

    node* insert(const string& x, const string& y, node* t)
    {
        if (!t)
        {
            t = new node;
            t->field = y;
            t->key = x;
            t->height = 0;
            t->left = t->right = NULL;
            return t;
        }
        if (x < t->key)
            t->left = insert(x, y, t->left);
        else
            t->right = insert(x, y, t->right);
        return balance(t);
    }
    
    node* singleRightRotate(node*& t)
    {
        node* u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(u->left), t->height) + 1;
        return u;
    }

    node* singleLeftRotate(node*& t)
    {
        node* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(t->right), t->height) + 1;
        return u;
    }

    node* findMin(node* t)
    {
        if (t == NULL)
            return NULL;
        else if (t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node* findMax(node* t)
    {
        if (t == NULL)
            return NULL;
        else if (t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    int bfactor(node* p)
    {
        return height(p->right) - height(p->left);
    }

    node* balance(node* p) 
    {
        p->height = max(height(p->left), height(p->right)) + 1;
        if (bfactor(p) == 2)
        {
            if (bfactor(p->right) < 0)
                p->right = singleRightRotate(p->right);
            return singleLeftRotate(p);
        }
        if (bfactor(p) == -2)
        {
            if (bfactor(p->left) > 0)
                p->left = singleLeftRotate(p->left);
            return singleRightRotate(p);
        }
        return p; 
    }

    node* findmin(node* p) 
    {
        return p->left ? findmin(p->left) : p;
    }

    node* removemin(node* p) 
    {
        if (p->left == 0)
            return p->right;
        p->left = removemin(p->left);
        return balance(p);
    }

    node* remove(node* p, const string& k) 
    {
        if (!p) return 0;
        if (k < p->key)
            p->left = remove(p->left, k);
        else if (k > p->key)
            p->right = remove(p->right, k);
        else 
        {
            node* q = p->left;
            node* r = p->right;
            delete p;
            if (!r) return q;
            node* min = findmin(r);
            min->right = removemin(r);
            min->left = q;
            return balance(min);
        }
        return balance(p);
    }

    int height(node* t)
    {
        return (t == NULL ? -1 : t->height);
    }

    string Search(string v) {
        if (root == NULL) {
            return "";
        }
        else {
            node* temp = root;
            while (temp != NULL) {
                if (v == temp->key) {
                    return temp->field;
                }
                else if (v < temp->key) {
                    temp = temp->left;
                }
                else {
                    temp = temp->right;
                }
            }
            return "";
        }
    }

public:
    Tree()
    {
        root = NULL;
    }
    void insert(string x, string y)
    {
        root = insert(x, y, root);
    }

    void remove(string x)
    {
        root = remove(root, x);
    }
    string search_field(string x)
    {
        return Search(x);
    }
};
#endif
