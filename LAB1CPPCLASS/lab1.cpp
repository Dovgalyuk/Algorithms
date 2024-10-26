#include "array.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

Array* createArray(ifstream& input)
{
    size_t num;
    input >> num;

    Array* arr = new Array(num);

    for (size_t i = 0; i < num; ++i)
    {
        int tmp;
        input >> tmp;
        arr->set(i, tmp);
    }

    return arr;
}

Array* fillArrayRandom(size_t num)
{
    Array* arr = new Array(num);

    for (size_t i = 0; i < num; ++i)
    {
        int randNum = rand() % 100 - 50;
        arr->set(i, randNum);
    }

    return arr;
}

void task1()
{

}

void task2()
{
    
}

int main(int argc, char *argv[]) 
{   
    

    return 0;
}