#include "../tasks.h"
#include <fstream>
#include <iostream>

using namespace std;

void task2(const char* filename)
{
  ifstream in(filename);

  if (!in.is_open())
  {
    cout << "Cant open a file" << endl;
    return;
  }

  int size = 0;

  if (!(in >> size))
  {
    cout << "Failed to read the array size\n";
    return;
  }

  if (size <= 0)
  {
    cout << "The array size is 0 or invalid\n";
    return;
  }

  int *arr = new int[size];

  for (int i = 0; i < size; i++)
  {
    if(!(in >> arr[i]))
    {
      cout << "There is not enough data in the file to populate the array\n";
      return;
    }
  }

  in.close();

  for (int i = 0; i < size; i++)
  {
    cout << "[" << i << "] = " << arr[i] << endl;
  }

  delete[] arr;
}