#include <algorithm>
#include <clocale>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "stack.h"
using namespace std;

// координаты текущей команды на двумерном поле
struct Point
{
    int x;
    int y;
};

// направление движения указателя команд
// dx по горизонтали dy по вертикали.
struct Direction
{
    int dx;
    int dy;
};

// чтение файла, возвращает его содержимое в виде строки
static string read_file(const string &filename)
{
    ifstream file(filename);

    if (!file)
    {
        throw runtime_error(
            "Ошибка открытия файла: " + filename
        );
    }

    ostringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

// преобразование текста скрипта в двумерное поле

// каждая строка файла становится строкой поля
// все строки дополняются пробелами до одинаковой длины, чтобы к любому символу можно было обратиться по координатам
static vector<string> make_grid(const string &source)
{
    vector<string> grid;
    stringstream input(source);
    string line;

    // Читаем скрипт построчно.
    while (getline(input, line))
    {
        // Удаляем символ '\r', который может появиться
        // в Windows-файлах с переносами строк \r\n.
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        grid.push_back(line);
    }

    // если файл пустой то создается поле из одной пустой строки
    if (grid.empty())
        grid.push_back("");

    // длина самой длинной строки
    size_t width = 0;

    for (const string &row : grid)
        width = max(width, row.size());

    // минимальная ширина поля - один символ
    if (width == 0)
        width = 1;

    // заполнение коротких строк пробелами
    for (string &row : grid)
        row.resize(width, ' ');

    return grid;
}

// установка направления движения указателя команд
static void set_direction(
    Direction &direction,
    char command
)
{
    switch (command)
    {
    case '>':
        direction = {1, 0};
        break;

    case '<':
        direction = {-1, 0};
        break;

    case '^':
        direction = {0, -1};
        break;

    case 'v':
        direction = {0, 1};
        break;

    default:
        break;
    }
}

// изменение направления движения при встрече с символом '/' и '\'
static void mirror_slash(Direction &direction)
{
    const int old_dx = direction.dx;

    direction.dx = -direction.dy;
    direction.dy = -old_dx;
}
static void mirror_backslash(Direction &direction)
{
    const int old_dx = direction.dx;

    direction.dx = direction.dy;
    direction.dy = old_dx;
}

// возврат верхнего элемента стека, его удаление
static Data pop_value(Stack *stack)
{
    return stack_pop(stack);
}

// возврат количества элементов стека
static size_t get_stack_size(Stack *stack)
{
    size_t count = 0;
    vector<Data> temporary;

    while (!stack_empty(stack))
    {
        temporary.push_back(stack_pop(stack));
        ++count;
    }

    // восстановление исходного порядока элементов
    for (auto iterator = temporary.rbegin();
         iterator != temporary.rend();
         ++iterator)
    {
        stack_push(stack, *iterator);
    }

    return count;
}

// выполнение арифметической или логической операции
static void binary_operation(
    Stack *stack,
    char operation
)
{
    const Data right = pop_value(stack);
    const Data left = pop_value(stack);

    switch (operation)
    {
    case '+':
        stack_push(stack, left + right);
        break;

    case '-':
        stack_push(stack, left - right);
        break;

    case '*':
        stack_push(stack, left * right);
        break;

    case ',':
        if (right == 0)
            throw runtime_error("Ошибка: деление на ноль");

        stack_push(stack, left / right);
        break;

    case '%':
        if (right == 0)
        {
            throw runtime_error(
                "Ошибка: деление по модулю на ноль"
            );
        }

        stack_push(stack, left % right);
        break;

    case '=':
        stack_push(
            stack,
            static_cast<Data>(left == right ? 1 : 0)
        );
        break;

    case ')':
        stack_push(
            stack,
            static_cast<Data>(left > right ? 1 : 0)
        );
        break;

    case '(':
        stack_push(
            stack,
            static_cast<Data>(left < right ? 1 : 0)
        );
        break;

    default:
        throw runtime_error(
            "Ошибка: неизвестная арифметическая операция"
        );
    }
}

// разворот порядока элементов стека
static void reverse_stack(Stack *stack)
{
    const size_t count = get_stack_size(stack);
    vector<Data> values;

    for (size_t i = 0; i < count; ++i)
        values.push_back(pop_value(stack));

    for (Data value : values)
        stack_push(stack, value);
}

// циклический сдвиг эдементов стека влево
static void rotate_left(Stack *stack)
{
    const size_t count = get_stack_size(stack);

    if (count < 2)
        return;

    vector<Data> values(count);

    for (size_t i = 0; i < count; ++i)
        values[i] = pop_value(stack);

    reverse(values.begin(), values.end());

    rotate(
        values.begin(),
        values.begin() + 1,
        values.end()
    );

    for (Data value : values)
        stack_push(stack, value);
}

// циклический сдвиг элементов стека вправо
static void rotate_right(Stack *stack)
{
    const size_t count = get_stack_size(stack);

    if (count < 2)
        return;

    vector<Data> values(count);

    for (size_t i = 0; i < count; ++i)
        values[i] = pop_value(stack);

    reverse(values.begin(), values.end());

    rotate(
        values.begin(),
        values.end() - 1,
        values.end()
    );

    for (Data value : values)
        stack_push(stack, value);
}

// выполнение скрипта Fish
// grid - двумерное поле команд
// input - содержимое входного файла
static void execute(
    vector<string> grid,
    const string &input
)
{
    // создание стека
    Stack *stack = stack_create();

    // начальная позиция - верхний левый угол
    Point position{0, 0};

    // по умолчанию движение идёт вправо
    Direction direction{1, 0};

    bool string_mode = false;
    char string_delimiter = '\0';

    // позиция следующего символа во входном файле
    size_t input_position = 0;

    // генератор случайных чисел для команды x
    mt19937 generator(1);
    uniform_int_distribution<int> random_direction(0, 3);

    const int height =
        static_cast<int>(grid.size());

    const int width =
        static_cast<int>(grid[0].size());

    // ограничение для защиты от бесконечных циклов в неправильных программах Fish
    constexpr size_t max_steps = 1'000'000;

    try
    {
        for (size_t step = 0;
             step < max_steps;
             ++step)
        {
            // получение текущей команды
            const char command = grid[position.y][position.x];

            // строковом режиме каждый символ помещается в стек как числовой код
            if (string_mode)
            {
                if (command == string_delimiter)
                {
                    // закрывающая кавычка завершает строковый режим
                    string_mode = false;
                }
                else
                {
                    stack_push(
                        stack,
                        static_cast<Data>(
                            static_cast<unsigned char>(command)
                        )
                    );
                }
            }
            // открывающая кавычка или \ включает строковый режим
            else if (command == '"' || command == '\'')
            {
                string_mode = true;
                string_delimiter = command;
            }
            // цифры помещаются в стек как числа от 0 до 9
            else if (command >= '0' && command <= '9')
            {
                stack_push(
                    stack,
                    static_cast<Data>(command - '0')
                );
            }
            // буквы a-f используются как числа 10-15
            else if (command >= 'a' && command <= 'f')
            {
                stack_push(
                    stack,
                    static_cast<Data>(command - 'a' + 10)
                );
            }
            else
            {
                switch (command)
                {
                case ' ':
                    break;

                // изменение направления движения
                case '>':
                case '<':
                case '^':
                case 'v':
                    set_direction(direction, command);
                    break;

                // отражение направления
                case '/':
                    mirror_slash(direction);
                    break;

                case '\\':
                    mirror_backslash(direction);
                    break;

                // '_' меняет горизонтальное направление при вертикальном движении
                case '_':
                    if (direction.dy != 0)
                        direction.dx = -direction.dx;
                    break;

                // '|' меняет вертикальное направление при горизонтальном движении
                case '|':
                    if (direction.dx != 0)
                        direction.dy = -direction.dy;
                    break;

                // разворот на 180 градусов
                case '#':
                    direction.dx = -direction.dx;
                    direction.dy = -direction.dy;
                    break;

                // случайное направление
                case 'x':
                {
                    const int value =
                        random_direction(generator);

                    if (value == 0)
                        direction = {1, 0};
                    else if (value == 1)
                        direction = {-1, 0};
                    else if (value == 2)
                        direction = {0, 1};
                    else
                        direction = {0, -1};

                    break;
                }

                // пропуск следующей команды
                case '!':
                    position.x += direction.dx;
                    position.y += direction.dy;
                    break;

                // если верхний элемент равен нулю, пропуск следующей команды
                case '?':
                    if (pop_value(stack) == 0)
                    {
                        position.x += direction.dx;
                        position.y += direction.dy;
                    }

                    break;

                // арифметические и логические операции
                case '+':
                case '-':
                case '*':
                case ',':
                case '%':
                case '=':
                case ')':
                case '(':
                    binary_operation(stack, command);
                    break;

                // дублирование верхнего элемента стека
                case ':':
                    stack_push(stack, stack_get(stack));
                    break;

                // удаление верхнего элемента стека
                case '~':
                    pop_value(stack);
                    break;

                // обмен двух верхних элементов стека
                case '$':
                {
                    const Data first = pop_value(stack);
                    const Data second = pop_value(stack);

                    stack_push(stack, first);
                    stack_push(stack, second);

                    break;
                }

                // перестановка трёх верхних элементов стека
                case '@':
                {
                    const Data first = pop_value(stack);
                    const Data second = pop_value(stack);
                    const Data third = pop_value(stack);

                    stack_push(stack, second);
                    stack_push(stack, first);
                    stack_push(stack, third);

                    break;
                }

                // циклический сдвиг стека влево
                case '{':
                    rotate_left(stack);
                    break;

                // циклический сдвиг стека вправо
                case '}':
                    rotate_right(stack);
                    break;

                // разворот всего стека
                case 'r':
                    reverse_stack(stack);
                    break;

                // помещение размера стека в стек
                case 'l':
                    stack_push(
                        stack,
                        static_cast<Data>(
                            get_stack_size(stack)
                        )
                    );
                    break;

                // чтение одного символа из входного файла
                case 'i':
                    if (input_position >= input.size())
                    {
                        // если вход закончился, то в стек помещается значение -1
                        stack_push(
                            stack,
                            static_cast<Data>(-1)
                        );
                    }
                    else
                    {
                        // чтение одного символа и помещение его кода в стек
                        stack_push(
                            stack,
                            static_cast<Data>(
                                static_cast<unsigned char>(
                                    input[input_position++]
                                )
                            )
                        );
                    }

                    break;

                // вывод символа
                case 'o':
                {
                    const Data value = pop_value(stack);

                    cout << static_cast<char>(value);
                    break;
                }

                // вывод числа
                case 'n':
                    cout << pop_value(stack);
                    break;

                // завершение программы
                case ';':
                    stack_delete(stack);
                    return;

                default:
                    throw runtime_error(
                        string(
                            "Ошибка: неизвестная инструкция: "
                        ) + command
                    );
                }
            }

            // после выполнения команды указатель перемещается в текущем направлении
            position.x += direction.dx;
            position.y += direction.dy;

            // при выходе за левую или правую границу указатель появляется с противоположной стороны
            if (position.x < 0) position.x = width - 1;

            if (position.x >= width) position.x = 0;

            // при выходе за верхнюю или нижнюю границу указатель появляется с противоположной стороны
            if (position.y < 0) position.y = height - 1;

            if (position.y >= height) position.y = 0;
        }

        throw runtime_error(
            "Превышено максимальное количество шагов"
        );
    }
    catch (...)
    {
        // освобождение памяти под стек при возникновении ошибки
        stack_delete(stack);
        throw;
    }
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    if (argc != 3)
    {
        cerr << "Ошибка: необходимо указать два файла.\n";
        return 1;
    }

    try
    {
        const string script = read_file(argv[1]);
        const string input = read_file(argv[2]);

        // создание двумерного поля и запуск интерпретатора
        execute(
            make_grid(script),
            input
        );
    }
    catch (const exception &error)
    {
        cerr << "Ошибка выполнения программы: " << error.what() << '\n';
        return 1;
    }

    return 0;
}