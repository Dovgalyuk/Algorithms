#include <iostream>
#include <unordered_map>
#include "array.h"

Array *array_create_and_read(FILE* input)
{
    int n;
    fscanf(input, "%d", &n);
    /* Create array */
    Array *arr = array_create(n);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        fscanf(input, "%d", &x);

        array_set(arr, i, x);
    }
    return arr;
}

std::pair<Array *, Array *> task1(Array *arr)
{
    Array *_arrNeg = array_create(array_size(arr));
    Array *_arrPos = array_create(array_size(arr));

    unsigned int cPos=0;
    unsigned int cNeg=0;

    for (size_t i = 0; i < array_size(arr); i++) {
        if (array_get(arr, i) > 0) {
            array_set(_arrPos,cPos, array_get(arr, i));
            cPos++;
        }else
            if (array_get(arr,i) < 0) {
                array_set(_arrNeg,cNeg, array_get(arr, i));
                cNeg++;
            }
    }

    Array *arrNeg = array_create(cNeg);
    for (size_t i = 0; i < array_size(arrNeg); i++) {
        array_set(arrNeg, i, array_get(_arrNeg, i));
    }
    Array *arrPos = array_create(cPos);
    for (size_t i = 0; i < array_size(arrPos); i++) {
        array_set(arrPos, i, array_get(_arrPos, i));
    }

    std::cout << "Negative numbers: ";
    for (size_t i = 0; i < cNeg; i++) {
        std::cout << array_get(arrNeg, i) << " ";
    }
    std::cout << std::endl;

    std::cout << "Positive numbers: ";
    for (size_t i = 0; i < cPos; i++) {
        std::cout << array_get(arrPos, i) << " ";
    }
    return std::make_pair(arrNeg, arrPos);
}



Array *task2(Array *arr)
{
    std::unordered_map<int, int> countMap;

    for (size_t i=0;i<array_size(arr);i++) {
        countMap[array_get(arr,i)]++;
    }
    Array *_arrRep = array_create(countMap.size());
    unsigned int count = 0;
    bool found = false;
    std::cout << "\nSecond numbers: ";
    for (const auto& pair : countMap) {
        if (pair.second == 2) {
            std::cout << pair.first << " ";
            array_set(_arrRep, count, pair.first);
            found = true;
            count++;
        }
    }
    Array *arrRep = array_create(count);
    for (size_t i = 0; i < array_size(arrRep); i++) {
        array_set(arrRep, i, array_get(_arrRep, i));
    }

    if (!found) {
        std::cout << "Нет таких элементов." << std::endl;
    }
    return arrRep;
}

bool testTask1(FILE* output,Array *arrNeg, Array *arrPos) {
    for(size_t i=0; i<array_size(arrNeg); i++) {
        int x;
        fscanf(output, "%d", &x);
        if(array_get(arrNeg,i) != x) {
            return false;
        }
    }
    for(size_t i=0; i<array_size(arrPos); i++) {
        int x;
        fscanf(output, "%d", &x);
        if(array_get(arrPos,i) != x) {
            return false;
        }
    }
    return true;
}
bool testTask2(FILE *output, Array *arrRep) {
    for(size_t i=0; i<array_size(arrRep); i++) {
        int x;
        fscanf(output, "%d", &x);
        if(array_get(arrRep,i) != x) {
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv)
{
    Array *arr;
    FILE *input=fopen(argv[1],"r");
    FILE *output=fopen(argv[2],"r");
    if (!input) {
        std::cerr << "Error opening file!" << std::endl;
        return EXIT_FAILURE;
    }
    if (!output) {
        std::cerr << "Error opening file!" << std::endl;
        return EXIT_FAILURE;
    }
    arr = array_create_and_read(input);
    auto twoArray = task1(arr);
    Array *arrNeg = twoArray.first;
    Array *arrPos = twoArray.second;
    if(!testTask1(output, arrNeg, arrPos)) {
        return 1;
    }
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    Array *arrRep = task2(arr);
    if(!testTask2(output,arrRep)) {
        return 1;
    }
    array_delete(arr);
    fclose(input);
}
