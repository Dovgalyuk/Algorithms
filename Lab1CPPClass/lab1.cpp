#include <iostream>
#include "array.h"
#include <fstream> // для работы с файлами
#include <string> // для работы с std::string
#include <unordered_map>

Array* createArray(std::ifstream& inputFile)
{
    int number;
    inputFile >> number;

    auto* arr = new Array(number);

    int tmp;

    for (int i = 0; i < number; ++i) {
        inputFile >> tmp;
        arr->set(i, tmp);
    }
    return arr;

}

void printArray(const Array* array)
{
    const size_t size = array->size();
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << array->get(i) << " ";
    }
    std::cout << std::endl;
}

void task1(std::ifstream& inputFile)
{
    const Array* array = createArray(inputFile);
    const size_t size = array->size();
    int numsSumMoreThen = 0;
    int numsSumLowerThen = 0;

    for (size_t i = 0; i < size; ++i)
    {
        if(array->get(i) > 20){
            numsSumMoreThen += array->get(i);
        }
        if(array->get(i) < 50){
            numsSumLowerThen += array->get(i);
        }
    }

    delete array;

    std::string firstOut = (numsSumMoreThen > 100) ? "true" : "false" ;
    std::cout << firstOut << std::endl;
    std::string secondOut = (numsSumLowerThen % 2 == 0) ? "true" : "false";
    std::cout << secondOut << std::endl;

}



void task2(std::ifstream& inputFile)
{
    const Array* array = createArray(inputFile);
    const size_t size = array->size();
    std::unordered_map<int, int> numsFrequency;

    for (size_t i = 0; i < size; ++i)
    {
        int item = array->get(i);
        if (numsFrequency.find(item) != numsFrequency.end()) {
            numsFrequency[item]++;
        }else{
            numsFrequency[item] = 1;
        }
    }

    int freqNumber = 0;
    int tmp = 0;

    for (const auto &pair : numsFrequency) {
        if(pair.second > tmp)
        {
            tmp = pair.second;
            freqNumber = pair.first;
        }
    }

    delete array;
    std::cout << freqNumber << std::endl;

}


int main(int argc, char **argv) {

    std::ifstream file(argv[1]);


    task1(file);
    task2(file);

    file.close();
    return 0;
}

