#include <cstdio>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "array.h"

Array* array_create_and_read(FILE* input);
void process_grades(const Array* arr);
void find_elements_occuring_twice(const Array* arr);

int main(__attribute__((unused)) int argc, char** argv)
{
    Array* arr = NULL;
    FILE* input = fopen(argv[1], "r");
    arr = array_create_and_read(input);
    process_grades(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    find_elements_occuring_twice(arr);
    array_delete(arr);

    fclose(input);
    return 0;       
}

Array* array_create_and_read(FILE* input)
{
    int n;
    if (fscanf(input, "%d", &n) < 1) throw std::invalid_argument("Failed to read size");
    /* Create array */
    Array* arr = array_create(n);
    /* Read array data */
    for (int i = 0; i < n; ++i)
    {
        int x;
        if (fscanf(input, "%d", &x) < 1) throw std::invalid_argument("Failed to read number");
        array_set(arr, i, x);
    }

    return arr;
}

void process_grades(const Array* arr)
{
    int fives = 0, fours = 0, threes = 0, twos = 0;
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; ++i)
    {
        int val = array_get(arr, i);
        if (val == 5) fives++;
        else if (val == 4) fours++;
        else if (val == 3) threes++;
        else if (val == 2) twos++;
    }
    printf("Количество пятерок: %d\n", fives);
    printf("Количество четверок: %d\n", fours);
    printf("Количество троек: %d\n", threes);
    printf("Количество двоек: %d\n", twos);
}

void find_elements_occuring_twice(const Array* arr)
{
    size_t size = array_size(arr);
    Array* printed = array_create(size);
    size_t printed_count = 0;

    for (size_t index{ 0 }; index < size; ++index) {
        int currentValue = (int)array_get(arr, index);
        int count = 0;


        for (size_t index1{ 0 }; index1 < size; ++index1) {
            if (array_get(arr, index1) == currentValue) {
                count++;
            }
        }


        if (count == 2) {

            bool already_printed = false;
            for (size_t j = 0; j < printed_count; ++j) {
                if (array_get(printed, j) == currentValue) {
                    already_printed = true;
                    break;
                }
            }


            if (!already_printed) {
                printf("%d\n", currentValue);
                array_set(printed, printed_count++, currentValue);
            }
        }
    }

    array_delete(printed);          
}
