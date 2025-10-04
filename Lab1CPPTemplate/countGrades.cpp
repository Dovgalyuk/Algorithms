#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

template <typename T>
Array<T> getArrayFromFile(const char* filename) 
{
    ifstream f(filename);

    size_t n;
    f >> n;
    if (n == 0) 
        throw runtime_error("Размер массива должен быть > 0");

    Array<T> arr(n);
    for (size_t i = 0; i < n; ++i) 
    {
        T val;
        if (!(f >> val)) 
            throw runtime_error("Недостаточно данных в файле");
        arr.set(i, val);
    }

    return arr;
}

void countGrades(const Array<int>& arr) 
{
    int twos = 0; 
    int threes = 0; 
    int fours = 0; 
    int fives = 0;

    for (size_t i = 0; i < arr.size(); ++i) 
    {
        int grade = arr.get(i);
        switch (grade) 
        {
            case 2: twos++; break;
            case 3: threes++; break;
            case 4: fours++; break;
            case 5: fives++; break;
            default: break;
        }
    }

    cout << "Количество 2: " << twos << endl;
    cout << "Количество 3: " << threes << endl;
    cout << "Количество 4: " << fours << endl;
    cout << "Количество 5: " << fives << endl;
}

int main(int argc, char* argv[]) 
{
    if (argc < 2)
    {
        cerr << "Недостаточно агрументов" << endl;
        return 1;
    }

    auto arr = getArrayFromFile<int>(argv[1]);

    countGrades(arr);

    return 0;
}
