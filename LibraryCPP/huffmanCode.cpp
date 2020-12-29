#include "huffmanCode.h"
#include <vector>
#include <map>

void huffman_fileCursorPositionStart(std::ifstream& fileIn)
{
   fileIn.clear();
   fileIn.seekg(0, std::ios::beg);
}

void huffman_makeAlphabet(std::ifstream& fileIn, Array* symbolsCount)
{
   std::string fileSymbols;
   std::stringstream fileSymbolsStream;

   fileSymbolsStream << fileIn.rdbuf();
   fileSymbols = fileSymbolsStream.str();

   huffman_fileCursorPositionStart(fileIn);
   for (unsigned long long int i = 0; i < fileSymbols.size(); i++)
      array_set(symbolsCount, fileSymbols[i], array_get(symbolsCount, fileSymbols[i]) + 1);
}

size_t huffman_alphabetGetSymbolsCount(Array* symbolsCount)
{
   size_t count = 0;
   for (uint16_t i = 0; i < 256; i++)
      if (array_get(symbolsCount, i))
         count++;
   return count;
}

void huffman_makeNodesQueue(PriorityQueue* queue, Array* symbolsCount)
{
   for (uint16_t i = 0; i < 256; i++)
      if (array_get(symbolsCount, i))
         priorityQueue_insert(queue, huffman_createLeafNode(i, array_get(symbolsCount, i)));
}

void huffman_writeBitToByte(std::ofstream& fileOut, uint8_t& byte, uint8_t& bitsCount, bool bitState)
{
   byte = byte | bitState << (7 - bitsCount++);

   if (bitsCount == 8)
   {
      bitsCount = 0;
      fileOut.put(byte);
      byte = 0;
   }
}

void huffman_writeSymbolToFile(unsigned char symbol, std::ofstream& fileOut, uint8_t& byte, uint8_t& bitsCount)
{
   for (uint8_t i = 0; i < 8; i++)
      huffman_writeBitToByte(fileOut, byte, bitsCount, ((symbol >> (7 - i)) & 1));
}

void huffman_saveTreeToFile(std::ofstream& fileOut, HuffmanNode* node, uint8_t& byte, uint8_t& bitsCount)
{
   if (huffman_nodeIsLeaf(huffman_getLeftNode(node)))
   {
      huffman_writeBitToByte(fileOut, byte, bitsCount, 1);
      huffman_writeSymbolToFile(huffman_getNodeChar(huffman_getLeftNode(node)), fileOut, byte, bitsCount);
   }
   else
   {
      huffman_writeBitToByte(fileOut, byte, bitsCount, 0);
      huffman_saveTreeToFile(fileOut, huffman_getLeftNode(node), byte, bitsCount);
   }

   if (huffman_nodeIsLeaf(huffman_getRightNode(node)))
   {
      huffman_writeBitToByte(fileOut, byte, bitsCount, 1);
      huffman_writeSymbolToFile(huffman_getNodeChar(huffman_getRightNode(node)), fileOut, byte, bitsCount);
   }
   else
   {
      huffman_writeBitToByte(fileOut, byte, bitsCount, 0);
      huffman_saveTreeToFile(fileOut, huffman_getRightNode(node), byte, bitsCount);
   }
}

void huffman_saveTotalSymbolsToFile(std::ofstream& fileOut, unsigned long long int total)
{
   uint8_t byte = 0;
   uint8_t bitsCount = 0;
   uint8_t totalBytesCount = 0;

   if (total < UINT8_MAX)
      totalBytesCount = 1;
   else if (total < UINT16_MAX)
      totalBytesCount = 2;
   else if (total < UINT32_MAX)
      totalBytesCount = 4;
   else
      totalBytesCount = 8;

   for (uint8_t i = 0; i < totalBytesCount * 8; i++)
      huffman_writeBitToByte(fileOut, byte, bitsCount, ((total >> ((totalBytesCount * 8 - 1) - i)) & 1));
}

