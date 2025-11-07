#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"
#define MAX_LINE_LENGTH 100
#define MAX_VARS 4 

typedef struct {
    Stack* stack;           // Стек для операндов
    Stack* return_stack;    // Стек для адресов возврата
    int vars[MAX_VARS];     // Локальные переменные 
    int function_calls;     // Счетчик 
} JavaMachine;


//создание новой машины
JavaMachine* java_machine_create(void) {
    
    JavaMachine* machine = (JavaMachine*)malloc(sizeof(JavaMachine));
    if (machine == NULL) {
        return NULL;  
    }
    
    // Создание стека для операндов
    machine->stack = stack_create(NULL);
    if (machine->stack == NULL) {
        free(machine);  
        return NULL;
    }
    
    // Создание стека для адресов возврата
    machine->return_stack = stack_create(NULL);
    if (machine->return_stack == NULL) {
        stack_delete(machine->stack);
        free(machine);  
        return NULL;
    }
    
    // Инициализация
    for (int i = 0; i < MAX_VARS; i++) {
        machine->vars[i] = 0;
    }
    
    // Инициализация
    machine->function_calls = 0;
    return machine;
}

//удаление машины
void java_machine_delete(JavaMachine* machine) {
    if (machine == NULL) {
        return;  
    }

    stack_delete(machine->stack);
    stack_delete(machine->return_stack);
    free(machine);
}


//дабавление числа
void handle_bipush(JavaMachine* machine, int value) {
    if (machine == NULL) {
        return;  
    }
    
    stack_push(machine->stack, (Data)value);
    
    machine->function_calls++;

    printf("bipush %d\n", value);
}


//удаление первого элемента
void handle_pop(JavaMachine* machine) {
    if (machine == NULL) {
        return;  
    }
    
    
    if (stack_empty(machine->stack)) {
        printf("Error: pop from empty stack\n");
        return;
    }
    
    // Удаляем верхний элемент из стека
    stack_pop(machine->stack);
    
    machine->function_calls++;
    printf("pop\n");
}


//сложение 
void handle_iadd(JavaMachine* machine) {
    if (machine == NULL) {
        return;
    }
    
    // Проверка существования двух элементов
    if (stack_empty(machine->stack)) {
        printf("Error: iadd with empty stack\n");
        return;
    }
    
    Data b = stack_get(machine->stack);
    stack_pop(machine->stack);
    
    // Проверяем, что после извлечения первого элемента стек не пустой
    if (stack_empty(machine->stack)) {
        printf("Error: iadd with only one element\n");
        // Возвращаем b обратно в стек
        stack_push(machine->stack, b);
        return;
    }
    
    Data a = stack_get(machine->stack);
    stack_pop(machine->stack);
    
    // Складываем и кладем результат в стек
    Data result = a + b;
    stack_push(machine->stack, result);
    
    machine->function_calls++;
    printf("iadd\n");
}


//вычиатние
void handle_isub(JavaMachine* machine) {
    if (machine == NULL) {
        return; 
    }
    
    // Проверка существования двух элементов
    if (stack_empty(machine->stack)) {
        printf("Error: isub with empty stack\n");
        return;
    }
    
    Data b = stack_get(machine->stack);
    stack_pop(machine->stack);
    
    // Проверяем, что после извлечения первого элемента стек не пустой
    if (stack_empty(machine->stack)) {
        printf("Error: isub with only one element\n");
        // Возвращаем b обратно в стек
        stack_push(machine->stack, b);
        return;
    }
    
    Data a = stack_get(machine->stack);
    stack_pop(machine->stack);
    

    Data result = a - b;
    stack_push(machine->stack, result);
  
    machine->function_calls++;
    
    printf("isub\n");
}


//умножение
void handle_imul(JavaMachine* machine) {
    if (machine == NULL) {
        return;  
    }
    
    // Проверка существования двух элементов
    if (stack_empty(machine->stack)) {
        printf("Error: imul with empty stack\n");
        return;
    }
    
    Data b = stack_get(machine->stack);
    stack_pop(machine->stack);
    
    // Проверяем, что после извлечения первого элемента стек не пустой
    if (stack_empty(machine->stack)) {
        printf("Error: imul with only one element\n");
        // Возвращаем b обратно в стек
        stack_push(machine->stack, b);
        return;
    }

    Data a = stack_get(machine->stack);
    stack_pop(machine->stack);
    
    Data result = a * b;
    stack_push(machine->stack, result);
    
    machine->function_calls++;
    
    printf("imul\n");
}


