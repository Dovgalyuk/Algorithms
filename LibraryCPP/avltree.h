#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>
#include <vector>

struct AvlNode;
typedef std::string Data;

Data node_data(AvlNode* node);

void avl_insert(const Data&, AvlNode*&);

bool avl_remove(const Data&, AvlNode*&);

AvlNode* avl_find(const Data&, AvlNode*);

void avl_inorder_print(AvlNode* node);

void avl_delete(AvlNode*& node);

int node_baseheight(const AvlNode* node);

#endif // AVLTREE
