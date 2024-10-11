#include "lab1.h"

int main(int argc, char **argv) 
{
    if (argc < 2)
        return 1;
    

    FILE *input = fopen(argv[1], "r");

    Array *arr = array_create_and_read(input);
    arr = task1(arr, input);

    Array *correctAns = array_create_and_read(input);

    bool isIncorrect = false;

    for(int i = 0; i < array_size(arr); i++)
    {
        if(array_get(arr,i) != array_get(correctAns,i))
        {
            std::cout << "Incorrect answer in " << i << "element" << std::endl;
            isIncorrect = true;
        }
    }

    if(isIncorrect)
    {
        std::cout << "TEST 1 FAIL: wrong answer. Current answer is: -1 4 -12 -10 -1 -19 -12- 2 -11" << std::endl;
        return 1;
    }

    array_delete(arr);
    array_delete(correctAns);
    
    arr = array_create_and_read(input);
    arr = task2(arr);
    correctAns = array_create_and_read(input);

    if(array_size(arr) != array_size(correctAns))
    {
        std::cout << "TEST 2 FAIL: Incorrect array size: " << array_size(arr) << " current size is: " << array_size(correctAns) << std::endl;
        return 1;
    }

    for(size_t i = 0; i < array_size(arr); i++)
    {
        if(array_get(arr, i) != array_get(correctAns, i))
        {
            std::cout << "Incorrect element: " << i << std::endl;
            isIncorrect = true;
        }
    }
    if(isIncorrect)
    {
        std::cout << "TEST 2 FAIL: wrong answer. Current answer is: 7 5 3 2";
        return 1;
    }

    array_delete(arr);
    array_delete(correctAns);

    fclose(input);
    return 0;
}
