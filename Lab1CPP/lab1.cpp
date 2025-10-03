#include <iostream>
#include <fstream>
#include "array.h"

Array *array_create_and_read(std::istream& input)
{
    size_t n;
    input >> n;

    /* Create array */
    Array *arr = array_create(n);
    /* Read array data */
    for (size_t i = 0 ; i < n ; ++i)
    {
        Data x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

Array* array_create_read_size(std::istream& input)
{
    size_t n;
    input >> n;
    return array_create(n);
}


bool is_prime(int n)
{
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
            return false;
    return true;
}

/*Read an integer from a file, create an array of this size. 
Fill the array with prime numbers, starting with 2. Display the array on the screen.*/
void task1(Array *arr) 
{
    array_set(arr, 0, 2);
    int num = 3;
    for (size_t i = 1; i < array_size(arr); )
    {
        if (is_prime(num))
        {
            array_set(arr, i, num);
            ++i;
        }
        ++num;
    }


    for (size_t i = 0; i < array_size(arr); ++i)
    {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << "\n";

}

/*Read an integer from a file, create an array of this size and 
fill it with numbers from the file. Find five neighboring elements, 
the sum of whose values is maximum. Display the result on the screen.*/
void task2(Array *arr)
{
    size_t n = array_size(arr);
    if (n < 5)
    {
        return;
    }

    int maxSum = 0;
    int currSum = 0;
    size_t indx = 0;

    for (size_t i = 0; i < 5; ++i)
        currSum += array_get(arr, i);
    maxSum = currSum;

    for (size_t i = 5; i < n; ++i)
    {
        currSum = currSum - array_get(arr, i - 5) + array_get(arr, i);
        if (currSum > maxSum)
        {
            maxSum = currSum;
            indx = i - 4;
        }
    }

    for (size_t i = indx; i < indx + 5; ++i)
    {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << "\n";
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input)
    {
        return 1;
    }

    Array* arr = array_create_read_size(input);
    task1(arr);
    array_delete(arr);

    input.seekg(0); // to set the read pointer to the beginning of the file
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    return 0;
}
