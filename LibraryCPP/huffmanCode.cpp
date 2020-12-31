#include "huffmanCode.h"

struct Byte
{
   uint8_t byte = 0;
   uint8_t bitsCount = 0;
   std::ifstream& fileIn;
   Byte(std::ifstream& fileInStream) : fileIn(fileInStream) { }
};

void huffman_fileCursorPositionStart(std::ifstream& fileIn)
{
   fileIn.clear();
   fileIn.seekg(0, std::ios::beg);
}

void huffman_makeAlphabet(std::ifstream& fileIn, Array* symbolsCount)
{
   unsigned char symbol = 0; 
   while ((symbol = fileIn.get()) && !fileIn.eof())
      array_set(symbolsCount, symbol, array_get(symbolsCount, symbol) + 1);
   huffman_fileCursorPositionStart(fileIn);
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

void huffman_writeBitToByte(std::ofstream& fileOut, Byte& byteStruct, bool bitState)
{   
   byteStruct.byte = (byteStruct.byte << 1) | bitState;
   byteStruct.bitsCount++;

   if (byteStruct.bitsCount == 8)
   {
      byteStruct.bitsCount = 0;
      fileOut.put(byteStruct.byte);
      byteStruct.byte = 0;
   }
}

void huffman_writeSymbolToFile(unsigned char symbol, std::ofstream& fileOut, Byte& byteStruct)
{
   for (uint8_t i = 0; i < 8; i++)
      huffman_writeBitToByte(fileOut, byteStruct, ((symbol >> i) & 1));
}

void huffman_saveTreeToFile(std::ofstream& fileOut, HuffmanNode* node, Byte& byteStruct)
{
   if (huffman_nodeIsLeaf(huffman_getLeftNode(node)))
   {
      huffman_writeBitToByte(fileOut, byteStruct, 1); 
      huffman_writeSymbolToFile(huffman_getNodeChar(huffman_getLeftNode(node)), fileOut, byteStruct);
   }
   else
   {
      huffman_writeBitToByte(fileOut, byteStruct, 0);
      huffman_saveTreeToFile(fileOut, huffman_getLeftNode(node), byteStruct);
   }

   if (huffman_nodeIsLeaf(huffman_getRightNode(node)))
   {
      huffman_writeBitToByte(fileOut, byteStruct, 1);
      huffman_writeSymbolToFile(huffman_getNodeChar(huffman_getRightNode(node)), fileOut, byteStruct);
   }
   else
   {
      huffman_writeBitToByte(fileOut, byteStruct, 0);
      huffman_saveTreeToFile(fileOut, huffman_getRightNode(node), byteStruct);
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
   {
      byte = byte | ((total >> ((totalBytesCount * 8 - 1) - i)) & 1) << (7 - bitsCount++);

      if (bitsCount == 8)
      {
         bitsCount = 0;
         fileOut.put(byte);
         byte = 0;
      }
   }
}

void huffman_makeTable(HuffmanNode* node, symbolsTableMap& table, std::vector<bool>& code)
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

void huffman_writeUncompletedByte(std::ofstream& fileOut, Byte& byteStruct)
{
   while (byteStruct.bitsCount)
      huffman_writeBitToByte(fileOut, byteStruct, 0);
}

void huffman_compress(std::ifstream& fileIn, const std::string& compressedFileName)
{
   Byte byteStruct(fileIn);

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
      huffman_writeBitToByte(fileOut, byteStruct, 0);
   else
      huffman_writeBitToByte(fileOut, byteStruct, 1);

   huffman_saveTreeToFile(fileOut, huffmanTree, byteStruct);
   huffman_writeUncompletedByte(fileOut, byteStruct);

   fileOut.put((unsigned int) 255);
   huffman_saveTotalSymbolsToFile(fileOut, huffman_getNodeWeight(huffmanTree));
   fileOut.put((unsigned int) 255);

   symbolsTableMap table;
   std::vector<bool> symbolCode;

   huffman_makeTable(huffmanTree, table, symbolCode);
   huffmanTree = huffman_deleteTree(huffmanTree);

   while (!fileIn.eof())
   {
      symbolCode = table[fileIn.get()];
      for (uint8_t i = 0; i < symbolCode.size(); i++)
         huffman_writeBitToByte(fileOut, byteStruct, symbolCode[i]);
   }
  
   huffman_writeUncompletedByte(fileOut, byteStruct);
   fileOut.close();
}


/* DECOMPRESS FUNCTIONS */


bool huffman_getBitFromByte(Byte& byteStruct)
{
   bool result = (byteStruct.byte >> (7 - byteStruct.bitsCount++)) & 1;

   if (byteStruct.bitsCount == 8)
   {
      byteStruct.bitsCount = 0;
      byteStruct.byte = byteStruct.fileIn.get();
   }  
   
   return result; 
}

unsigned char huffman_getSymbolFromByte(Byte& byteStruct)
{
   unsigned char symbol = 0;
   for (uint8_t i = 0; i < 8; i++)
      symbol = symbol | (huffman_getBitFromByte(byteStruct) << i); 
   return symbol;
}

bool huffman_getCurrentBitState(const Byte& byteStruct)
{
   return (byteStruct.byte >> (7 - byteStruct.bitsCount)) & 1;
}

HuffmanNode* huffman_rebuildHuffmanTree(Byte& byteStruct, HuffmanNode* node)
{
   bool isLeaf = huffman_getBitFromByte(byteStruct);

   if (!node)
   {
      if (!isLeaf)
         node = huffman_createInternalNode(NULL, NULL);
      else
      {
         unsigned char symbol = huffman_getSymbolFromByte(byteStruct);
         node = huffman_createLeafNode(symbol, 0);
         return node;
      }
   }

   if (!isLeaf)
   {
      if (!huffman_getCurrentBitState(byteStruct))
         huffman_setLeftNode(node, huffman_createInternalNode(NULL, NULL));
      huffman_setLeftNode(node, huffman_rebuildHuffmanTree(byteStruct, huffman_getLeftNode(node)));

      if (!huffman_getCurrentBitState(byteStruct))
         huffman_setRightNode(node, huffman_createInternalNode(NULL, NULL));
      huffman_setRightNode(node, huffman_rebuildHuffmanTree(byteStruct, huffman_getRightNode(node)));
   }
   else
   {
      unsigned char symbol = huffman_getSymbolFromByte(byteStruct);
      return huffman_createLeafNode(symbol, 0);
   }

   return node;
}

unsigned long long int huffman_readSymbolsCountFromFile(Byte& byteStruct)
{
   uint8_t symbolsBytesCount = 0;
   unsigned long long int symbolsCount = 0;

   while ((byteStruct.byte = byteStruct.fileIn.get()) != 255)
   {
      symbolsCount = symbolsCount << (symbolsBytesCount * 8);
      symbolsCount = symbolsCount | (unsigned long long int) byteStruct.byte;
      symbolsBytesCount++;
   }

   return symbolsCount;
}

void huffman_decompress(std::ifstream& fileIn, const std::string& decompressedFileName)
{
   Byte byteStruct(fileIn);
   byteStruct.byte = fileIn.get();

   std::ofstream fileOut;
   fileOut.open(decompressedFileName, std::ios::binary);

   HuffmanNode* huffmanTree = huffman_rebuildHuffmanTree(byteStruct, huffmanTree);

   huffman_fileCursorPositionStart(fileIn);
   while ((byteStruct.byte = fileIn.get()) != 255);

   bool flag = true;
   unsigned long long int symbolsRead = 0;
   unsigned long long int symbolsCount = huffman_readSymbolsCountFromFile(byteStruct);

   HuffmanNode* currentNode = huffmanTree;

   byteStruct.byte = fileIn.get();
   byteStruct.bitsCount = 0;
   
   while (flag)
   {
      if (byteStruct.bitsCount == 8)
      {
         byteStruct.byte = fileIn.get();
         byteStruct.bitsCount = 0;

         if (fileIn.eof())
            break;
      }
     
      for (uint8_t i = 0; i < 8; i++)
      {
         if (huffman_getBitFromByte(byteStruct))
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
