#ifndef SPLAYTREE_H
#define SPLAYTREE_H
#include <string>

typedef std::string Key;
typedef std::string Data;

struct Node;

void splay(Node *node);

void node_set(Node* node, const Key& key, const Data& value);

Data node_get_value(Node* node);

Key node_get_key(Node* node);

Node* node_create();

void tree_delete(Node* root);

Node* node_find(Node* root, const Key& key);

bool node_add(Node* root, Node* new_node);

Node* root_remove(Node* root);

int tree_height(Node* root, int height);

void print_tree(Node* root);//DEBUG

#endif