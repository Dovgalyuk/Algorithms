#include <iostream>
#include <fstream>
#include <map>
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
        int val;
        if (!(f >> val)) 
            throw runtime_error("Недостаточно данных в файле");
        arr.set(i, val);
    }

    return arr;
}

void findElementsTwice(const Array<int>& arr) 
{
    map<int, int> freq;

    for (size_t i = 0; i < arr.size(); ++i)
        ++freq[arr.get(i)];

    cout << "Элементы, встречающиеся ровно дважды: ";
    bool found = false;

    for (const auto &p : freq) 
    {
        if (p.second == 2) 
        {
            cout << p.first << " ";
            found = true;
        }
    }

    if (!found) 
        cout << "нет";
}

int main(int argc, char* argv[]) 
{

    if (argc < 2)
    {
        cerr << "Недостаточно агрументов" << endl;
        return 1;
    }

    auto arr = getArrayFromFile<int>(argv[1]);

    findElementsTwice(arr);

    return 0;
}
