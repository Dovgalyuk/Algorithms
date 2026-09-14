#include <iostream>
#include <fstream>
#include <cmath>
#include "../tasks.h"
#include "../../LibraryCPP/array.h"

using namespace std;

bool isPrime(int n)
{
  if (n < 2)
  {
    return false;
  }

  int sqrt_n = sqrt(n);

  for (int i = 2; i <= sqrt_n; ++i)
  {
    if (n % i == 0)
    {
      return false;
    }
  }

  return true;
}

void task1(const char *filename)
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

  Array *arr = array_create(size);

  int index = 0;

  for (int currentNumber = 2; index < size; ++currentNumber)
  {
    if (isPrime(currentNumber))
    {
      array_set(arr, index, currentNumber);
      ++index;
    }
  }

  for (int i = 0; i < size; i++)
  {
    cout << "[" << i << "]" << " = " << array_get(arr, i) << endl;
  }

  array_delete(arr);
}
