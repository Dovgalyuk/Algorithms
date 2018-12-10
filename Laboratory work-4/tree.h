#ifndef ARRAY_H
#define ARRAY_H
#include <string>

typedef std::string Data;

struct Leaf;
struct Tree;

//Создаёт дерево.
Tree* tree_create();

//Добавляет пару ключ - значение в дерево.
void insert_leaf(Tree* tree, Data key, Data value);

//Получает элемент дерева по указанному ключу.
Data get_value_of_leaf(const Tree* tree, Data key);

//Удаляет элемент дерева.
void delete_leaf(Tree* tree, Data key);

//Возвращает true, если дерево сбалансировано.
int balance_tree(Leaf* leaf);

//Возвращает корень дерева.
Leaf* get_root(Tree* tree);

//Возвращает ключ корня дерева
Data get_root_key(Tree* tree);
#endif
