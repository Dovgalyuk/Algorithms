#include "array.h"
#include <stdio.h>

/*Array *array_create_and_read(FILE *input) {
  int n;
  fscanf(input, "%d", &n);
  Array *arr = array_create(n, NULL);
  for (int i = 0; i < n; ++i) {
    int x;
    fscanf(input, "%d", &x);
    array_set(arr, i, x);
  }
  return arr;
}

void task1(Array *arr) {
  Data sum = 0;
  for (size_t i = 0; i < array_size(arr); i++) {
    sum += array_get(arr, i);
  }

  double average = double(sum) / double(array_size(arr));
}
void task2(Array *arr) {}

*/
int main(int argc, char **argv)
{
    /*Array *arr = NULL;
    FILE *input = fopen(argv[1], "r");
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    fclose(input);*/
    return 0;
}
