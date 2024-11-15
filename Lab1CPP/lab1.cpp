#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;
Array *array_create_and_read(ifstream &input)
{
    int n;
    input>>n;
    /* Create array */
    Array *arr = new Array(n);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        input >> x;
        arr->set(i, x);
    }
    return arr;
}

void task1(Array *arr)
{

}

void task2(Array *arr)
{
    
}

int main(int argc, char **argv)
{
    Array *arr = NULL;
    ifstream input(argv[1]);
    arr = array_create_and_read(input);
    task1(arr);
    delete arr;
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    delete arr;
    input.close();
}
