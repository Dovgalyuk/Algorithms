#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H
#include <string>

typedef std::string Key;

struct Node;


Node* splay_create(const Key data);

void splay(Node* root, Node* node);

void replace(Node* root, Node* u, Node* v);

Node* subtree_minimum(Node* u);

Node* subtree_maximum(Node* u);

void insert(Node* root, const Key key);

Node* find(Node* root, const Key key);

void erase(Node* root, const Key key);

Node* splay_delete(Node* root);

#endif