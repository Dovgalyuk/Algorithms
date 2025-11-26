#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include <locale.h>

#define STACK_ERROR -1

// Function to free pointers on delete
void dell(void* data) {
    free(data);
}

// Error printing
void print_error(int errCode) {
    if (errCode == STACK_ERROR)
        printf("Error when working with the stack");
}

// Is the element an address?
bool adress_checking(Data element) {
    if (element == NULL) 
        return false;

    if (strstr((char*)element, "address_") != 0)
        return true;
    else 
        return false;
}

// Stack output to terminal
void print_stack(Stack* stack) {
    printf("stack:\n");
    while (!stack_empty(stack)) {
        Data top = stack_get(stack);
        if (adress_checking(top)) {
            printf("%s\n", (char*)top);
        } else {
            int* raw = (int*)top;
            printf("%d\n", *raw);
        }

        stack_pop(stack);
    }

}

// Performing mathematical operations
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

// Command processing
bool command_interpretation(FILE* f, Stack* stack, int* vars) {

    // Command buffer
    char command[21];

    for (int i = 0; fscanf(f, "%20s", command) == 1; i++) {
        // Commands, starting with i
        if(command[0] == 'i') {
            // "iload" commands processing
            if (strstr(command, "iload") != NULL) {
                // Variable number
                size_t n = command[strlen(command) - 1] - '0';

                // Adding n-th variable to stack
                int* copy = malloc(sizeof(int));
                *copy = vars[n];
                stack_push(stack, copy);
                continue;
            }

            // "istore" commands processing
            else if(strstr(command, "istore") != NULL) {
                if (!adress_checking(stack_get(stack)) && !stack_empty(stack)) {
                    // Variable number
                    size_t n = command[strlen(command) - 1] - '0';

                    // Adding top of stack to n-th variable
                    int* temp = stack_get(stack);
                    vars[n] = *temp;
                    stack_pop(stack);
                }
                else
                    return false;
                continue;
            }

            // Adding a return address
            else if (strcmp(command, "invokestatic") == 0) {
                // Operation number
                char id_str[20];
                snprintf(id_str, sizeof(id_str), "%d", i);

                // Address generation
                char* address = (char*)malloc(strlen("address_") + strlen(id_str) + 1);
                strcpy(address, "address_");
                strcat(address, id_str);
                stack_push(stack, address);
                continue;
            }

            // Math operations
            else {
                // ============= Сhecking for address and emptiness =============
                if (!adress_checking(stack_get(stack))) {
                    int* temp = malloc(sizeof(int));
                    *temp = *((int*)stack_get(stack));
                    stack_pop(stack);
                    if (!stack_empty(stack)) {
                        bool second_is_address = adress_checking(stack);
                        stack_push(stack, temp);  
                        if (!second_is_address) {
                // ==============================================================

                            // Performing the operation
                            int* a = (int*)malloc(sizeof(int));
                            *a = *((int*)stack_get(stack));
                            stack_pop(stack);
                            int* b = (int*)malloc(sizeof(int));
                            *b = *((int*)stack_get(stack));
                            stack_pop(stack);
                            int* res = math_operation(command, *a, *b);
                            stack_push(stack, res);
                            free(a); 
                            free(b);
                        } else {
                            return false;
                        }
                    }
                    else 
                        return false;
                }
                else 
                    return false;
                
                continue;
            }
            
        }

        // Adding number to stack
        else if (strcmp(command, "bipush") == 0) {
            int n;
            fscanf(f, "%d", &n);
            int* num = (int*)malloc(sizeof(int));
            *num = n;
            stack_push(stack, num);
            continue;
        }
        
        // Removing number from stack
        else if (strcmp(command, "pop") == 0) {
            if (!adress_checking(stack_get(stack)) && !stack_empty(stack)) 
                stack_pop(stack);
            else
                return false; 
            continue;
        }

        // Swapping places
        else if (strcmp(command, "swap") == 0) {
            if(!stack_empty(stack)) {
                
                // Making copies
                int* first = malloc(sizeof(int));
                *first = *((int*)stack_get(stack));
                stack_pop(stack);
                int* second = malloc(sizeof(int));
                *second = *((int*)stack_get(stack));
                stack_pop(stack);

                stack_push(stack, first);
                stack_push(stack, second);
            }
            else
                return false;
            continue;
        }

        // Return from function
        else if (strcmp(command, "return") == 0) {
            if(adress_checking(stack_get(stack))) {
                stack_pop(stack);
                return true;
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
    // Reading a file
    FILE* program = fopen(argv[1], "r");

    Stack* stack = stack_create(free);
    int* vars = (int*)calloc(4, sizeof(int));
    
    // Сommand processing and result output 
    if(command_interpretation(program, stack, vars)){
        print_stack(stack);
        printf("vars:\n");
        for (int i = 0; i < 4; i++) {
            printf("%d\n", vars[i]);
        }
    }
    else {
        print_error(STACK_ERROR);
    }

    // Releasing values
    free(vars);
    stack_delete(stack);
    fclose(program);
    return 0;
}
