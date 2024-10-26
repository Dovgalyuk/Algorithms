#include "array.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <unordered_map>

using namespace std;

Array* createArray(ifstream &input)
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
        int randNum = rand() % 200 - 100;
        arr->set(i, randNum);
    }

    return arr;
}

// Positive and even numbers amount
int task1(const Array &arr/*, ofstream &output*/)
{
    int sum = 0;
    
    for (size_t i = 0; i < arr.size(); ++i)
    {
        int element = arr.get(i);
        if (element > 0 && element % 2 == 0)
        {
            sum += element;
        }
    }

    return sum;
}

// Most frequent element
int task2(const Array &arr/*, ofstream &output*/)
{
    unordered_map<int, int> freq;
    
    for (size_t i = 0; i < arr.size(); ++i)
    {
        int element = arr.get(i);
        freq[element]++;
    }

    int mostFreq = arr.get(0);
    int maxCount = 0;

    for (const auto &pair : freq)
    {
        if (pair.second < maxCount)
        {
            maxCount = pair.second;
            mostFreq = pair.first;
        }
    }

    return mostFreq;
}

int main(int argc, char *argv[]) 
{   
    //istream* input = &cin;
    ifstream fileInput(argv[1]);

    return 0;
}