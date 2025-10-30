#include <iostream>
#include <fstream>
#include "array.h"
using namespace std;
Array *array_create_and_read(std::ifstream &input)
{
    int n;
    input >> n;
    
    Array *arr = array_create(n);
  
    for(int i = 0; i < n; i++)
    { 
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{
  if (arr == nullptr || array_size(arr) != 30) {
    return;
  }
  double sum1 = 0, sum2 = 0, sum3 = 0;

  for(size_t i = 0; i < 10; i++) {
    sum1 += array_get(arr, i);
  }
  for(size_t i = 10; i < 20; i++) {
    sum2 += array_get(arr, i);
  }
  for(size_t i = 20; i < 30; i++) {
    sum3 += array_get(arr, i);
  }
  double average1 = sum1 / 10.0;
  double average2 = sum2 / 10.0;
  double average3 = sum3 / 10.0;

  cout << average1 << endl;
  cout << average2 << endl;
  cout << average3 << endl;

}

void task2(Array *arr)
{
  if (arr == nullptr || array_size(arr) < 5) {
    return;
  }
  size_t n = array_size(arr);
  int max_sum = 0;
  size_t max_start_index = 0;

  for(size_t i = 0; i <= n - 5; i++) {
    int current_sum = 0;
    for (size_t j = i; j < i + 5; j++) {
      current_sum += array_get(arr, j);
    }

    if(current_sum > max_sum) {
      max_sum = current_sum;
      max_start_index = i;
    }
  }

  for (size_t i = max_start_index; i < max_start_index + 5; i++) {
    cout << array_get(arr, i);
    if (i < max_start_index + 4) {
      cout << ", ";
    }
  }
  cout << endl;
  cout << max_sum << endl;

}

int main(int argc, char **argv)
{ 
    Array *arr = NULL;
    std::ifstream input(argv[1]);
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    input.close();
}