void huffman_makeTable(HuffmanNode* node, std::map<unsigned char, std::vector<bool>>& table, std::vector<bool>& code)
{
   if (huffman_getLeftNode(node))
   {
      code.push_back(0);
      huffman_makeTable(huffman_getLeftNode(node), table, code);
   }
   if (huffman_getRightNode(node))
   {
      code.push_back(1);
      huffman_makeTable(huffman_getRightNode(node), table, code);
   }

   if (huffman_nodeIsLeaf(node))
      table[huffman_getNodeChar(node)] = code;
   
   if (!code.empty())
      code.pop_back();
}

void huffman_compress(std::ifstream& fileIn, const std::string& compressedFileName)
{
   uint8_t byte = 0;
   uint8_t bitsCount = 0;

   Array* symbolsCount = array_create(256);
   huffman_makeAlphabet(fileIn, symbolsCount);

   PriorityQueue* nodesQueue = priorityQueue_create(huffman_alphabetGetSymbolsCount(symbolsCount));
   huffman_makeNodesQueue(nodesQueue, symbolsCount);

   while (priorityQueue_getSize(nodesQueue) > 1)
   {
      HuffmanNode* firstNode = priorityQueue_getNode(nodesQueue);
      priorityQueue_remove(nodesQueue);

      HuffmanNode* newInternalNode = huffman_createInternalNode(firstNode, priorityQueue_getNode(nodesQueue));
      priorityQueue_remove(nodesQueue);

      priorityQueue_insert(nodesQueue, newInternalNode);
   }

   HuffmanNode* huffmanTree = priorityQueue_getNode(nodesQueue);
   priorityQueue_delete(nodesQueue);

   std::ofstream fileOut;
   fileOut.open(compressedFileName, std::ios::binary);

   if (!huffman_nodeIsLeaf(huffmanTree))
      huffman_writeBitToByte(fileOut, byte, bitsCount, 0);
   else
      huffman_writeBitToByte(fileOut, byte, bitsCount, 1);

   huffman_saveTreeToFile(fileOut, huffmanTree, byte, bitsCount);

   if (bitsCount)
   {
      fileOut.put(byte);
      bitsCount = 0;
      byte = 0;
   }

   fileOut.put((unsigned int) 255);
   huffman_saveTotalSymbolsToFile(fileOut, huffman_getNodeWeight(huffmanTree));
   fileOut.put((unsigned int) 255);

   std::vector<bool> symbolCode;
   std::map<unsigned char, std::vector<bool>> table;

   huffman_makeTable(huffmanTree, table, symbolCode);
   huffmanTree = huffman_deleteTree(huffmanTree);

   while (!fileIn.eof())
   {
      symbolCode = table[fileIn.get()];
      for (uint8_t i = 0; i < symbolCode.size(); i++)
         huffman_writeBitToByte(fileOut, byte, bitsCount, symbolCode[i]);
   }

   if (bitsCount)
      fileOut.put(byte);

   fileOut.close();
}


/* DECOMPRESS FUNCTIONS */


bool huffman_getBitFromByte(std::ifstream& fileIn, uint8_t& byte, uint8_t& bitsCount)
{  
   bool result = (byte >> (7 - bitsCount++)) & 1;
   
   if (bitsCount == 8)
   {
      bitsCount = 0;
      byte = fileIn.get();
   }  
   
   return result; 
}

unsigned char huffman_getSymbolFromByte(std::ifstream& fileIn, uint8_t& byte, uint8_t& bitsCount)
{
   unsigned char symbol = 0;
   for (uint8_t i = 0; i < 8; i++)
   {
      if (bitsCount == 8)
      {
         bitsCount = 0;
         byte = fileIn.get();
      }
      symbol = symbol | (((byte >> (7 - bitsCount)) & 1) << (7 - i));
      bitsCount++;
   }
   
   if (bitsCount == 8)
   {
      bitsCount = 0;
      byte = fileIn.get();
   }  
   
   return symbol;
}

