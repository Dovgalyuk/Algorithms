#include <iostream>
#include "str.h"
#include <string>

using namespace std;

int main() 
{
    // Получение входных данных от пользователя
    string inputString, searchString;
    cout << "Enter the main string: ";
    getline(cin, inputString);
    cout << "Enter the string to find: ";
    getline(cin, searchString);

    // Создание объекта класса String
    String myString(inputString.c_str(), inputString.length());

    // Использование функции findString
    int position = myString.findString(String(searchString.c_str(), searchString.length()));

    // Вывод результата
    if (position != String::NULL_POS) 
    {
        cout << "Substring found at position " << position << endl;
    }
    else 
    {
        cout << "Substring not found." << endl;
    }
    return 0;
}
