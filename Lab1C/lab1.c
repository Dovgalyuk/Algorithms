#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "stack.h"
#define MAX_LINE_LENGTH 100
#define MAX_VARS 4 


typedef struct {
    int tag;       // метка типа
    int value;     // значение (число или адрес возврата)
} VMValue;

enum { VT_INT = 0x11AA55CC, VT_RET = 0x22BB66DD };

static inline bool is_int_token(Data d) {
    if (d == 0) return false;
    return ((VMValue*)(void*)d)->tag == VT_INT;
}
static inline bool is_return_token(Data d) {
    if (d == 0) return false;
    return ((VMValue*)(void*)d)->tag == VT_RET;
}
static inline int get_int(Data d) {
    return ((VMValue*)(void*)d)->value;
}
static inline int get_ret(Data d) {
    return ((VMValue*)(void*)d)->value;
}
static inline Data make_int(int x) {
    VMValue* v = (VMValue*)malloc(sizeof(VMValue));
    if (!v) return (Data)0;
    v->tag = VT_INT;
    v->value = x;
    return (Data)(uintptr_t)v;
}
static inline Data make_ret(int addr) {
    VMValue* v = (VMValue*)malloc(sizeof(VMValue));
    if (!v) return (Data)0;
    v->tag = VT_RET;
    v->value = addr;
    return (Data)(uintptr_t)v;
}

typedef struct {
    Stack* stack;           // Стек для операндов и адресов возврата 
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

    // Очистка элементов стека - освобождаем все VMValue
    while (!stack_empty(machine->stack)) {
        Data d = stack_get(machine->stack);
        stack_pop(machine->stack);
        if (d) free((void*)(uintptr_t)d);
    }
    stack_delete(machine->stack);
    free(machine);
}


