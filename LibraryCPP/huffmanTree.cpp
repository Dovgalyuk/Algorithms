#include "huffmanTree.h"

struct HuffmanNode
{
   bool isLeaf;
   unsigned long long int weight;
   unsigned char symbol;

   HuffmanNode* leftNode;
   HuffmanNode* rightNode;
};

HuffmanNode* huffman_createLeafNode(unsigned char symbol, unsigned long long int weight)
{
   HuffmanNode* node = new HuffmanNode;
   node->isLeaf = true;
   node->symbol = symbol;
   node->weight = weight;
   node->leftNode = NULL;
   node->rightNode = NULL;
   return node;
}

HuffmanNode* huffman_createInternalNode(HuffmanNode* leftNode, HuffmanNode* rightNode)
{
   HuffmanNode* node = new HuffmanNode;
   node->isLeaf = false;
   node->leftNode = leftNode;
   node->rightNode = rightNode;
   node->weight = (leftNode && rightNode) ? leftNode->weight + rightNode->weight : 0;
   return node;
}

HuffmanNode* huffman_getLeftNode(HuffmanNode* node)
{
   return node ? node->leftNode : NULL;
}

HuffmanNode* huffman_getRightNode(HuffmanNode* node)
{
   return node ? node->rightNode : NULL;
}

void huffman_setLeftNode(HuffmanNode* node, HuffmanNode* newNode)
{
   node->leftNode = node->leftNode ? node->leftNode : newNode;
}

void huffman_setRightNode(HuffmanNode* node, HuffmanNode* newNode)
{
   node->rightNode = node->rightNode ? node->rightNode : newNode;
}

bool huffman_nodeIsLeaf(HuffmanNode* node)
{
   return node->isLeaf;
}

unsigned char huffman_getNodeChar(HuffmanNode* node)
{
   return node->symbol;
}

unsigned long long int huffman_getNodeWeight(HuffmanNode* node)
{
   return node->weight;
}

HuffmanNode* huffman_deleteTree(HuffmanNode* node)
{
   if (!node)
   {
      huffman_deleteTree(node->leftNode);
      huffman_deleteTree(node->rightNode);
      delete node;
   }
   return NULL;
}

void huffman_printTree(HuffmanNode* node, unsigned int height)
{
   if (node)
   {
      huffman_printTree(node->rightNode, height + 1);
      for (unsigned int i = 0; i < height; i++)
         std::cout << "  ";
      if (node->isLeaf)
         std::cout << (unsigned char) node->symbol;
      else
         std::cout << node->weight;
      huffman_printTree(node->leftNode, height + 1);
   }
   else
      std::cout << std::endl;
}
