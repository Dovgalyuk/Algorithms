#include "stack.h"
#include "list.h"
#include <stdlib.h>
struct Stack
{
    List* l = nullptr;
};

Stack *stack_create()
{
    Stack* stack  = new Stack;
    stack->l = list_create();
    return stack;
}

void stack_delete(Stack *stack)
{
    list_delete(stack->l);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    list_insert(stack->l,data);
}

Data stack_get(const Stack *stack)
{
    return list_item_data(list_first(stack->l));
}

void stack_pop(Stack *stack)
{
    list_erase_first(stack->l);
}

bool stack_empty(const Stack *stack)
{
    if (list_first(stack->l) == nullptr) {
        return true;
    }
    else return false;
    
}

void imul(Stack* stack) {
    int mul = 1;
    int element = 0;
    int i = 0;
    for(; i!=2; i++) {
        if (stack_empty(stack) == true)
            break;
        element = stack_get(stack);
        mul *= element;
        stack_pop(stack);
    }
    for (int j = 0; j != i; j++)
        stack_push(stack, 0);
    stack_push(stack,mul);
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
    for (int i = si-ind-2; i > 0; i--) {
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
    stack_push(stack,pz);
    stack_push(stack,vz);
}

bool iand(Stack* stack) {
    int pz = stack_get(stack);
    stack_pop(stack);
    int vz = stack_get(stack);
    stack_push(stack,pz);
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