#include "../tasks.h"
#include <fstream>
#include <iostream>
#include "../../LibraryCPP/array.h"

using namespace std;

void task2(const char *filename)
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

  Array *arr = array_create(size);
  Array *array_counter = array_create(1001);
  int array_counter_size = array_size(array_counter);

  for (int i = 0; i < array_counter_size; ++i)
  {
    array_set(array_counter, i, 0);
  }

  for (int i = 0; i < size; i++)
  {
    int value;
    if (!(in >> value))
    {
      cout << "There is not enough data in the file to populate the array\n";
      array_delete(arr);
      array_delete(array_counter);
      return;
    }

    array_set(arr, i, value);

    int current_count = array_get(array_counter, value);
    current_count++;
    array_set(array_counter, value, current_count);
  }

  int max_count = array_get(array_counter, 0);
  int most_frequent = 0;

  for (int i = 1; i < array_counter_size; ++i)
  {
    int count = array_get(array_counter, i);

    if (max_count < count)
    {
      max_count = count;
      most_frequent = i;
    }
  }

  in.close();

  cout << "Most frequent number = " << most_frequent << endl;
  cout << "Count = " << max_count << endl;

  array_delete(arr);
  array_delete(array_counter);
}