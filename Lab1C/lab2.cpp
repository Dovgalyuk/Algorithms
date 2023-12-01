#include <iostream>
#include <stack.h>
#include <fstream>
#include <string>
#include <algorithm>

int main()
{
  Stack *stack = stack_create();

  std::ifstream inFile("in.txt");
  std::ofstream outFile("out.txt");

  while (inFile)
  {
    std::string line;
    getline(inFile, line);

    if (line == "")
    {
      continue;
    }

    for (int i = 0; i < line.length(); i++)
    {
      line[i] = tolower(line[i]);
    }

    if (line[0] != '<' || line[line.length() - 1] != '>')
    {
      outFile << "Wrong input format";
      return 0;
    }

    if (line[1] != '/')
    {
      int hash_open_tag = std::hash<std::string>()(line);
      stack_push(stack, hash_open_tag);
    }
    else
    {
      if (stack_empty(stack))
      {
        outFile << "NO";
        return 0;
      }

      int hash_open_tag = stack_get(stack);
      line.erase(1, 1);
      int hash_close_tag = std::hash<std::string>()(line);
      if (hash_open_tag == hash_close_tag)
      {
        stack_pop(stack);
      }
      else
      {
        outFile << "NO";
        stack_delete(stack);
        return 0;
      }
    }
  }

  if (stack_empty(stack))
  {
    outFile << "YES";
  }
  else
  {
    outFile << "NO";
    stack_delete(stack);
  }

  return 0;
}