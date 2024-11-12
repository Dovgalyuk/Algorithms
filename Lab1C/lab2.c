#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "stack.h"

#define REGISTERS 4

typedef struct {
    int registers[REGISTERS];
    Stack *stack;
} CPU;

void execute_instruction(CPU *cpu, const char *instruction) {
    char command[10];
    int value;

    // Обработка команды PUSH
    if (sscanf(instruction, "%s %d", command, &value) == 2) {
        if (strcmp(command, "PUSH") == 0) {
            stack_push(cpu->stack, (Data)(intptr_t)value);
            return;
        }
    } 
    // Обработка команды POP
    else {
        char reg_char;
        if (sscanf(instruction, "%s %c", command, &reg_char) == 2) {
            if (strcmp(command, "POP") == 0) {
                int reg = reg_char - 'A';
                if (reg < 0 || reg >= REGISTERS) {
                    fprintf(stderr, "Error: Invalid case %c\n", reg_char);
                    return;  
                }
                
                if (stack_empty(cpu->stack)) {
                    fprintf(stderr, "Error: Stack is empty, register cannot be POPed %c\n", reg_char);
                    return; 
                }
                
                cpu->registers[reg] = (int)(intptr_t)stack_pop(cpu->stack);
                return;
            }
        } 

        // Обработка других команд (например, PUSH из регистра)
        if (strcmp(command, "PUSH") == 0) {
            if (reg_char >= 'A' && reg_char < 'A' + REGISTERS) {
                int reg = reg_char - 'A';
                int reg_value = cpu->registers[reg];
                stack_push(cpu->stack, (Data)(intptr_t)reg_value);
                return;
            }
        }

        // Обработка ADD
        if (strcmp(command, "ADD") == 0) {
            int reg = reg_char - 'A';
            if (reg < 0 || reg >= REGISTERS) {
                fprintf(stderr, "Error: Invalid case %c\n", reg_char);
                return;
            }
            if (stack_empty(cpu->stack)) {
                fprintf(stderr, "Error: Stack is empty, ADD cannot be performed\n");
                return;
            }
            int a = (int)(intptr_t)stack_pop(cpu->stack);
            int b = (int)(intptr_t)stack_pop(cpu->stack);
            cpu->registers[reg] = a + b;
            return;
        }
        // Обработка SUB
        if (strcmp(command, "SUB") == 0) {
            int reg = reg_char - 'A';
            if (reg < 0 || reg >= REGISTERS) {
                fprintf(stderr, "Error: Invalid case %c\n", reg_char);
                return;
            }
            if (stack_empty(cpu->stack)) {
                fprintf(stderr, "Error: Stack is empty, SUB cannot be performed\n");
                return;
            }
            int a = (int)(intptr_t)stack_pop(cpu->stack);
            int b = (int)(intptr_t)stack_pop(cpu->stack);
            cpu->registers[reg] = a - b;
            return;
        }
        // Обработка MUL
        if (strcmp(command, "MUL") == 0) {
            int reg = reg_char - 'A';
            if (reg < 0 || reg >= REGISTERS) {
                fprintf(stderr, "Error: Invalid case %c\n", reg_char);
                return;
            }
            if (stack_empty(cpu->stack)) {
                fprintf(stderr, "Error: Stack is empty, MUL cannot be performed\n");
                return;
            }
            int a = (int)(intptr_t)stack_pop(cpu->stack);
            int b = (int)(intptr_t)stack_pop(cpu->stack);
            cpu->registers[reg] = a * b;
            return;
        }
    }
}

void print_registers(const CPU *cpu) {
    for (int i = 0; i < REGISTERS; i++) {
        printf("%c = %d\n", 'A' + i, cpu->registers[i]);
    }
}

int main(int argc, char **argv) {
    CPU cpu = {0};
    cpu.stack = stack_create(NULL);
    if (cpu.stack == NULL) {
        fprintf(stderr, "Stack creation error\n");
        return 0;
    }

    if (argc < 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        stack_delete(cpu.stack);
        return 0;
    }

    char instruction[50];

    while (fgets(instruction, sizeof(instruction), file)) {
        execute_instruction(&cpu, instruction);
    }

    fclose(file);
    print_registers(&cpu);
    stack_delete(cpu.stack);
    return 0;
}