//дабавление числа
void handle_bipush(JavaMachine* machine, int value) {
    if (machine == NULL) {
        return;  
    }
    
    Data d = make_int(value);
    if (d == 0) {
        printf("Error: cannot allocate int value\n");
        return;
    }
    stack_push(machine->stack, d);
    
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
    
    // Проверяем, что верхний элемент не является адресом возврата
    Data top = stack_get(machine->stack);
    if (is_return_token(top)) {
        printf("Error: pop with return address\n");
        return;
    }
    
    // Удаляем верхний элемент из стека и освобождаем память
    stack_pop(machine->stack);
    free((void*)(uintptr_t)top);
    
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
    
    Data b_token = stack_get(machine->stack);
    if (!is_int_token(b_token)) {
        if (is_return_token(b_token)) {
            printf("Error: iadd with return address\n");
        } else {
            printf("Error: iadd with invalid operand\n");
        }
        return;
    }
    stack_pop(machine->stack);
    int ib = get_int(b_token);
    free((void*)(uintptr_t)b_token);
    
    // Проверяем, что после извлечения первого элемента стек не пустой
    if (stack_empty(machine->stack)) {
        printf("Error: iadd with only one element\n");
        return;
    }
    
    Data a_token = stack_get(machine->stack);
    if (!is_int_token(a_token)) {
        if (is_return_token(a_token)) {
            printf("Error: iadd with return address\n");
        } else {
            printf("Error: iadd with invalid operand\n");
        }
        return;
    }
    stack_pop(machine->stack);
    int ia = get_int(a_token);
    free((void*)(uintptr_t)a_token);
    
    // Складываем и кладем результат в стек
    Data result = make_int(ia + ib);
    if (result == 0) { 
        printf("Error: cannot allocate int value\n"); 
        return; 
    }
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
    
    Data b_token = stack_get(machine->stack);
    if (!is_int_token(b_token)) {
        if (is_return_token(b_token)) {
            printf("Error: isub with return address\n");
        } else {
            printf("Error: isub with invalid operand\n");
        }
        return;
    }
    stack_pop(machine->stack);
    int ib = get_int(b_token);
    free((void*)(uintptr_t)b_token);
    
    // Проверяем, что после извлечения первого элемента стек не пустой
    if (stack_empty(machine->stack)) {
        printf("Error: isub with only one element\n");
        return;
    }
    
    Data a_token = stack_get(machine->stack);
    if (!is_int_token(a_token)) {
        if (is_return_token(a_token)) {
            printf("Error: isub with return address\n");
        } else {
            printf("Error: isub with invalid operand\n");
        }
        return;
    }
    stack_pop(machine->stack);
    int ia = get_int(a_token);
    free((void*)(uintptr_t)a_token);
    

    Data result = make_int(ia - ib);
    if (!result) { 
        printf("Error: cannot allocate int value\n"); 
        return; 
    }
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
    
    Data b_token = stack_get(machine->stack);
    if (!is_int_token(b_token)) {
        if (is_return_token(b_token)) {
            printf("Error: imul with return address\n");
        } else {
            printf("Error: imul with invalid operand\n");
        }
        return;
    }
    stack_pop(machine->stack);
    int ib = get_int(b_token);
    free((void*)(uintptr_t)b_token);
    
    // Проверяем, что после извлечения первого элемента стек не пустой
    if (stack_empty(machine->stack)) {
        printf("Error: imul with only one element\n");
        return;
    }

    Data a_token = stack_get(machine->stack);
    if (!is_int_token(a_token)) {
        if (is_return_token(a_token)) {
            printf("Error: imul with return address\n");
        } else {
            printf("Error: imul with invalid operand\n");
        }
        return;
    }
    stack_pop(machine->stack);
    int ia = get_int(a_token);
    free((void*)(uintptr_t)a_token);
    
    Data result = make_int(ia * ib);
    if (!result) { 
        printf("Error: cannot allocate int value\n"); 
        return; 
    }
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
    
    Data b_token = stack_get(machine->stack);
    if (!is_int_token(b_token)) {
        if (is_return_token(b_token)) {
            printf("Error: iand with return address\n");
        } else {
            printf("Error: iand with invalid operand\n");
        }
        return;
    }
    stack_pop(machine->stack);
    int ib = get_int(b_token);
    free((void*)(uintptr_t)b_token);
    
    // Проверяем, что после извлечения первого элемента стек не пустой
    if (stack_empty(machine->stack)) {
        printf("Error: iand with only one element\n");
        return;
    }
    
    Data a_token = stack_get(machine->stack);
    if (!is_int_token(a_token)) {
        if (is_return_token(a_token)) {
            printf("Error: iand with return address\n");
        } else {
            printf("Error: iand with invalid operand\n");
        }
        return;
    }
    stack_pop(machine->stack);
    int ia = get_int(a_token);
    free((void*)(uintptr_t)a_token);
    
   
    Data result = make_int(ia & ib);
    if (!result) { 
        printf("Error: cannot allocate int value\n"); 
        return; 
    }
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
    
    Data b_token = stack_get(machine->stack);
    if (!is_int_token(b_token)) {
        if (is_return_token(b_token)) {
            printf("Error: ior with return address\n");
        } else {
            printf("Error: ior with invalid operand\n");
        }
        return;
    }
    stack_pop(machine->stack);
    int ib = get_int(b_token);
    free((void*)(uintptr_t)b_token);
    
    // Проверяем, что после извлечения первого элемента стек не пустой
    if (stack_empty(machine->stack)) {
        printf("Error: ior with only one element\n");
        return;
    }
    
    Data a_token = stack_get(machine->stack);
    if (!is_int_token(a_token)) {
        if (is_return_token(a_token)) {
            printf("Error: ior with return address\n");
        } else {
            printf("Error: ior with invalid operand\n");
        }
        return;
    }
    stack_pop(machine->stack);
    int ia = get_int(a_token);
    free((void*)(uintptr_t)a_token);
    
    // побитовое ИЛИ
    Data result = make_int(ia | ib);
    if (!result) { 
        printf("Error: cannot allocate int value\n"); 
        return; 
    }
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
    
    Data b_token = stack_get(machine->stack);
    if (!is_int_token(b_token)) {
        if (is_return_token(b_token)) {
            printf("Error: ixor with return address\n");
        } else {
            printf("Error: ixor with invalid operand\n");
        }
        return;
    }
    stack_pop(machine->stack);
    int ib = get_int(b_token);
    free((void*)(uintptr_t)b_token);
    
    // Проверяем, что после извлечения первого элемента стек не пустой
    if (stack_empty(machine->stack)) {
        printf("Error: ixor with only one element\n");
        return;
    }
    
    Data a_token = stack_get(machine->stack);
    if (!is_int_token(a_token)) {
        if (is_return_token(a_token)) {
            printf("Error: ixor with return address\n");
        } else {
            printf("Error: ixor with invalid operand\n");
        }
        return;
    }
    stack_pop(machine->stack);
    int ia = get_int(a_token);
    free((void*)(uintptr_t)a_token);
     
    Data result = make_int(ia ^ ib);
    if (!result) { 
        printf("Error: cannot allocate int value\n"); 
        return; 
    }
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
    Data d = make_int(machine->vars[0]);
    if (!d) {
        printf("Error: cannot allocate int value\n");
        return;
    }
    stack_push(machine->stack, d);
    
    machine->function_calls++;
    
    printf("iload_0\n");
}

