#include "huffmanCode.h"

int main()
{
   std::ifstream fileIn;
   
   fileIn.open("testText.txt", std::ios::binary);
   huffman_compress(fileIn, "compressedText.arc");
   
   fileIn.close();

   fileIn.open("compressedText.arc", std::ios::binary);
   huffman_decompress(fileIn, "decompessedText.txt");

   fileIn.close();

   return 0;
}
