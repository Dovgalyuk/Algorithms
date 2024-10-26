#include "lab2.h"

int main(int argc, char **argv)
{
    FILE *input;
    if (argc <= 1)
        input = stdin;
    else
        input = fopen(argv[1], "r");

    FILE* out = fopen("out.txt", "w");

    Stack *stack = stack_create();
    
    task1(input, stack, out);

    stack_delete(stack);

    fclose(input);
    fclose(out);

    return 0;
}