bool huffman_getCurrentBitState(const uint8_t& byte, const uint8_t& bitsCount)
{
   return (byte >> (7 - bitsCount)) & 1;
}

HuffmanNode* huffman_rebuildHuffmanTree(std::ifstream& fileIn, HuffmanNode* node, uint8_t& byte, uint8_t& bitsCount)
{
   bool isLeaf = huffman_getBitFromByte(fileIn, byte, bitsCount);

   if (!node)
   {
      if (!isLeaf)
         node = huffman_createInternalNode(NULL, NULL);
      else
      {
         unsigned char symbol = huffman_getSymbolFromByte(fileIn, byte, bitsCount);
         node = huffman_createLeafNode(symbol, 0);
         return node;
      }
   }

   if (!isLeaf)
   {
      if (!huffman_getCurrentBitState(byte, bitsCount))
         huffman_setLeftNode(node, huffman_createInternalNode(NULL, NULL));
      huffman_setLeftNode(node, huffman_rebuildHuffmanTree(fileIn, huffman_getLeftNode(node), byte, bitsCount));

      if (!huffman_getCurrentBitState(byte, bitsCount))
         huffman_setRightNode(node, huffman_createInternalNode(NULL, NULL));
      huffman_setRightNode(node, huffman_rebuildHuffmanTree(fileIn, huffman_getRightNode(node), byte, bitsCount));
   }
   else
   {
      unsigned char symbol = huffman_getSymbolFromByte(fileIn, byte, bitsCount);
      return huffman_createLeafNode(symbol, 0);
   }

   return node;
}

unsigned long long int huffman_readSymbolsCountFromFile(std::ifstream& fileIn, uint8_t& byte)
{
   uint8_t symbolsBytesCount = 0;
   unsigned long long int symbolsCount = 0;

   while ((byte = fileIn.get()) != 255)
   {
      symbolsCount = symbolsCount << (symbolsBytesCount * 8);
      symbolsCount = symbolsCount | (unsigned long long int) byte;
      symbolsBytesCount++;
   }

   return symbolsCount;
}

void huffman_decompress(std::ifstream& fileIn, const std::string& decompressedFileName)
{
   uint8_t byte = fileIn.get();
   uint8_t bitsCount = 0;

   std::ofstream fileOut;
   fileOut.open(decompressedFileName, std::ios::binary);

   HuffmanNode* huffmanTree = huffman_rebuildHuffmanTree(fileIn, huffmanTree, byte, bitsCount);
   
   huffman_fileCursorPositionStart(fileIn);
   while ((byte = fileIn.get()) != 255);

   bool flag = true;
   unsigned long long int symbolsRead = 0;
   unsigned long long int symbolsCount = huffman_readSymbolsCountFromFile(fileIn, byte);

   HuffmanNode* currentNode = huffmanTree;

   byte = fileIn.get();
   bitsCount = 0;
   
   while (flag)
   {
      if (bitsCount == 8)
      {
         byte = fileIn.get();
         bitsCount = 0;

         if (fileIn.eof())
            break;
      }
     
      for (uint8_t i = 0; i < 8; i++)
      {
         if (huffman_getBitFromByte(fileIn, byte, bitsCount))
            currentNode = huffman_getRightNode(currentNode);
         else
            currentNode = huffman_getLeftNode(currentNode);

         if (!currentNode)
            currentNode = huffmanTree;
         else if (huffman_nodeIsLeaf(currentNode))
         {
            fileOut.put(huffman_getNodeChar(currentNode));
            currentNode = huffmanTree;
            symbolsRead++;

            if (symbolsRead == symbolsCount)
            {
               flag = false;
               break;
            }
         }
      }
   }

   huffmanTree = huffman_deleteTree(huffmanTree);
   fileOut.close();
}