void handle_iload_1(JavaMachine* machine) {
    if (machine == NULL) {
        return;  
    }
    
    // Загружаем значение переменной 1 в стек
    Data d = make_int(machine->vars[1]);
    if (!d) {
        printf("Error: cannot allocate int value\n");
        return;
    }
    stack_push(machine->stack, d);
    
    machine->function_calls++;
    
    printf("iload_1\n");
}

void handle_iload_2(JavaMachine* machine) {
    if (machine == NULL) {
        return;  
    }
    
    // Загружаем значение переменной 2 в стек
    Data d = make_int(machine->vars[2]);
    if (!d) {
        printf("Error: cannot allocate int value\n");
        return;
    }
    stack_push(machine->stack, d);
    
    machine->function_calls++;
    
    printf("iload_2\n");
}

void handle_iload_3(JavaMachine* machine) {
    if (machine == NULL) {
        return; 
    }
    
    // Загружаем значение переменной 3 в стек
    Data d = make_int(machine->vars[3]);
    if (!d) {
        printf("Error: cannot allocate int value\n");
        return;
    }
    stack_push(machine->stack, d);
    
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
    if (!is_int_token(value)) {
        if (is_return_token(value)) {
            printf("Error: istore_0 with return address\n");
        } else {
            printf("Error: istore_0 with invalid operand\n");
        }
        return;
    }
    stack_pop(machine->stack);
    int iv = get_int(value);
    free((void*)(uintptr_t)value);
    
    // Сохраняем в переменную 0
    machine->vars[0] = iv;
    
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
    if (!is_int_token(value)) {
        if (is_return_token(value)) {
            printf("Error: istore_1 with return address\n");
        } else {
            printf("Error: istore_1 with invalid operand\n");
        }
        return;
    }
    stack_pop(machine->stack);
    int iv = get_int(value);
    free((void*)(uintptr_t)value);
    
    // Сохраняем в переменную 1
    machine->vars[1] = iv;
    
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
    if (!is_int_token(value)) {
        if (is_return_token(value)) {
            printf("Error: istore_2 with return address\n");
        } else {
            printf("Error: istore_2 with invalid operand\n");
        }
        return;
    }
    stack_pop(machine->stack);
    int iv = get_int(value);
    free((void*)(uintptr_t)value);
    
    // Сохраняем в переменную 2
    machine->vars[2] = iv;
    
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
    if (!is_int_token(value)) {
        if (is_return_token(value)) {
            printf("Error: istore_3 with return address\n");
        } else {
            printf("Error: istore_3 with invalid operand\n");
        }
        return;
    }
    stack_pop(machine->stack);
    int iv = get_int(value);
    free((void*)(uintptr_t)value);
    
    // Сохраняем в переменную 3
    machine->vars[3] = iv;
    
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
    if (is_return_token(b)) {
        printf("Error: swap with return address\n");
        return;
    }
    stack_pop(machine->stack);
    
    // Проверяем, что после извлечения первого элемента стек не пустой
    if (stack_empty(machine->stack)) {
        printf("Error: swap with only one element\n");
        // Возвращаем b обратно в стек
        stack_push(machine->stack, b);
        return;
    }
    
    Data a = stack_get(machine->stack);
    if (is_return_token(a)) {
        stack_push(machine->stack, b);
        printf("Error: swap with return address\n");
        return;
    }
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
    
    // создаём токен адреса возврата на операндном стеке
    Data ra = make_ret(address);
    if (!ra) { 
        printf("Error: cannot allocate return address token\n"); 
        return; 
    }
    stack_push(machine->stack, ra);
    
    machine->function_calls++;

    printf("invokestatic %d\n", address);
}


