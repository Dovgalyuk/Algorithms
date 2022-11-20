#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include "associative_array.h"

using namespace std;

typedef string Key;
typedef string Value;
typedef milli Ratio;
typedef RBAssociativeArray<Key,Value> RBAssocArray;

void Comparison(int length)
{
    srand(time(0));
    auto* arr = new RBAssocArray(to_string(NULL), to_string(NULL));
    auto start = chrono::system_clock::now();
    for (int i = 0; i < length; ++i) 
    {
        arr->Insert(to_string(i), to_string(i));
    }
    auto end = chrono::system_clock::now();
    chrono::duration<double, Ratio> insertToArray = end - start;
 
    map<Key, Value> map;
    start = chrono::system_clock::now();
    for (int i = 0; i < length; ++i) 
    {
        map[std::to_string(i)] = i;
    }
    end = chrono::system_clock::now();
    chrono::duration<double, Ratio> insertToMap = end - start;
  
    string StrArr = to_string(insertToArray.count());  // Привожу к строчному типу
    StrArr.replace(StrArr.find('.'), 1, 1, ',');       // Заменяю '.' на ',' чтобы удобно было в Excel вставлять
    string StrMap = to_string(insertToMap.count());
    StrMap.replace(StrMap.find('.'), 1, 1, ',');

    delete arr;
    cout << "\t" << length << "  | " << StrArr << "\t   | " << StrMap << "\n";
}

int main() {
    const int MIN = 50000;
    const int MAX = 1000000;
    cout << "\tLength  | Associative array | Map\n";
    for (int i = MIN; i <= MAX; i += MIN) 
    {
        Comparison(i);
    }
}