#include <iostream>
#include <fstream>
#include "queue.h"
#include <string>

int main()
{
  Queue *queue = queue_create();

  std::ifstream inFile("in.txt");
  std::ofstream outFile("out.txt");

  size_t size;
  std::string buf;

  if (!inFile.is_open())
  {
    std::cout << "Error opening input file";
    return 0;
  }
  else
  {
    getline(inFile, buf);
    size = stoi(buf);
    if (size <= 0)
    {
      std::cout << "Wrong size";
      return 0;
    }
    for (size_t k = 0; k < size; k++)
    {
      getline(inFile, buf);
      queue_insert(queue, stoi(buf));
    }
  }

  if (!outFile.is_open())
  {
    std::cout << "Error opening output file";
    return 0;
  }
  else
  {
    int add = 0;
    int out, firstNum, secondNum;
    while (!(queue_empty(queue)))
    {
      for (size_t k = 0; k < size; k++)
      {
        getline(inFile, buf);
        secondNum = stoi(buf);
        firstNum = queue_get(queue);
        out = (secondNum + firstNum) + add;
        add = out / 10;
        outFile << out % 10 << std::endl;
        queue_remove(queue);
      }
    }
    if (add != 0)
    {
      outFile << add;
    }
  }

  return 0;
}