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

    node* insert(string x, string y, node* t)
    {
        if (t == NULL)
        {
            t = new node;
            t->key = x;
            t->field = y;
            t->height = 0;
            t->left = t->right = NULL;
        }
        else if (x < t->key)
        {
            t->left = insert(x, y, t->left);
            if (height(t->left) - height(t->right) == 2)
            {
                if (x < t->left->key)
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if (x > t->key)
        {
            t->right = insert(x, y, t->right);
            if (height(t->right) - height(t->left) == 2)
            {
                if (x > t->right->key)
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }

        t->height = max(height(t->left), height(t->right)) + 1;
        return t;
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

    node* doubleLeftRotate(node*& t)
    {
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    node* doubleRightRotate(node*& t)
    {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
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


    node* remove(string x, node* t)
    {
        node* temp;

        // Element not found
        if (t == NULL)
            return NULL;

        // Searching for element
        else if (x < t->key)
            t->left = remove(x, t->left);
        else if (x > t->key)
            t->right = remove(x, t->right);

        // Element found
        // With 2 children
        else if (t->left && t->right)
        {
            temp = findMin(t->right);
            t->key = temp->key;
            t->field = temp->field;
            t->right = remove(t->key, t->right);
        }
        // With one or zero child
        else
        {
            temp = t;
            if (t->left == NULL)
                t = t->right;
            else if (t->right == NULL)
                t = t->left;
            delete temp;
        }
        if (t == NULL)
            return t;

        t->height = max(height(t->left), height(t->right)) + 1;

        // If node is unbalanced
        // If left node is deleted, right case
        if (height(t->left) - height(t->right) == 2)
        {
            // right right case
            if (height(t->left->left) - height(t->left->right) == 1)
                return singleLeftRotate(t);
            // right left case
            else
                return doubleLeftRotate(t);
        }
        // If right node is deleted, left case
        else if (height(t->right) - height(t->left) == 2)
        {
            // left left case
            if (height(t->right->right) - height(t->right->left) == 1)
                return singleRightRotate(t);
            // left right case
            else
                return doubleRightRotate(t);
        }
        return t;
    }
    string Search(string v) {
        if (root == NULL) {
            return root->field;
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
            return NULL;
        }
    }
    int height(node* t)
    {
        return (t == NULL ? -1 : t->height);
    }

    int getBalance(node* t)
    {
        if (t == NULL)
            return 0;
        else
            return height(t->left) - height(t->right);
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
        root = remove(x, root);
    }

    string search_field(string x)
    {
        return Search(x);
    }
};
#endif
