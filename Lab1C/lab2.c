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

// Функция для освобождения данных, хранящихся в стеке
void free_data(void *data) {
    free(data); // Освобождение памяти для данных
}

void execute_instruction(CPU *cpu, const char *instruction) {
    char command[10];
    char reg_char;
    int value;

    // Обработка команды PUSH
    if (sscanf(instruction, "%s %d", command, &value) == 2) {
        if (strcmp(command, "PUSH") == 0) {
            int *data = malloc(sizeof(int));  // Выделяем память для int
            if (data == NULL) {
                fprintf(stderr, "Ошибка выделения памяти\n");
                return;  
            }
            *data = value;  // Сохраняем значение
            stack_push(cpu->stack, (Data)data);  // Пушим указатель на выделенную память
            return;
        }
    } 
    // Обработка команды POP
    else if (sscanf(instruction, "%s %c", command, &reg_char) == 2) {
        if (strcmp(command, "POP") == 0) {
            int reg = reg_char - 'A';
            if (reg < 0 || reg >= REGISTERS) {
                fprintf(stderr, "Error: Invalid register %c\n", reg_char);
                return;  
            }
            
            if (stack_empty(cpu->stack)) {
                fprintf(stderr, "Error: Stack is empty, register cannot be POPed %c\n", reg_char);
                return; 
            }
            
            int *data = (int *)stack_pop(cpu->stack);  // Извлечение указателя на int
            if (data != NULL) {
                cpu->registers[reg] = *data;  // Получаем значение из извлеченного указателя
                free(data);  // Освобождаем память
            }
            return;
        }
    }

    // Обработка других команд (например, PUSH из регистра)
    if (strcmp(command, "PUSH") == 0 && reg_char >= 'A' && reg_char < 'A' + REGISTERS) {
        int reg = reg_char - 'A';
        int reg_value = cpu->registers[reg];
        int *data = malloc(sizeof(int));
        if (data == NULL) {
            fprintf(stderr, "Ошибка выделения памяти\n");
            return;
        }
        *data = reg_value; // Сохраняем значение регистра
        stack_push(cpu->stack, data); // Пушим указатель на выделенную память
        return;
    }

    // Обработка арифметических операций (ADD, SUB, MUL)
    int a, b;
    if (strcmp(command, "ADD") == 0 || strcmp(command, "SUB") == 0 || strcmp(command, "MUL") == 0) {
        int reg = reg_char - 'A';
        if (reg < 0 || reg >= REGISTERS) {
            fprintf(stderr, "Error: Invalid register %c\n", reg_char);
            return;
        }

        if (stack_empty(cpu->stack)) {
            fprintf(stderr, "Error: Stack is empty, cannot perform %s\n", command);
            return;
        }
        
        // Получаем первое значение
        int *ptr_a = (int *)stack_pop(cpu->stack);
        a = (ptr_a != NULL) ? *ptr_a : 0; // Если были данные, извлекаем их
        free(ptr_a); // Освобождаем память, выделенную для данных

        // Проверяем стек перед извлечением второго значения
        if (stack_empty(cpu->stack)) {
            fprintf(stderr, "Error: Stack is empty, cannot perform %s\n", command);
            return;
        }

        int *ptr_b = (int *)stack_pop(cpu->stack);
        b = (ptr_b != NULL) ? *ptr_b : 0; // Извлекаем данные
        free(ptr_b); // Освобождаем память, выделенную для данных

        if (strcmp(command, "ADD") == 0) {
            cpu->registers[reg] = a + b;
        } else if (strcmp(command, "SUB") == 0) {
            cpu->registers[reg] = a - b;
        } else if (strcmp(command, "MUL") == 0) {
            cpu->registers[reg] = a * b;
        }
        return;
    }
}


void print_registers(const CPU *cpu) {
    for (int i = 0; i < REGISTERS; i++) {
        printf("%c = %d\n", 'A' + i, cpu->registers[i]);
    }
}

int main(int argc, char **argv) {
    CPU cpu = {0};
    cpu.stack = stack_create(free_data); // Передаем функцию для освобождения
    if (cpu.stack == NULL) {
        fprintf(stderr, "Stack creation error\n");
        return EXIT_FAILURE;
    }

    if (argc < 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return EXIT_FAILURE;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        stack_delete(cpu.stack);
        return EXIT_FAILURE;
    }

    char instruction[50];

    while (fgets(instruction, sizeof(instruction), file)) {
        execute_instruction(&cpu, instruction);
    }

    fclose(file);
    print_registers(&cpu);
    stack_delete(cpu.stack);
    return EXIT_SUCCESS;
}