//извлечение адреса 
void handle_return(JavaMachine* machine) {
    if (machine == NULL) {
        return;  
    }
    
    if (stack_empty(machine->stack)) {
        printf("Error: return with empty stack\n");
        return;
    }
    
    // Верх стека должен быть токеном адреса возврата
    Data top = stack_get(machine->stack);
    if (!is_return_token(top)) {
        printf("Error: return with non-address value\n");
        return;
    }
    int addr = get_ret(top);
    stack_pop(machine->stack);
    // Освобождаем память токена адреса возврата
    free((void*)(uintptr_t)top);

    machine->function_calls++;
    
    // Выводим адрес возврата
    printf("return %d\n", addr);
}



void parse_and_execute(JavaMachine* machine, const char* line) {
    if (machine == NULL || line == NULL) {
        return;  
    }
    
    char command[MAX_LINE_LENGTH];
    int value;
    
    if (sscanf(line, "%s %d", command, &value) == 2) {
        if (strcmp(command, "bipush") == 0) {
            handle_bipush(machine, value);
        } else if (strcmp(command, "invokestatic") == 0) {
            handle_invokestatic(machine, value);
        } else {
            printf("Unknown command: %s\n", command);
        }
    } else if (sscanf(line, "%s", command) == 1) {
        if (strcmp(command, "pop") == 0) {
            handle_pop(machine);
        } else if (strcmp(command, "iadd") == 0) {
            handle_iadd(machine);
        } else if (strcmp(command, "isub") == 0) {
            handle_isub(machine);
        } else if (strcmp(command, "imul") == 0) {
            handle_imul(machine);
        } else if (strcmp(command, "iand") == 0) {
            handle_iand(machine);
        } else if (strcmp(command, "ior") == 0) {
            handle_ior(machine);
        } else if (strcmp(command, "ixor") == 0) {
            handle_ixor(machine);
        } else if (strcmp(command, "iload_0") == 0) {
            handle_iload_0(machine);
        } else if (strcmp(command, "iload_1") == 0) {
            handle_iload_1(machine);
        } else if (strcmp(command, "iload_2") == 0) {
            handle_iload_2(machine);
        } else if (strcmp(command, "iload_3") == 0) {
            handle_iload_3(machine);
        } else if (strcmp(command, "istore_0") == 0) {
            handle_istore_0(machine);
        } else if (strcmp(command, "istore_1") == 0) {
            handle_istore_1(machine);
        } else if (strcmp(command, "istore_2") == 0) {
            handle_istore_2(machine);
        } else if (strcmp(command, "istore_3") == 0) {
            handle_istore_3(machine);
        } else if (strcmp(command, "swap") == 0) {
            handle_swap(machine);
        } else if (strcmp(command, "return") == 0) {
            handle_return(machine);
        } else {
            printf("Unknown command: %s\n", command);
        }
    }
}

void print_results(JavaMachine* machine) {
    if (machine == NULL) {
        return;
    }
    
    printf("stack:\n");
    if (stack_empty(machine->stack)) {
        printf("(empty)\n");
    } else {
        // Создаём временный стек для вывода
        Stack* temp = stack_create(NULL);
        if (temp == NULL) {
            return;
        }
        
        // Перекладываем элементы во временный стек (чтобы вывести в правильном порядке)
        while (!stack_empty(machine->stack)) {
            Data d = stack_get(machine->stack);
            stack_pop(machine->stack);
            stack_push(temp, d);
        }
        
        // Выводим и возвращаем обратно
        while (!stack_empty(temp)) {
            Data d = stack_get(temp);
            stack_pop(temp);
            stack_push(machine->stack, d);
            
            // Выводим значение
            VMValue* v = (VMValue*)(void*)d;
            printf("%d\n", v->value);
        }
        
        stack_delete(temp);
    }
    
    printf("vars:\n");
    for (int i = 0; i < MAX_VARS; i++) {
        printf("%d\n", machine->vars[i]);
    }
    
    printf("function_calls: %d\n", machine->function_calls);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
        return 1;
    }
    
    JavaMachine* machine = java_machine_create();
    if (machine == NULL) {
        fprintf(stderr, "Error: cannot create Java machine\n");
        fclose(file);
        return 1;
    }
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        // Удаляем символ новой строки
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        
        parse_and_execute(machine, line);
    }
    
    fclose(file);
    
    print_results(machine);
    
    java_machine_delete(machine);
    
    return 0;
}
