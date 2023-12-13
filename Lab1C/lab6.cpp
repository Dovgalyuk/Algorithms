#include <iostream>
#include "str.h"
#include <string>

using namespace std;

int main() 
{
    // ��������� ������� ������ �� ������������
    string inputString, searchString;
    cout << "Enter the main string: ";
    getline(cin, inputString);
    cout << "Enter the string to find: ";
    getline(cin, searchString);

    // �������� ������� ������ String
    String myString(inputString.c_str(), inputString.length());

    // ������������� ������� findString
    int position = myString.findString(String(searchString.c_str(), searchString.length()));

    // ����� ����������
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
