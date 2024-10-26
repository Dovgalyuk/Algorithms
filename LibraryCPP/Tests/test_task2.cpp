#include "lab2.h"

void check(FILE* input, FILE* out, Stack* stack) {

    int output_value, expected_value;
    int is_equal = 1;

    while (fscanf(out, "%d", &output_value) == 1 &&
           fscanf(input, "%d", &expected_value) == 1) {
        if (output_value != expected_value) {
            is_equal = 0;
            std::cout << "Test failed. Expected: " << expected_value << ", Got: " << output_value << "\n";
        }
    }

    if ((fscanf(out, "%d", &output_value) == 1) ||
        (fscanf(input, "%d", &expected_value) == 1)) {
        is_equal = 0;
        printf("Файлы имеют разное количество чисел.\n");
    }

    if (is_equal) {
        std::cout << "Test passed.\n";
    } 

}

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

    fclose(out);

    FILE* out1 = fopen("out.txt", "r");

    check(input, out1, stack);

    stack_delete(stack);

    fclose(input);
    fclose(out1);

    return 0;
}