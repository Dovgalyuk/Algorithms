#include "lab1.h"

int main(int argc, char **argv)
{
    FILE *input;
    if (argc <= 1)
        input = stdin;
    else
        input = fopen(argv[1], "r");

    InputData inputArrAB = array_create_and_read(input);
    task1(inputArrAB);
    array_delete(inputArrAB.array);

    inputArrAB = array_create_and_read(input);
    task2(inputArrAB.array);
    array_delete(inputArrAB.array);
    
    fclose(input);
    return 0;
}