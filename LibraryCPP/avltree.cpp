#include "avltree.h"

//#define DEBUG

struct Node
{
   Data data;
   Key key;

   int8_t height;
   Node* leftNode;
   Node* rightNode;
};

Node* node_create(const Data& data, const Key& key)
{
   Node* node = new Node;
   node->data = data;
   node->key = key;
   node->height = 1;
   node->leftNode = NULL;
   node->rightNode = NULL;
   return node;
}

Node* node_insert(Node* node, const Data& data, const Key& key)
{
   if (!node)
      return node_create(data, key);
   else
   {
      if (key < node->key)
         node->leftNode = node_insert(node->leftNode, data, key);
      else if (key > node->key)
         node->rightNode = node_insert(node->rightNode, data, key);
      else
         return node;
   }
   return node_balance(node);
}

Node* node_balance(Node* node)
{
   node_fixHeight(node);
   if (node_getBalance(node) == 2)
   {
      if (node_getBalance(node->leftNode) < 0)
         return node_bigRightRotate(node);
      else
         return node_smallRightRotate(node);
   }
   else if (node_getBalance(node) == -2)
   {
      if (node_getBalance(node->rightNode) > 0)
         return node_bigLeftRotate(node);
      else
         return node_smallLeftRotate(node);
   }
#ifdef DEBUG 
      std::cout << (node_isBalanced(node) ? "BALANCED" : "NOT_BALANCED") << std::endl;
#endif
   return node;
}

bool node_isBalanced(Node* node)
{
   if (!node)
      return true;
   else
   {
      if (std::abs(node_getBalance(node)) < 2)
         return true;
      else
         return false;
   }
}

void node_fixHeight(Node* node)
{
   node->height = node_getMaxHeight(node_getHeight(node->leftNode), node_getHeight(node->rightNode)) + 1;
}

int8_t node_getBalance(Node* node)
{
   return node_getHeight(node->leftNode) - node_getHeight(node->rightNode);
}

int8_t node_getHeight(Node* node)
{
   return node ? node->height : 0;
}

int8_t node_getMaxHeight(const int8_t leftHeight, const int8_t rightHeight)
{
   return (leftHeight > rightHeight) ? leftHeight : rightHeight;
}

Node* node_smallLeftRotate(Node* aNode)
{
   Node* bNode = aNode->rightNode;
   aNode->rightNode = bNode->leftNode;
   bNode->leftNode = aNode;
   node_fixHeight(aNode);
   node_fixHeight(bNode);
   return bNode;
}

Node* node_smallRightRotate(Node* aNode)
{
   Node* bNode = aNode->leftNode;
   aNode->leftNode = bNode->rightNode;
   bNode->rightNode = aNode;
   node_fixHeight(aNode);
   node_fixHeight(bNode);
   return bNode;
}

Node* node_bigLeftRotate(Node* aNode)
{
   Node* bNode = aNode->rightNode;
   Node* cNode = bNode->leftNode;
   aNode->rightNode = cNode->leftNode;
   bNode->leftNode = cNode->rightNode;
   cNode->leftNode = aNode;
   cNode->rightNode = bNode;
   node_fixHeight(aNode);
   node_fixHeight(bNode);
   node_fixHeight(cNode);
   return cNode;
}

Node* node_bigRightRotate(Node* aNode)
{
   Node* bNode = aNode->leftNode;
   Node* cNode = bNode->rightNode;
   aNode->leftNode = cNode->rightNode;
   bNode->rightNode = cNode->leftNode;
   cNode->leftNode = bNode;
   cNode->rightNode = aNode;
   node_fixHeight(aNode);
   node_fixHeight(bNode);
   node_fixHeight(cNode);
   return cNode;
}

Node* node_getLeftChild(Node* node)
{
   return node->leftNode ? node->leftNode : NULL;
}

Node* node_getRightChild(Node* node)
{
   return node->rightNode ? node->rightNode : NULL;
}

Data node_getData(Node* node)
{
   return node ? node->data : "";
}

Node* node_search(Node* node, const Key& key)
{
   if (!node)
      return NULL;
   if (node->key == key)
      return node;
   if (key < node->key)
      return node_search(node->leftNode, key);
   else
      return node_search(node->rightNode, key);
}

Node* node_findMin(Node* node)
{
   return node->leftNode ? node_findMin(node->leftNode) : node;
}

Node* node_findMinParent(Node* fromNode, Node* toNode)
{
   if (!fromNode)
      return NULL;
   if (fromNode == toNode || fromNode->leftNode == toNode)
      return fromNode;
   else
      return node_findMinParent(fromNode, toNode);
}

Node* node_remove(Node* node, const Key& key)
{
   if (!node)
      return node;
   else
   {
      if (key < node->key)
         node->leftNode = node_remove(node->leftNode, key);
      else if (key > node->key)
         node->rightNode = node_remove(node->rightNode, key);
      else
      {
         if (!node->leftNode && !node->rightNode)
         {
            delete node;
            return NULL;
         }
         else if (!node->leftNode || !node->rightNode)
         {
            Node* nextNode = node->leftNode ? node->leftNode : node->rightNode;
            delete node;
            return nextNode;
         }
         else
         {
            Node* leftMinNode = node_findMin(node->rightNode);
            Node* leftMinParentNode = node_findMinParent(node->rightNode, leftMinNode);
            
            node->data = leftMinNode->data;
            node->key = leftMinNode->key;
            
            if (leftMinNode == leftMinParentNode)
            {
               if (!leftMinParentNode->rightNode)
                  node->rightNode = NULL;
            }
            else
            {
               if (!leftMinNode->rightNode)
                  leftMinParentNode->leftNode = NULL;
               else
                  leftMinParentNode->leftNode = leftMinNode->rightNode;
            }

            delete leftMinNode;
         }
      }
   }
   return node_balance(node);
}

Node* node_delete(Node* node)
{
   if (!node)
   {
      node_delete(node->leftNode);
      node_delete(node->rightNode);
      delete node;
   }
   return NULL;
}

void node_printTree(Node* node, unsigned height)
{
   if (node)
   {
      node_printTree(node->rightNode, height + 1);
      for (int i = 0; i < height; i++)
         std::cout << "  ";
      std::cout << node->data;
      node_printTree(node->leftNode, height + 1);
   }
   else
      std::cout << std::endl;
}
