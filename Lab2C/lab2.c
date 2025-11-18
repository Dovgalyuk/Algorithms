#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "array.h"

void dell(void* par) {
    free(par);
}

void interpretationCommand(FILE* f, Stack* stack, Array* vars) {
    for (char command[20]; fscanf(f, "%s", command);) {
        if (command == "bipush") {
            int n;
            fscanf(f, "%d", &n);
            Data data = &n;
            stack_push(stack, data);
            dell(data);
        }
        
        else if (command == "pop") {
            stack_pop(stack);
        }

        else if(command == "imul") {
            int* a = stack_get(stack);
            stack_pop(stack);
            int* b = stack_get(stack);
            stack_pop(stack);
            Data res = ((*a) * (*b));
            stack_push(stack, res);
        }

        else if (command == "iand") {
            int* a = stack_get(stack);
            stack_pop(stack);
            int* b = stack_get(stack);
            stack_pop(stack);
            Data res = ((*a) & (*b));
            stack_push(stack, res);
        }

        else if(command == "ior"){
             int* a = stack_get(stack);
            stack_pop(stack);
            int* b = stack_get(stack);
            stack_pop(stack);
            Data res = ((*a) | (*b));
            stack_push(stack, res);
        }

        else if (command == "ixor") {
            int* a = stack_get(stack);
            stack_pop(stack);
            int* b = stack_get(stack);
            stack_pop(stack);
            Data res = ((*a) ^ (*b));
            stack_push(stack, res);
        }

        else if(command == "iadd") {
            int* a = stack_get(stack);
            stack_pop(stack);
            int* b = stack_get(stack);
            stack_pop(stack);
            Data res = ((*a) + (*b));
            stack_push(stack, res);
        }

        else if(command == "isub"){
            int* a = stack_get(stack);
            stack_pop(stack);
            int* b = stack_get(stack);
            stack_pop(stack);
            Data res = ((*a) - (*b));
            stack_push(stack, res);
        }

        else if (command == "iload_0") {
            stack_push(stack, array_get(vars, 0));
        }
        else if (command == "iload_1") {
            stack_push(stack, array_get(vars, 1));
        }
        else if (command == "iload_2") {
            stack_push(stack, array_get(vars, 2));
        }
        else if (command == "iload_3") {
            stack_push(stack, array_get(vars, 3));
        }

        else if (command == "istore_0") {
            array_set(vars, 0, stack_get(stack));
            stack_pop(stack);
        }
        else if (command == "istore_1") {
            array_set(vars, 1, stack_get(stack));
            stack_pop(stack);
        }
        else if (command == "istore_2") {
            array_set(vars, 2, stack_get(stack));
            stack_pop(stack);
        }
        else if (command == "istore_3") {
            array_set(vars, 3, stack_get(stack));
            stack_pop(stack);
        }

        else if(command == "swap") {
            Data first = stack_get(stack);
            stack_pop(stack);
            Data second = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, second);
            stack_push(stack, first);
        }

    }
}

int main(int argc, char** argv) {

    FILE* program = fopen(argv[1], "r");
    Stack* stack = stack_create(dell);
    Array* vars = array_create(4, dell);
    


    array_delete(vars);
    stack_delete(stack);
    fclose(program);
    return 0;

}