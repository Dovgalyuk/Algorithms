// lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <stdio.h>
#include <iostream>
#include "stack.h"
#include <string>
using namespace std;
int main()
{
    Stack* a;
    a = stack_create(NULL);
    string z;
    int b0=0, b1=0, b2=0, b3=0,buf;
  

    z = "bipush 1";
    if (z.find(' ')) {
        stoi(z.substr(z.find(' ') + 1));
        int* p = (int*)malloc(sizeof(int));
        *p = stoi(z.substr(z.find(' ') + 1));
   
        
        stack_push(a, p);
      }
    z = "bipush 2";
    if (z.find(' ')) {
        stoi(z.substr(z.find(' ') + 1));
        int* p = (int*)malloc(sizeof(int));
        *p = stoi(z.substr(z.find(' ') + 1));


        stack_push(a, p);
    }
    z = "bipush 3";
    if (z.find(' ')) {
        stoi(z.substr(z.find(' ') + 1));
        int* p = (int*)malloc(sizeof(int));
        *p = stoi(z.substr(z.find(' ') + 1));


        stack_push(a, p);
    }
    for (int i = 0; i < 2; i++)
    {

        cin >> z;
        if (z == "pop")
            stack_pop(a);
        if (z == "imul")
        {
            buf = *(int*)stack_get(a);
            stack_pop(a);
            buf = *(int*)stack_get(a) * buf;
            stack_pop(a);
            int* p = (int*)malloc(sizeof(int));
            *p = buf;
            stack_push(a, p);
        }
        if (z == "iand")
        {
            buf = *(int*)stack_get(a);
            stack_pop(a);
            buf = *(int*)stack_get(a) & buf;
            stack_pop(a);
            int* p = (int*)malloc(sizeof(int));
            *p = buf;
            stack_push(a, p);

        }
        if (z == "ior")
        {
            buf = *(int*)stack_get(a);
            stack_pop(a);
            buf = *(int*)stack_get(a) | buf;
            stack_pop(a);
            int* p = (int*)malloc(sizeof(int));
            *p = buf;
            stack_push(a, p);

        }
        if (z == "ixor")
        {
            buf = *(int*)stack_get(a);
            stack_pop(a);
            buf = *(int*)stack_get(a) ^ buf;
            stack_pop(a);
            int* p = (int*)malloc(sizeof(int));
            *p = buf;
            stack_push(a, p);

        }
        if (z == "iadd")
        {
            buf = *(int*)stack_get(a);
            stack_pop(a);
            buf = *(int*)stack_get(a) + buf;
            stack_pop(a);
            int* p = (int*)malloc(sizeof(int));
            *p = buf;
            stack_push(a, p);

        }
        if (z == "isub")
        {
            buf = *(int*)stack_get(a);
            stack_pop(a);
            buf = *(int*)stack_get(a) - buf;
            stack_pop(a);
            int* p = (int*)malloc(sizeof(int));
            *p = buf;
            stack_push(a, p);

        }
        if (z == "swap")
        {
            int buf1;

            buf = *(int*)stack_get(a);
            stack_pop(a);
            buf1 = *(int*)stack_get(a);
            stack_pop(a);
            int* p = (int*)malloc(sizeof(int));
            *p = buf;
            stack_push(a, p);
        
            *p = buf1;
            stack_push(a, p);

        }
        if (z == "iload_0")
        {

            int* p = (int*)malloc(sizeof(int));
            *p = b0;
            stack_push(a, p);

        }
        if (z == "iload_1")
        {

            int* p = (int*)malloc(sizeof(int));
            *p = b1;
            stack_push(a, p);

        }
        if (z == "iload_2")
        {

            int* p = (int*)malloc(sizeof(int));
            *p = b2;
            stack_push(a, p);

        }
        if (z == "iload_3")
        {

            int* p = (int*)malloc(sizeof(int));
            *p = b3;
            stack_push(a, p);

        }

        if (z == "istore_0")
        {
            b0 = *(int*)stack_get(a);
            stack_pop(a);

        }
        if (z == "istore_1")
        {

            b1 = *(int*)stack_get(a);
            stack_pop(a);
        }
        if (z == "istore_2")
        {

            b2 = *(int*)stack_get(a);
            stack_pop(a);
        }
        if (z == "istore_3")
        {

            b3 = *(int*)stack_get(a);
            stack_pop(a);
        }


    } 
    
    cout << "stack\n";
    cout << stack_size(a);
    cout << "\n";
    cout << "vars\n";
    
        cout << b0;
        cout << "\n";
        cout << b1;
        cout << "\n";
        cout << b2;
        cout << "\n";
        cout << b3;
        cout << "\n";

    


    }





