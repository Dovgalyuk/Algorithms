#include <iostream>
#include <fstream>
#include <cmath>
#include "../tasks.h"

using namespace std;

bool isPrime(int n)
{
  if (n < 2)
  {
    return false;
  }

  for (int i = 2; i <= std::sqrt(n); ++i)
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

  int *arr = new int[size];

  int index = 0;

  for (int currentNumber = 2; index < size; ++currentNumber)
  {
    if (isPrime(currentNumber))
    {
      arr[index] = currentNumber;
      ++index;
    }
  }

  for (int i = 0; i < size; i++)
  {
    cout << "[" << i << "]" << " = " << arr[i] << endl;
  }

  delete[] arr;
}
