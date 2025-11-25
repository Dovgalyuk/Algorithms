#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define STACK_ERROR -1

void dell(void* par) {
    free(par);
}

void print_error(int errCode) {
    if (errCode == STACK_ERROR)
        printf("Error when working with the stack");
}

bool adress_checking(Stack* stack) {
    char* address = (char*)stack_get(stack);
    if (strncmp(address, "address_", 8) == 0) return true;
    return false;
}

int* math_operation(const char* command, int a, int b) {
    int* res = malloc(sizeof(int));
    if (strcmp(command, "imul") == 0)
        *res = a * b;
    else if (strcmp(command, "iand") == 0)
        *res = a & b;
    else if (strcmp(command, "ior") == 0)
        *res = a | b;
    else if (strcmp(command, "ixor") == 0)
        *res = a ^ b;
    else if (strcmp(command, "iadd") == 0)
        *res = a + b;
    else if (strcmp(command, "isub") == 0)
        *res = a - b;
    else {
        free(res);
        return NULL;
    }
    return res;
}

bool command_interpretation(FILE* f, Stack* stack, int* vars) {
    char command[21];
    for (int i = 0; fscanf(f, "%20s", command) == 1; i++) {
        if(command[0] == 'i') {
            if (strstr(command, "iload") != NULL) {
                size_t n = command[strlen(command) - 1] - '0';
                int* copy = malloc(sizeof(int));
                *copy = vars[n];
                stack_push(stack, copy);
                continue;
            }

            else if(strstr(command, "istore") != NULL) {
                if (!adress_checking(stack) && !stack_empty(stack)) {
                    size_t n = command[strlen(command) - 1] - '0';
                    int* temp = stack_get(stack);
                    vars[n] = *temp;
                    stack_pop(stack);
                }
                else
                    return false;
                continue;
            }

            else {
                if (!adress_checking(stack)) {
                    Data temp = stack_get(stack);
                    stack_pop(stack);
                    if (!stack_empty(stack)) {
                        bool second_is_address = adress_checking(stack);
                        stack_push(stack, temp);  

                        if (!second_is_address) {
                            int* a = stack_get(stack);
                            stack_pop(stack);
                            int* b = stack_get(stack);
                            stack_pop(stack);
                            Data res = math_operation(command, a, b);
                            stack_push(stack, res);
                        } else {
                            return false;
                        }
                    }
                }
                else 
                    return false;
                
                continue;
            }
        }

        else if (strcmp(command, "bipush") == 0) {
            int n;
            fscanf(f, "%d", &n);
            int* num = malloc(sizeof(int));
            *num = n;
            stack_push(stack, num);
            continue;
        }
        
        else if (strcmp(command, "pop") == 0) {
            if (!adress_checking(stack) && !stack_empty(stack)) 
                stack_pop(stack);
            else
                return false; 
            continue;
        }

        else if (strcmp(command, "swap") == 0) {
            if(!stack_empty(stack)) {
                Data first = stack_get(stack);
                stack_pop(stack);
                Data second = stack_get(stack);
                stack_pop(stack);
                stack_push(stack, second);
                stack_push(stack, first);
            }
            else
                return false;
            continue;
        }

        else if (strcmp(command, "invokestatic") == 0) {
            char id_str[20];
            snprintf(id_str, sizeof(id_str), "%d", i);

            char* address = (char*)malloc(strlen("address_") + strlen(id_str) + 1);

            strcpy(address, "address_");
            strcat(address, id_str);
            stack_push(stack, address);
            continue;
        }

        else if (strcmp(command, "return") == 0) {
            if(adress_checking(stack)) {
                stack_pop(stack);
            }
            else {
                return false;
            }
            continue;
        }
    }
    return true;
}

int main(int argc, char** argv) {

    FILE* program = fopen(argv[1], "r");
    Stack* stack = stack_create(dell);
    int* vars = (int*)calloc(4, sizeof(int));
    
    if(command_interpretation(program, stack, vars)){
        printf("stack:\n");
        while (!stack_empty(stack)){
            Data element = stack_get(stack);
            if (adress_checking(element)) {
                printf("%s\n", (char*)element);
            } else {
                printf("%d\n", *((int*)element));
            }
            stack_pop(stack);  
        }
        printf("vars:\n");
        for (int i = 0; i < 4; i++) {
            printf("%d\n", vars[i]);
        }
    }

    free(vars);
    stack_delete(stack);
    fclose(program);
    return 0;
}