//побитовое и
void handle_iand(JavaMachine* machine) {
    if (machine == NULL) {
        return;
    }
    
    // Проверка существования двух элементов
    if (stack_empty(machine->stack)) {
        printf("Error: iand with empty stack\n");
        return;
    }
    
    Data b = stack_get(machine->stack);
    stack_pop(machine->stack);
    
    // Проверяем, что после извлечения первого элемента стек не пустой
    if (stack_empty(machine->stack)) {
        printf("Error: iand with only one element\n");
        // Возвращаем b обратно в стек
        stack_push(machine->stack, b);
        return;
    }
    
    Data a = stack_get(machine->stack);
    stack_pop(machine->stack);
    
   
    Data result = a & b;
    stack_push(machine->stack, result);
    
    machine->function_calls++;
    
    printf("iand\n");
}


//побитовок или
void handle_ior(JavaMachine* machine) {
    if (machine == NULL) {
        return;  
    }
    
    // Проверка существования двух элементов
    if (stack_empty(machine->stack)) {
        printf("Error: ior with empty stack\n");
        return;
    }
    
    Data b = stack_get(machine->stack);
    stack_pop(machine->stack);
    
    // Проверяем, что после извлечения первого элемента стек не пустой
    if (stack_empty(machine->stack)) {
        printf("Error: ior with only one element\n");
        // Возвращаем b обратно в стек
        stack_push(machine->stack, b);
        return;
    }
    
    Data a = stack_get(machine->stack);
    stack_pop(machine->stack);
    
    // побитовое ИЛИ
    Data result = a | b;
    stack_push(machine->stack, result);
    
    machine->function_calls++;
    
    printf("ior\n");
}


//исключающее или
void handle_ixor(JavaMachine* machine) {
    if (machine == NULL) {
        return;  
    }
    
    // Проверка существования двух элементов
    if (stack_empty(machine->stack)) {
        printf("Error: ixor with empty stack\n");
        return;
    }
    
    Data b = stack_get(machine->stack);
    stack_pop(machine->stack);
    
    // Проверяем, что после извлечения первого элемента стек не пустой
    if (stack_empty(machine->stack)) {
        printf("Error: ixor with only one element\n");
        // Возвращаем b обратно в стек
        stack_push(machine->stack, b);
        return;
    }
    
    Data a = stack_get(machine->stack);
    stack_pop(machine->stack);
     
    Data result = a ^ b;
    stack_push(machine->stack, result);
    
    
    machine->function_calls++;
    
    printf("ixor\n");
}


//добавление переменных
void handle_iload_0(JavaMachine* machine) {
    if (machine == NULL) {
        return; 
    }
    
    // Загружаем значение переменной 0 в стек
    Data value = (Data)machine->vars[0];
    stack_push(machine->stack, value);
    
    machine->function_calls++;
    
    printf("iload_0\n");
}

void handle_iload_1(JavaMachine* machine) {
    if (machine == NULL) {
        return;  
    }
    
    // Загружаем значение переменной 1 в стек
    Data value = (Data)machine->vars[1];
    stack_push(machine->stack, value);
    
    machine->function_calls++;
    
    printf("iload_1\n");
}

void handle_iload_2(JavaMachine* machine) {
    if (machine == NULL) {
        return;  
    }
    
    // Загружаем значение переменной 2 в стек
    Data value = (Data)machine->vars[2];
    stack_push(machine->stack, value);
    
    machine->function_calls++;
    
    printf("iload_2\n");
}

void handle_iload_3(JavaMachine* machine) {
    if (machine == NULL) {
        return; 
    }
    
    // Загружаем значение переменной 3 в стек
    Data value = (Data)machine->vars[3];
    stack_push(machine->stack, value);
    
    machine->function_calls++;
    
    printf("iload_3\n");
}   

