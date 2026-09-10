#include <iostream>
#include <fstream>
#include "../tasks.h"

using namespace std;

void task1(const char* filename)
{
  ifstream in(filename);

  if (!in.is_open())
  {
    cout << "Cant open a file\n";
    return;
  }

  int number;
  int size = 0;

  while (in >> number)
  {
    size = number;
    break;
  }

  in.close();

  int* arr = new int[size];

  for(int i = 0; i < size; i++)
  {
    arr[i] = 2 * (i + 1);
  }

  for(int i = 0; i < size; i++)
  {
    cout << "[" << i << "]" << " = " << arr[i] << endl;
  }

  delete[] arr;
}
