#include <iostream>
#include <stdexcept>
#include "array.h"
#include "lab1.h"

void test_task(FILE* input) {
    InputData inputArrAB = array_create_and_read(input);
    int expectedTask1Result;
    fscanf(input, "%d", &expectedTask1Result);

    int resultTask1 = task1(inputArrAB);
    if (resultTask1 == expectedTask1Result) {
        std::cout << "Task 1 passed.\n";
    } else {
        std::cout << "Task 1 failed. Expected: " << expectedTask1Result << ", Got: " << resultTask1 << "\n";
    }
    array_delete(inputArrAB.array);

    inputArrAB = array_create_and_read(input);
    int expectedTask2Result;
    fscanf(input, "%d", &expectedTask2Result);

    int resultTask2 = task2(inputArrAB.array);
    if (resultTask2 == expectedTask2Result) {
        std::cout << "Task 2 passed.\n";
    } else {
        std::cout << "Task 2 failed. Expected: " << expectedTask2Result << ", Got: " << resultTask2 << "\n";
    }
    array_delete(inputArrAB.array);
}

int main(int argc, char **argv)
{
    FILE *input;
    if (argc <= 1)
        input = stdin;
    else
        input = fopen(argv[1], "r");

    try {
        test_task(input);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    fclose(input);
    return 0;
}
