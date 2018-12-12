#ifndef TREE_H
#define TREE_H

typedef int Data;

struct Leaf;
struct Tree;

//Создаёт дерево.
Tree* tree_create();

//Добавляет значение в дерево.
void insert(Leaf* tree, Data value);

//Возвращает указатель на корень дерева.
Leaf* get_root(const Tree* tree);

//Возвращает самую длинную последовательность.
void get_result_length(Leaf* leaf);

//Возвращает длину самой длинной последовательности.
void get_result_hight(Leaf* leaf);

#endif
