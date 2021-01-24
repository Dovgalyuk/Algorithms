#pragma once

#include <iostream>

typedef std::string Key;
typedef std::string Data;

struct binaryTree;

binaryTree* createBinTree(const Key& key, const Data& value);
binaryTree* insertElem(binaryTree* root, const Key& key, const Data& value);
binaryTree* deleteElem(binaryTree* root, const Key& key);
binaryTree* findElem(binaryTree* root, const Key& key);
binaryTree* deleteBinTree(binaryTree* root);
Data getTreeData(binaryTree* node);
void printBinTree(binaryTree* root, int offset);