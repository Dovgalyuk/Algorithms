#include "avl.h"

#include <algorithm>
#include <stdexcept>

using namespace std;

struct AVLNode
{
    string value;
    AVLNode *left;
    AVLNode *right;
    int height;
};

struct AVLTree
{
    AVLNode *root;
    size_t size;
};

static int node_height(const AVLNode *node)
{
    return node == nullptr ? 0 : node->height;
}

static void update_height(AVLNode *node)
{
    node->height = 1 + max(node_height(node->left), node_height(node->right));
}

static int balance_factor(const AVLNode *node)
{
    return node_height(node->right) - node_height(node->left);
}

static AVLNode *rotate_left(AVLNode *node)
{
    AVLNode *top = node->right;
    node->right = top->left;
    top->left = node;
    update_height(node);
    update_height(top);
    return top;
}

static AVLNode *rotate_right(AVLNode *node)
{
    AVLNode *top = node->left;
    node->left = top->right;
    top->right = node;
    update_height(node);
    update_height(top);
    return top;
}

static AVLNode *balance(AVLNode *node)
{
    update_height(node);

    if (balance_factor(node) == 2)
    {
        if (balance_factor(node->right) < 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    if (balance_factor(node) == -2)
    {
        if (balance_factor(node->left) > 0)
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    return node;
}

static AVLNode *insert_node(AVLNode *node, const string &value, bool &added)
{
    if (node == nullptr)
    {
        AVLNode *created = new AVLNode{value, nullptr, nullptr, 1};
        added = true;
        return created;
    }

    if (value < node->value)
        node->left = insert_node(node->left, value, added);
    else if (value > node->value)
        node->right = insert_node(node->right, value, added);
    else
        return node;

    return balance(node);
}

static AVLNode *detach_min(AVLNode *node, AVLNode *&minimum)
{
    if (node->left == nullptr)
    {
        minimum = node;
        return node->right;
    }

    node->left = detach_min(node->left, minimum);
    return balance(node);
}

static AVLNode *erase_node(AVLNode *node, const string &value, bool &removed)
{
    if (node == nullptr)
        return nullptr;

    if (value < node->value)
        node->left = erase_node(node->left, value, removed);
    else if (value > node->value)
        node->right = erase_node(node->right, value, removed);
    else
    {
        removed = true;

        if (node->left == nullptr || node->right == nullptr)
        {
            AVLNode *child = node->left == nullptr ? node->right : node->left;
            delete node;
            return child;
        }

        AVLNode *minimum = nullptr;
        AVLNode *right = detach_min(node->right, minimum);
        minimum->left = node->left;
        minimum->right = right;
        delete node;
        return balance(minimum);
    }

    return balance(node);
}

static void delete_nodes(AVLNode *node)
{
    if (node == nullptr)
        return;

    delete_nodes(node->left);
    delete_nodes(node->right);
    delete node;
}

static int check_node(const AVLNode *node, const string *lower,
                      const string *upper, size_t &count)
{
    if (node == nullptr)
        return 0;

    if ((lower != nullptr && node->value <= *lower) ||
        (upper != nullptr && node->value >= *upper))
        return -1;

    int left = check_node(node->left, lower, &node->value, count);
    if (left == -1)
        return -1;

    int right = check_node(node->right, &node->value, upper, count);
    if (right == -1)
        return -1;

    int height = 1 + max(left, right);
    if (right - left < -1 || right - left > 1 || node->height != height)
        return -1;

    ++count;
    return height;
}

AVLTree *avl_create()
{
    return new AVLTree{nullptr, 0};
}

void avl_delete(AVLTree *tree)
{
    if (tree == nullptr)
        return;

    delete_nodes(tree->root);
    delete tree;
}

bool avl_insert(AVLTree *tree, const string &value)
{
    if (tree == nullptr)
        return false;

    bool added = false;
    tree->root = insert_node(tree->root, value, added);
    if (added)
        ++tree->size;
    return added;
}

bool avl_find(const AVLTree *tree, const string &value)
{
    const AVLNode *node = tree == nullptr ? nullptr : tree->root;

    while (node != nullptr)
    {
        if (value < node->value)
            node = node->left;
        else if (value > node->value)
            node = node->right;
        else
            return true;
    }

    return false;
}

bool avl_erase(AVLTree *tree, const string &value)
{
    if (tree == nullptr)
        return false;

    bool removed = false;
    tree->root = erase_node(tree->root, value, removed);
    if (removed)
        --tree->size;
    return removed;
}

size_t avl_size(const AVLTree *tree)
{
    return tree == nullptr ? 0 : tree->size;
}

int avl_height(const AVLTree *tree)
{
    return tree == nullptr ? 0 : node_height(tree->root);
}

bool avl_check(const AVLTree *tree)
{
    if (tree == nullptr)
        return true;

    size_t count = 0;
    return check_node(tree->root, nullptr, nullptr, count) != -1 && count == tree->size;
}

AVLIterator avl_begin(const AVLTree *tree)
{
    AVLIterator iterator;
    const AVLNode *node = tree == nullptr ? nullptr : tree->root;

    while (node != nullptr)
    {
        iterator.path.push_back(node);
        node = node->left;
    }

    return iterator;
}

bool avl_iterator_valid(const AVLIterator &iterator)
{
    return !iterator.path.empty();
}

const string &avl_iterator_get(const AVLIterator &iterator)
{
    if (!avl_iterator_valid(iterator))
        throw out_of_range("AVL iterator is at end");

    return iterator.path.back()->value;
}

void avl_iterator_next(AVLIterator &iterator)
{
    if (!avl_iterator_valid(iterator))
        return;

    const AVLNode *node = iterator.path.back()->right;
    iterator.path.pop_back();

    while (node != nullptr)
    {
        iterator.path.push_back(node);
        node = node->left;
    }
}
