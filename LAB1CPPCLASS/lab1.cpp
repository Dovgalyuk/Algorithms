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

Array* arrayRandom(size_t num)
{
    Array* arr = new Array(num);

    for (size_t i = 0; i < num; ++i)
    {
        int randNum = rand() % 200 - 100;
        arr->set(i, randNum);
    }

    return arr;
}

void printArray(Array* arrN, ostream* output)
{
    for (size_t i = 0; i < arrN->size(); ++i) 
    {
        *output << arrN->get(i) << " ";
    }
        *output << endl;
}

// Positive and even numbers amount
int task1(const Array &arr)
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
int task2(const Array &arr)
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
        if (pair.second > maxCount)
        {
            maxCount = pair.second;
            mostFreq = pair.first;
        }
    }

    return mostFreq;
}

int main(int argc, char *argv[]) 
{   
    istream* input = &cin;
    ifstream fileInput;
    ostream* output = &cout;
    ofstream fileOutput;

    if (argc == 3)
    {
        fileInput.open(argv[1]);
        fileOutput.open(argv[2]);

        if (!fileInput)
        {
            cerr << "Error! Opening input file is failed!" << endl;
            return 1;
        }
        if (!fileOutput)
        {
            cerr << "Error! Opening output file is failed!" << endl;
            return 1;
        }

        input = &fileInput;
        output = &fileOutput;
    }

    size_t sizeF, sizeS;

    // task 1
    *output << "Task 1: The sum of positive and even numbers\n";
    cout << "Array size: ";
    *input >> sizeF;

    Array* arrF = arrayRandom(sizeF);

    *output << "Original array: ";
    printArray(arrF, output);

    int pena = task1(*arrF);
    *output << "Amount of positive and even: " << pena;
    *output << endl;

    delete arrF;

    // task 2
    *output << "Task 2: Most frequent element\n";
    cout << "Array size: ";
    *input >> sizeS;

    Array* arrS = arrayRandom(sizeS);

    *output << "Original array: ";
    printArray(arrS, output);

    int mfe = task2(*arrS);
    *output << "Most frequent element: " << mfe;
    *output << endl;

    delete arrS;

    return 0;
}