//извлечение значения из сека и сохрание в vars
void handle_istore_0(JavaMachine* machine) {
    if (machine == NULL) {
        return;  
    }
    
    if (stack_empty(machine->stack)) {
        printf("Error: istore_0 with empty stack\n");
        return;
    }
    
    // Извлекаем значение с верха стека
    Data value = stack_get(machine->stack);
    stack_pop(machine->stack);
    
    // Сохраняем в переменную 0
    machine->vars[0] = (int)value;
    
    machine->function_calls++;
    
    printf("istore_0\n");
}

void handle_istore_1(JavaMachine* machine) {
    if (machine == NULL) {
        return; 
    }
    

    if (stack_empty(machine->stack)) {
        printf("Error: istore_1 with empty stack\n");
        return;
    }
    
    // Извлекаем значение с верха стека
    Data value = stack_get(machine->stack);
    stack_pop(machine->stack);
    
    // Сохраняем в переменную 1
    machine->vars[1] = (int)value;
    
    machine->function_calls++;
    
    printf("istore_1\n");
}

void handle_istore_2(JavaMachine* machine) {
    if (machine == NULL) {
        return;  
    }
    
    if (stack_empty(machine->stack)) {
        printf("Error: istore_2 with empty stack\n");
        return;
    }
    
    // Извлекаем значение с верха стека
    Data value = stack_get(machine->stack);
    stack_pop(machine->stack);
    
    // Сохраняем в переменную 2
    machine->vars[2] = (int)value;
    
    machine->function_calls++;
    
    printf("istore_2\n");
}

void handle_istore_3(JavaMachine* machine) {
    if (machine == NULL) {
        return;  
    }
    
    if (stack_empty(machine->stack)) {
        printf("Error: istore_3 with empty stack\n");
        return;
    }
    
    // Извлекаем значение с верха стека
    Data value = stack_get(machine->stack);
    stack_pop(machine->stack);
    
    // Сохраняем в переменную 3
    machine->vars[3] = (int)value;
    
    machine->function_calls++;
    
    printf("istore_3\n");
}

//свап 
void handle_swap(JavaMachine* machine) {
    if (machine == NULL) {
        return;  
    }
    
    // Проверка существования двух элементов
    if (stack_empty(machine->stack)) {
        printf("Error: swap with empty stack\n");
        return;
    }
    
    Data b = stack_get(machine->stack);
    stack_pop(machine->stack);
    
    // Проверяем, что после извлечения первого элемента стек не пустой
    if (stack_empty(machine->stack)) {
        printf("Error: swap with only one element\n");
        // Возвращаем b обратно в стек
        stack_push(machine->stack, b);
        return;
    }
    
    Data a = stack_get(machine->stack);
    stack_pop(machine->stack);
    
    // свапаем
    stack_push(machine->stack, b);
    stack_push(machine->stack, a);
    
    machine->function_calls++;
    
    printf("swap\n");
}

//сохранение адреса
void handle_invokestatic(JavaMachine* machine, int address) {
    if (machine == NULL) {
        return; 
    }
    
    // добавляем адрес возврата в отдельный стек для адресов возврата
    stack_push(machine->return_stack, (Data)address);
    
    machine->function_calls++;

    printf("invokestatic %d\n", address);
}


//извлечение адреса 
void handle_return(JavaMachine* machine) {
    if (machine == NULL) {
        return;  
    }
    
    // Проверяем, что стек адресов возврата не пустой
    if (stack_empty(machine->return_stack)) {
        printf("Error: return with empty return stack\n");
        return;
    }
    
    // Извлекаем адрес возврата из отдельного стека
    Data return_address = stack_get(machine->return_stack);
    stack_pop(machine->return_stack);

    machine->function_calls++;
    
    // Выводим адрес возврата
    printf("return %d\n", (int)return_address);
}



