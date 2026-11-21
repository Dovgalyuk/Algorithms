#include <fstream>
#include <iostream>
#include <string>

#include "stack.h"

// Константа пустого стержня (по правилам Ханойских башен для байтов)
const int EMPTY_TOWER = 255;

// Чтение содержимого файла целиком в строку
std::string read_file(const std::string &path)
{
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Cannot open file: " << path << std::endl;
        return "";
    }

    std::string content;
    char ch;
    while (file.get(ch))
    {
        content += ch;
    }
    return content;
}

// Освобождение памяти всех используемых стеков
void free_all_stacks(Stack *t1, Stack *t2, Stack *t3, Stack *in)
{
    stack_delete(t1);
    stack_delete(t2);
    stack_delete(t3);
    stack_delete(in);
}

// Помещение диска на стержень с проверкой правила Ханойских башен
bool push_tower(Stack *tower, int disk)
{
    // Если стержень пуст, максимальный допустимый диск — 255.
    // Если не пуст — ограничением является верхний диск стержня.
    int limit = stack_empty(tower) ? EMPTY_TOWER : stack_get(tower);

    // Правило: нельзя класть больший диск на меньший
    if (disk > limit)
    {
        std::cerr << "Hanoi error: rule violated" << std::endl;
        return false;
    }

    stack_push(tower, disk);
    return true;
}

// Снятие верхнего диска со стержня
int pop_tower(Stack *tower)
{
    if (stack_empty(tower))
    {
        return EMPTY_TOWER;
    }
    int disk = stack_get(tower);
    stack_pop(tower);
    return disk;
}

// Вывод одного символа (печатный символ или шестнадцатеричный код \xHH)
void print_symbol(int val)
{
    if (val >= 32 && val <= 126)
    {
        std::cout << (char)val;
    }
    else
    {
        const char hex[] = "0123456789abcdef";
        unsigned char b = (unsigned char)val;
        std::cout << "\\x" << hex[b / 16] << hex[b % 16];
    }
}

// Вывод состояния стержня со дна до вершины
void print_tower(Stack *tower)
{
    // Чтобы вывести элементы со дна до вершины, перекладываем их
    // во временный стек (при этом порядок элементов развернётся)
    Stack *temp = stack_create();

    while (!stack_empty(tower))
    {
        stack_push(temp, stack_get(tower));
        stack_pop(tower);
    }

    // Теперь снимаем элементы с вершины temp (это было дно tower),
    // выводим их и возвращаем обратно в tower
    while (!stack_empty(temp))
    {
        int val = stack_get(temp);
        stack_pop(temp);
        print_symbol(val);
        stack_push(tower, val);
    }

    stack_delete(temp);
    std::cout << "\n";
}

// Получение следующего символа из входных данных
int read_input(Stack *input_stack)
{
    if (stack_empty(input_stack))
    {
        return 0; // при исчерпании ввода возвращаем 0
    }
    int val = stack_get(input_stack);
    stack_pop(input_stack);
    return val;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <script_file> <input_file>\n";
        return 1;
    }

    std::string script = read_file(argv[1]);
    std::string input = read_file(argv[2]);

    // Удаляем переводы строк в конце входного файла, если они есть
    while (!input.empty() && (input.back() == '\n' || input.back() == '\r'))
    {
        input.pop_back();
    }

    // Создаем три стержня (стека)
    Stack *tower1 = stack_create();
    Stack *tower2 = stack_create();
    Stack *tower3 = stack_create();

    // Создаем стек для входных символов
    // Заполняем его с конца строки, чтобы первый символ оказался на вершине
    Stack *input_stack = stack_create();
    for (size_t i = input.size(); i > 0; --i)
    {
        stack_push(input_stack, (unsigned char)input[i - 1]);
    }

    bool printed_output = false;

    // Выполнение команд скрипта
    for (size_t i = 0; i < script.size(); ++i)
    {
        char cmd = script[i];

        if (cmd == '(')
        {
            // 1 -> 2: переместить диск со стержня 1 на стержень 2
            if (!push_tower(tower2, pop_tower(tower1)))
            {
                free_all_stacks(tower1, tower2, tower3, input_stack);
                return 1;
            }
        }
        else if (cmd == ')')
        {
            // 2 -> 1: переместить диск со стержня 2 на стержень 1
            if (!push_tower(tower1, pop_tower(tower2)))
            {
                free_all_stacks(tower1, tower2, tower3, input_stack);
                return 1;
            }
        }
        else if (cmd == '[')
        {
            // 3 -> 2: переместить диск со стержня 3 на стержень 2
            if (!push_tower(tower2, pop_tower(tower3)))
            {
                free_all_stacks(tower1, tower2, tower3, input_stack);
                return 1;
            }
        }
        else if (cmd == ']')
        {
            // 2 -> 3: переместить диск со стержня 2 на стержень 3
            if (!push_tower(tower3, pop_tower(tower2)))
            {
                free_all_stacks(tower1, tower2, tower3, input_stack);
                return 1;
            }
        }
        else if (cmd == '{')
        {
            // Ввод -> 2: прочитать символ и положить на стержень 2
            if (!push_tower(tower2, read_input(input_stack)))
            {
                free_all_stacks(tower1, tower2, tower3, input_stack);
                return 1;
            }
        }
        else if (cmd == '}')
        {
            // 2 -> Вывод: снять со стержня 2 и напечатать символ
            int val = pop_tower(tower2);
            std::cout << (char)val;
            printed_output = true;
        }
        else if (cmd == '>')
        {
            // Дублирование: снять значение со стержня 2 и положить дважды
            int a = pop_tower(tower2);
            if (!push_tower(tower2, a) || !push_tower(tower2, a))
            {
                free_all_stacks(tower1, tower2, tower3, input_stack);
                return 1;
            }
        }
        else if (cmd == '<')
        {
            // Дедупликация: снять два значения со стержня 2; если равны — вернуть одно
            int a1 = pop_tower(tower2);
            int a2 = pop_tower(tower2);
            if (a1 != a2)
            {
                std::cerr << "Hanoi error: irreversible operation" << std::endl;
                free_all_stacks(tower1, tower2, tower3, input_stack);
                return 1;
            }
            if (!push_tower(tower2, a1))
            {
                free_all_stacks(tower1, tower2, tower3, input_stack);
                return 1;
            }
        }
        else if (cmd == '-')
        {
            // Вычитание: снять два значения a и b, положить b, затем (b - a)
            int a = pop_tower(tower2);
            int b = pop_tower(tower2);
            if (!push_tower(tower2, b) || !push_tower(tower2, b - a))
            {
                free_all_stacks(tower1, tower2, tower3, input_stack);
                return 1;
            }
        }
        // Все остальные символы (пробелы, переводы строк, комментарии) пропускаются
    }

    // Если команда '}' выводила текст, переходим на новую строку перед состоянием башен
    if (printed_output)
    {
        std::cout << "\n";
    }

    // Вывод состояния трех башен
    print_tower(tower1);
    print_tower(tower2);
    print_tower(tower3);

    // Освобождение памяти
    free_all_stacks(tower1, tower2, tower3, input_stack);
    return 0;
}
