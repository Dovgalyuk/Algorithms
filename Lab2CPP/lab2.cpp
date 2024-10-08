#include <iostream>
#include <fstream>
#include "stack.h"
#include <string>
using namespace std;

void imul(Stack* stack) {
    int mul = 1;
    int element = 0;
    int i = 0;
    for (; i != 2; i++) {
        if (stack_empty(stack) == true)
            break;
        element = stack_get(stack);
        mul *= element;
        stack_pop(stack);
    }
    for (int j = 0; j != i; j++)
        stack_push(stack, 0);
    stack_push(stack, mul);
}

void iadd(Stack* stack) {
    int slo = 0;
    int element = 0;
    int i = 0;
    for (; i != 2; i++) {
        if (stack_empty(stack) == true)
            break;
        element = stack_get(stack);
        slo += element;
        stack_pop(stack);
    }
    for (int j = 0; j != i; j++)
        stack_push(stack, 0);
    stack_push(stack, slo);
}

void isub(Stack* stack) {
    int vich = 0;
    int element = 0;
    int i = 0;
    for (; i != 2; i++) {
        if (stack_empty(stack) == true)
            break;
        element = stack_get(stack);
        vich -= element;
        stack_pop(stack);
    }
    for (int j = 0; j != i; j++)
        stack_push(stack, 0);
    stack_push(stack, vich);
}

void ist(Stack* stack, int ind, int si) {
    int is0 = 0;
    int is1 = 0;
    int is2 = 0;
    int znach = stack_get(stack);
    for (int i = 0; i < si - ind; i++) {
        switch (i) {
        case 0:
            is0 = stack_get(stack);
            break;
        case 1:
            is1 = stack_get(stack);
            break;
        case 2:
            is2 = stack_get(stack);
            break;
        case 3:
            is0 = stack_get(stack);
            break;
        }
        stack_pop(stack);
    }
    stack_push(stack, znach);
    for (int i = si - ind - 2; i > 0; i--) {
        switch (i) {
        case 0:
            stack_push(stack, is0);
            break;
        case 1:
            stack_push(stack, is1);
            break;
        case 2:
            stack_push(stack, is2);
            break;
        case 3:

            break;
        }
    }
    stack_push(stack, 0);
}

void swap(Stack* stack) {
    int pz = stack_get(stack);
    int vz = 0;
    stack_pop(stack);
    vz = stack_get(stack);
    stack_pop(stack);
    stack_push(stack, pz);
    stack_push(stack, vz);
}

bool iand(Stack* stack) {
    int pz = stack_get(stack);
    stack_pop(stack);
    int vz = stack_get(stack);
    stack_push(stack, pz);
    if (pz >= 1 && vz >= 1) {
        stack_push(stack, 1);
        return true;
    }
    else {
        stack_push(stack, 0);
        return false;
    }
}

bool ior(Stack* stack) {
    int pz = stack_get(stack);
    stack_pop(stack);
    int vz = stack_get(stack);
    stack_push(stack, pz);
    if (pz >= 1 || vz >= 1) {
        stack_push(stack, 1);
        return true;
    }
    else {
        stack_push(stack, 0);
        return false;
    }
}

bool ixor(Stack* stack) {
    int pz = stack_get(stack);
    stack_pop(stack);
    int vz = stack_get(stack);
    stack_push(stack, pz);
    if ((pz == 0 && vz >= 1) || (pz >= 1 && vz == 0)) {
        stack_push(stack, 1);
        return true;
    }
    else {
        stack_push(stack, 0);
        return false;
    }
}

void ilo(Stack* stack, int ind, int si) {
    int is0 = 0;
    int is1 = 0;
    int is2 = 0;
    for (int i = 0; i < si-1 - ind; i++) {
        switch (i) {
        case 0:
            is0 = stack_get(stack);
            break;
        case 1:
            is1 = stack_get(stack);
            break;
        case 2:
            is2 = stack_get(stack);
            break;
        case 3:
            is0 = stack_get(stack);
            break;
        }
        stack_pop(stack);
        
    }
    int czn = stack_get(stack);
    for (int i = si - 1 - ind; i > 0; i--) {
        switch (i) {
        case 0:
            stack_push(stack,is2);
            break;
        case 1:
            stack_push(stack, is0);
            break;
        case 2:
            stack_push(stack, is1);
            break;
        case 3:

            break;
        }
    }
    stack_push(stack, czn);
}

void oper(Stack*& st, std::ifstream& v) {
    string o;
    int arr[] = { 0,0,0,0 };
    int ili = 0;
    while (v >> o) {   
        if (o == "bipush") {
            int n;
            v >> n;
            ili++;
            stack_push(st, n);
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
            ilo(st, preobr, ili);
        }
        if (o == "istore_0" || o == "istore_1" || o == "istore_2" || o == "istore_3") {
            char z = o[o.size() - 1];  
            int preobr = z - '0';
            ist(st, preobr,ili);
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