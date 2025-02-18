#include <stdio.h>
#include "../LibraryC/array.h"

// Найти количество элементов, превышающих сумму всех элементов массива
void task1(Array *arr) {
}

// Сдвиг элементов массива в указанном направлении
void task2(Array *arr) {

}

int main(int argc, char **argv)
{
    Array *arr = NULL;
    FILE *input = fopen(argv[1], "r");
    arr = array_create_and_read(input);
    task1(arr);
}