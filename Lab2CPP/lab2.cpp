#include <iostream>
#include <fstream>
#include "stack.h"
#include <string>
using namespace std;

void oper(Stack*& st, std::ifstream& v) {
    string o;
    int il0 = 0;
    int il1 = 0;
    int il2 = 0;
    int il3 = 0;
    int ili = 0;
    while (v >> o) {
        
        if (o == "bipush") {
            int n;
            v >> n;
            switch (ili) {
            case 0:
                il0 = n;
                break;
            case 1:
                il1 = n;
                break;
            case 2:
                il2 = n;
                break;
            case 3:
                il3 = n;
                break;
            }
            stack_push(st, n);
            ili++;
        }
        if (o == "pop") {
            stack_pop(st);
            ili--;
        }
        if (o == "imul") {
            imul(st);
            ili++;
        }
        if (o == "iadd") {
            iadd(st);
            ili++;
        }
        if (o == "isub") {
            isub(st);
            ili++;
        }
        
        if (o == "iload_0" || o == "iload_1" || o == "iload_2" || o == "iload_3") {
            char z = o[o.size()-1];
            int preobr = z - '0';
            switch (preobr) {
            case 0:
                stack_push(st, il0);
                break;
            case 1:
                stack_push(st, il1);
                break;
            case 2:
                stack_push(st, il2);
                break;
            case 3:
                stack_push(st, il3);
                break;
            }
            ili++;
        }
        if (o == "istore_0" || o == "istore_1" || o == "istore_2" || o == "istore_3") {
            char z = o[o.size() - 1];  
            int preobr = z - '0';
            switch (preobr) {
            case 0:
                
                ist(st, 0, ili);
                break;
            case 1:
                ist(st, 1, ili);
                break;
            case 2:
                ist(st, 2, ili);
                break;
            case 3:
                ist(st, 3, ili);
                break;
            }
        }
        if(o == "swap") {
            swap(st);
        }
        if (o == "iand") {
            iand(st);
        }
        if (o == "ior") {
            ior(st);
        }
        if (o == "ixor") {
            ixor(st);
        }
    }
}

void vivod_stack(Stack* st) {
    Stack* stviv = stack_create();
    while (true) {
        if (stack_empty(st) == true)
            break;
        stack_push(stviv, stack_get(st));
        stack_pop(st);
    }
    cout << "stack \n1 \nvars:\n" << endl;
    while (true) {
        if (stack_empty(stviv) == true)
            break;
        cout << stack_get(stviv) << endl;
        stack_pop(stviv);
    }
}

int main()
{
    std::ifstream v("input.txt");  
    if (v.is_open()) {            
        Stack* st = stack_create();     
        oper(st, v);
        vivod_stack(st);
        stack_delete(st);
        cin.get();
    }
}