void parse_and_execute(JavaMachine* machine, const char* line) {
    if (machine == NULL || line == NULL) {
        return;  
    }
    
    // Пропускаем пустые строки и пробелы
    while (*line == ' ' || *line == '\t' || *line == '\n' || *line == '\r') {
        line++;
    }
    
    if (*line == '\0') {
        return;  
    }
    
    // Парсим команду
    if (strncmp(line, "bipush", 6) == 0) {
        int value;
        if (sscanf(line + 6, " %d", &value) == 1) {
            handle_bipush(machine, value);
        } else {
            printf("Error: invalid bipush command\n");
        }
    }
    else if (strcmp(line, "pop") == 0) {
        handle_pop(machine);
    }
    else if (strcmp(line, "iadd") == 0) {
        handle_iadd(machine);
    }
    else if (strcmp(line, "isub") == 0) {
        handle_isub(machine);
    }
    else if (strcmp(line, "imul") == 0) {
        handle_imul(machine);
    }
    else if (strcmp(line, "iand") == 0) {
        handle_iand(machine);
    }
    else if (strcmp(line, "ior") == 0) {
        handle_ior(machine);
    }
    else if (strcmp(line, "ixor") == 0) {
        handle_ixor(machine);
    }
    else if (strcmp(line, "iload_0") == 0) {
        handle_iload_0(machine);
    }
    else if (strcmp(line, "iload_1") == 0) {
        handle_iload_1(machine);
    }
    else if (strcmp(line, "iload_2") == 0) {
        handle_iload_2(machine);
    }
    else if (strcmp(line, "iload_3") == 0) {
        handle_iload_3(machine);
    }
    else if (strcmp(line, "istore_0") == 0) {
        handle_istore_0(machine);
    }
    else if (strcmp(line, "istore_1") == 0) {
        handle_istore_1(machine);
    }
    else if (strcmp(line, "istore_2") == 0) {
        handle_istore_2(machine);
    }
    else if (strcmp(line, "istore_3") == 0) {
        handle_istore_3(machine);
    }
    else if (strcmp(line, "swap") == 0) {
        handle_swap(machine);
    }
    else if (strncmp(line, "invokestatic", 12) == 0) {
        int address;
        if (sscanf(line + 12, " %d", &address) == 1) {
            handle_invokestatic(machine, address);
        } else {
            printf("Error: invalid invokestatic command\n");
        }
    }
    else if (strcmp(line, "return") == 0) {
        handle_return(machine);
    }
    else {
        printf("Error: unknown command: %s\n", line);
    }
}

void process_java_file(JavaMachine* machine, const char* filename) {
    if (machine == NULL || filename == NULL) {
        return;  
    }
    
    // Открываем файл для чтения
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: cannot open file %s\n", filename);
        return;
    }
    
    char line[MAX_LINE_LENGTH];
    
    // Читаем файл построчно
    while (fgets(line, sizeof(line), file) != NULL) {
        // Убираем символ новой строки в конце
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        
    
        parse_and_execute(machine, line);
    }
    
    fclose(file);
}


//вывод финальных результатов
void print_results(JavaMachine* machine) {
    if (machine == NULL) {
        return;  
    }
    
    // Выводим состояние стека
    printf("stack:\n");
    if (stack_empty(machine->stack)) {
        printf("(empty)\n");
    } else {
        // Создаем временный стек для вывода
        Stack* temp_stack = stack_create(NULL);
        if (temp_stack == NULL) {
            printf("Error: cannot create temporary stack\n");
            return;
        }
        // Копируем элементы в обратном порядке
        while (!stack_empty(machine->stack)) {
            Data value = stack_get(machine->stack);
            stack_pop(machine->stack);
            stack_push(temp_stack, value);
        }
        
        // Выводим элементы в правильном порядке
        while (!stack_empty(temp_stack)) {
            Data value = stack_get(temp_stack);
            stack_pop(temp_stack);
            printf("%d\n", (int)value);
            // Возвращаем обратно в основной стек
            stack_push(machine->stack, value);
        }
        
        stack_delete(temp_stack);
    }
    
    // Выводим переменные
    printf("vars:\n");
    for (int i = 0; i < MAX_VARS; i++) {
        printf("%d\n", machine->vars[i]);
    }
    
    // Выводим количество вызовов функций
    printf("function_calls: %d\n", machine->function_calls);
}



int main(int argc, char** argv) {
    // Проверяем аргументы командной строки
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    JavaMachine* machine = java_machine_create();
    if (machine == NULL) {
        printf("Error: cannot create Java machine\n");
        return 1;
    }
    
    // Обрабатываем входной файл
    process_java_file(machine, argv[1]);
    
    // Выводим результаты
    print_results(machine);
    
    // Освобождаем память
    java_machine_delete(machine);
    
    return 0;
}




