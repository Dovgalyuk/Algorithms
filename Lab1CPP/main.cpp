#include "lab1.h"
#include <stdio.h>
int main(int argc, char **argv)
{
    FILE *input;
    if (argc <= 1)
    {
        input = stdin;
    }
    else
    {
        input = fopen(argv[1], "r");
    }

    Array *arr = array_create_and_read(input);
    task1(arr);
    task2(arr);

    delete arr;
    fclose(input);
    return 0;
}