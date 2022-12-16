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
typedef RBAssociativeArray RBAssocArray;

void Comparison(int length)
{
    srand(time(0));
    auto* arr = new RBAssocArray(to_string(0), to_string(0));
    string *Strs = new string[length];
    for (int i = 0; i < length; ++i)
    {
        Strs[i] = to_string(i);
      
    }
    auto start = chrono::system_clock::now();
    for (int i = 0; i < length; ++i) 
    {
        arr->Insert(Strs[i], Strs[i]);
    }
    auto end = chrono::system_clock::now();
    chrono::duration<double, Ratio> insertToArray = end - start;
 
    map<Key, Value> map;
    start = chrono::system_clock::now();
    for (int i = 0; i < length; ++i) 
    {
        map[Strs[i]] = Strs[i];
    }
    end = chrono::system_clock::now();
    chrono::duration<double, Ratio> insertToMap = end - start;
  
    string StrArr = to_string(insertToArray.count());  // Привожу к строчному типу
    StrArr.replace(StrArr.find('.'), 1, 1, ',');       // Заменяю '.' на ',' чтобы удобно было в Excel вставлять
    string StrMap = to_string(insertToMap.count());
    StrMap.replace(StrMap.find('.'), 1, 1, ',');

    delete arr;  delete[] Strs;
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
