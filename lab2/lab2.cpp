#include <iostream>
#include <string>
#include "stack.h"
#include "list.h"

#define size 3

using namespace std;

void reverse(string &s)
{
    Stack* stack = stack_create();
    for (int i = 0; i < s.length(); i++)
        stack_push(stack, s[i]);
        for (int i = 0; i < s.length(); i++)
        {
          s[i] = stack_get(stack);
          stack_pop(stack);
        }
        stack_delete(stack);
}

int main()
{
    setlocale(LC_ALL, "ru");
    string a[size];
    cout << "Входные данные" << endl;
    for (int i = 0; i < size; i++)
    {
        getline(cin, a[i]);
        reverse(a[i]);
    }
    cout << "Выходные данные" << endl;
    for (int i = 0; i < size; i++)
        cout << a[i] << endl;
    
}
        
            
           
    
   
     

