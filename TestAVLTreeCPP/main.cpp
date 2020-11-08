#include "avltree.h"

int main()
{
   Node* tree = node_create("Test10", "Test1");

   if (node_getData(tree) != "Test10")
      std::cout << "Tree is not created" << std::endl;

   // Small left rotate

   tree = node_insert(tree, "Test20", "Test5"); // To rightNode
   tree = node_insert(tree, "Test30", "Test9"); // To rightNode -> rightNode

   std::cout << "=========" << std::endl;
   node_printTree(tree, 0);
   std::cout << "=========" << std::endl;

   if (node_getData(tree) != "Test20")
      std::cout << "Tree small left rotate error: root" << std::endl;
   if (node_getData(node_getLeftChild(tree)) != "Test10")
      std::cout << "Tree small left rotate error: root->leftNode" << std::endl;
   if (node_getData(node_getRightChild(tree)) != "Test30")
      std::cout << "Tree small left rotate error: root->rightNode" << std::endl;

   // Big left rotate

   tree = node_insert(tree, "Test40", "Test99"); // To rightNode -> rightNode
   tree = node_insert(tree, "Test50", "Test7"); // To rightNode -> leftNode
   tree = node_insert(tree, "Test60", "Test75"); // To rightNode -> rightNode -> rightNode

   std::cout << "=========" << std::endl;
   node_printTree(tree, 0);
   std::cout << "=========" << std::endl;

   if (node_getData(node_getLeftChild(tree)) != "Test20")
      std::cout << "Tree big left rotate error: root->leftNode" << std::endl;
   if (node_getData(node_getRightChild(tree)) != "Test30")
      std::cout << "Tree big right rotate error: root->rightNode" << std::endl;
   if (node_getData(node_getLeftChild(node_getLeftChild(tree))) != "Test10")
      std::cout << "Tree big left rotate error: root->leftNode->leftNode" << std::endl;
   if (node_getData(node_getLeftChild(node_getRightChild(tree))) != "Test60")
      std::cout << "Tree big left rotate error: root->leftNode->rightNode" << std::endl;
   if (node_getData(node_getRightChild(node_getRightChild(tree))) != "Test40")
      std::cout << "Tree big left rotate error: root->rightNode->rightNode" << std::endl;

   // node_search test

   if (node_getData(node_search(tree, "Test75")) != "Test60")
      std::cout << "Tree node search error: Test6" << std::endl;
   if (node_getData(node_search(tree, "Test99")) != "Test40")
      std::cout << "Tree node search error: Test99" << std::endl;

   // node_remove test

   tree = node_remove(tree, "Test9");
   tree = node_remove(tree, "Test5");

   std::cout << "=========" << std::endl;
   node_printTree(tree, 0);
   std::cout << "=========" << std::endl;

   if (node_getData(node_getRightChild(tree)) != "Test40")
      std::cout << "Remove error: Test9" << std::endl;
   if (node_getRightChild(node_getLeftChild(tree)) != NULL)
      std::cout << "Remove error: Test9" << std::endl;
   if (node_getData(node_getLeftChild(tree)) != "Test10")
      std::cout << "Remove error: Test5" << std::endl;

   tree = node_delete(tree);
   return 0;
}
