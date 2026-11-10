#ifndef AVL_H
#define AVL_H

#include <cstddef>
#include <string>
#include <vector>

struct AVLNode;
struct AVLTree;

struct AVLIterator
{
    std::vector<const AVLNode *> path;
};

AVLTree *avl_create();
void avl_delete(AVLTree *tree);
bool avl_insert(AVLTree *tree, const std::string &value);
bool avl_find(const AVLTree *tree, const std::string &value);
bool avl_erase(AVLTree *tree, const std::string &value);
std::size_t avl_size(const AVLTree *tree);
int avl_height(const AVLTree *tree);
bool avl_check(const AVLTree *tree);

AVLIterator avl_begin(const AVLTree *tree);
bool avl_iterator_valid(const AVLIterator &iterator);
const std::string &avl_iterator_get(const AVLIterator &iterator);
void avl_iterator_next(AVLIterator &iterator);

#endif
