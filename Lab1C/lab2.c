#include <stdio.h>         
#include <stdlib.h>       
#include <string.h>        
#include <stdint.h>        
#include "stack.h"       

#define REGISTERS 4        // Определяем количество регистров CPU

typedef struct {           // Определяем структуру CPU
    int registers[REGISTERS]; // Массив регистров процессора
    Stack *stack;         // Указатель на стек
} CPU;

void free_data(void *data) { // Функция для освобождения памяти, занимаемой данными в стеке
    free(data);              // Освобождаем память
}

void execute_instruction(CPU *cpu, const char *instruction) { // Функция для выполнения инструкции CPU
    char command[10];        // Строка для хранения команды
    char reg_char;           // Переменная для хранения символа регистра
    int value;               // Переменная для хранения значения

    // Если инструкция состоит из команды и целочисленного значения
    if (sscanf(instruction, "%s %d", command, &value) == 2) {
        if (strcmp(command, "PUSH") == 0) { // Если команда PUSH
            int *data = malloc(sizeof(int)); // Выделяем память для целочисленного значения
            if (data == NULL) { // Проверяем, успешно ли выделена память
                fprintf(stderr, "Ошибка выделения памяти\n"); 
                return;           
            }
            *data = value;       // Сохраняем значение в выделенной памяти
            stack_push(cpu->stack, (Data)data); // Добавляем данные в стек
            return;              
        }
    } 
    
    // Если инструкция состоит из команды и символа регистра
    else if (sscanf(instruction, "%s %c", command, &reg_char) == 2) {
        if (strcmp(command, "POP") == 0) { // Если команда POP
            int reg = reg_char - 'A';       // Преобразуем символ регистра в индекс
            if (reg < 0 || reg >= REGISTERS) { // Проверяем допустимость регистра
                fprintf(stderr, "Error: Invalid register %c\n", reg_char); 
                return; 
            }
            
            if (stack_empty(cpu->stack)) { // Проверяем, пуст ли стек
                fprintf(stderr, "Error: Stack is empty, register cannot be POPed %c\n", reg_char); 
                return; 
            }
            
            int *data = (int *)stack_pop(cpu->stack); // Извлекаем верхний элемент из стека
            if (data != NULL) {
                cpu->registers[reg] = *data; // Сохраняем данные в регистре
                free(data); // Освобождаем память, занятую данными
            }
            return; 
        }
    }

    // Если команда PUSH и использован регистр
    if (strcmp(command, "PUSH") == 0 && reg_char >= 'A' && reg_char < 'A' + REGISTERS) {
        int reg = reg_char - 'A'; // Преобразуем символ регистра в индекс
        int reg_value = cpu->registers[reg]; // Получаем значение из регистра
        int *data = malloc(sizeof(int)); // Выделяем память для хранения значения
        if (data == NULL) { // Проверяем, успешно ли выделена память
            fprintf(stderr, "Ошибка выделения памяти\n"); 
            return; 
        }
        *data = reg_value;  // Сохраняем значение в выделенной памяти
        stack_push(cpu->stack, data); // Добавляем данные в стек
        return; 
    }

    // Обработка арифметических команд: ADD, SUB, MUL
    int a, b; // Переменные для хранения значений из стека
    if (strcmp(command, "ADD") == 0 || strcmp(command, "SUB") == 0 || strcmp(command, "MUL") == 0) {
        int reg = reg_char - 'A'; // Преобразуем символ регистра в индекс
        if (reg < 0 || reg >= REGISTERS) { // Проверяем допустимость регистра
            fprintf(stderr, "Error: Invalid register %c\n", reg_char); 
            return; 
        }

        if (stack_empty(cpu->stack)) { // Проверяем, пуст ли стек
            fprintf(stderr, "Error: Stack is empty, cannot perform %s\n", command); 
            return; 
        }
        
        int *ptr_a = (int *)stack_pop(cpu->stack); // Извлекаем первое значение из стека
        a = (ptr_a != NULL) ? *ptr_a : 0; // Если данные успешно извлечены, сохраняем их, иначе 0
        free(ptr_a); // Освобождаем память 

        // Снова проверяем стек для второго значения
        if (stack_empty(cpu->stack)) { // Проверяем, пуст ли стек
            fprintf(stderr, "Error: Stack is empty, cannot perform %s\n", command); 
            return; 
        }

        int *ptr_b = (int *)stack_pop(cpu->stack); // Извлекаем второе значение из стека
        b = (ptr_b != NULL) ? *ptr_b : 0; // Если данные успешно извлечены, сохраняем их, иначе 0
        free(ptr_b); // Освобождаем память 

        // Выполнение арифметической операции в зависимости от команды
        if (strcmp(command, "ADD") == 0) { // Если команда ADD
            cpu->registers[reg] = a + b; // Сохраняем результат сложения в регистре
        } else if (strcmp(command, "SUB") == 0) { // Если команда SUB
            cpu->registers[reg] = a - b; // Сохраняем результат вычитания в регистре
        } else if (strcmp(command, "MUL") == 0) { // Если команда MUL
            cpu->registers[reg] = a * b; // Сохраняем результат умножения в регистре
        }
        return; 
    }
}

void print_registers(const CPU *cpu) { // Функция для вывода значений регистров на экран
    for (int i = 0; i < REGISTERS; i++) { // Проходим по всем регистрам
        printf("%c = %d\n", 'A' + i, cpu->registers[i]); // Выводим регистр и его значение
    }
}

int main(int argc, char **argv) { // Главная функция программы
    CPU cpu = {0}; // Инициализация структуры CPU с нулевыми значениями
    cpu.stack = stack_create(free_data); // Создаем стек, передавая функцию освобождения памяти
    if (cpu.stack == NULL) { // Проверяем, успешно ли создан стек
        fprintf(stderr, "Stack creation error\n"); 
        return EXIT_FAILURE; 
    }

    if (argc < 2) { // Если не передан аргумент с именем файла
        printf("Использование: %s <имя_файла>\n", argv[0]); // Выводим сообщение о использовании программы
        return EXIT_FAILURE; 
    }
    FILE *file = fopen(argv[1], "r"); // Открываем файл для чтения
    if (file == NULL) { // Проверяем, успешно ли открыт файл
        fprintf(stderr, "Error opening file\n"); 
        stack_delete(cpu.stack); // Освобождаем память, занятую стеком
        return EXIT_FAILURE;
    }

    char instruction[50]; // Массив для хранения инструкции

    // Читаем инструкции из файла до тех пор, пока не достигнем конца файла
    while (fgets(instruction, sizeof(instruction), file)) { // Читаем строку из файла
        execute_instruction(&cpu, instruction); // Выполняем считанную инструкцию
    }

    fclose(file); // Закрываем файл
    print_registers(&cpu); // Выводим значения регистров на экран
    stack_delete(cpu.stack); // Освобождаем память, занятую стеком
    return EXIT_SUCCESS; // Завершаем работу программы успешно
}
