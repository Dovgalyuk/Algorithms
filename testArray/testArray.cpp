#include <iostream>
#include <ctime>
#include "array.h"

typedef Array<int> MyArray; //a(9);
int main() {

    MyArray *a = new MyArray(9);
    srand(time(nullptr));
    int CurrentCounter = 0, BiggestCounter = 0, FrequentEl = 0;
    //CurrentCounter - текущее число повторений
    //BiggestCounter - наибольшее число повторений
    //FrequentEl - наиболее часто встречающийся элемент


    for (int i = 0; i < a->size(); ++i)
    {
        a->set(i, rand()%10);
    }

    for(int i = 0; i < a->size(); i++)
    {
        for(int j = i; j < a->size(); j++)
        {
            if(a->get(i) == a->get(j))
            {
                CurrentCounter++;
            }
        }
        if(CurrentCounter > BiggestCounter)
        {
            BiggestCounter = CurrentCounter;
            FrequentEl = a->get(i);
        }
        CurrentCounter = 0;
    }
    std::cout << FrequentEl;

    return 0;
};