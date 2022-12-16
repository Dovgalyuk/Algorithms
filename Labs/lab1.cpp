#include <iostream>
#include <ctime>
#include <climits>
#include "array.h"

void fill_array(Array *array)
{
  for (int i = 0; i < array_size(array); i++)
  {
    array_set(array, i, std::rand() % 10 + 1);
  }
}

void print_array(Array *array)
{
  for (int i = 0; i < array_size(array); i++)
  {
    std::cout << array_get(array, i) << " ";
  }
  std::cout << "\n";
}

int main()
{
  srand(time(0));

  int size;
  std::cin >> size;
  Array *array = array_create(size);
  fill_array(array);
  print_array(array);

  int max_length = 0;
  int current_length = 0;
  for (int i = 0; i < array_size(array); i++)
  {

    if (array_get(array, i) % 2 != 0 && i < array_size(array))
    {
      current_length += 1;
    }
    else
    {
      current_length = 0;
    }
    if (current_length > max_length)
    {
      max_length = current_length;
    };
  }

  std::cout << max_length << std::endl;
}