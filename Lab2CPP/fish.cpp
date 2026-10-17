// Интерпретатор Fish.

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "stack.h"

// Строка скрипта: символы одного ряда поля
typedef std::vector<Data> CodeLine;

// Поле скрипта: прямоугольная таблица символов по которой движется рыбка
typedef std::vector<CodeLine> Code;

// Любая ошибка в скрипте по описанию языка выдаёт одно и то же сообщение
static const char* FISH_ERROR = "something smells fishy...";

// Снимает значение с вершины стека
static Data pop(Stack& stack)
{
    if (stack.empty())
        throw std::runtime_error(FISH_ERROR);
    const Data value = stack.get();
    stack.pop();
    return value;
}

// Перекладывает все значения из одного стека в другой.
// Порядок значений при этом меняется на обратный.
static void move_all(Stack& from, Stack& to)
{
    while (!from.empty())
    {
        to.push(from.get());
        from.pop();
    }
}

class Fish
{
public:
    Fish(const Code& code, std::istream& input)
        : code_(code), input_(input)
    {
    }

    // Выполняет скрипт до инструкции ';' или до ошибки
    void run();

private:
    Data cell(size_t x, size_t y) const;
    void set_cell(size_t x, size_t y, Data value);
    size_t width() const { return code_.empty() ? 0 : code_[0].size(); }
    size_t height() const { return code_.size(); }

    void move(); // сдвиг рыбки на одну клетку
    void execute(Data command); // выполнение одной инструкции
    void execute_arithmetic(Data command);
    void execute_stack(Data command);

    Code code_;
    std::istream& input_;
    Stack stack_;

    size_t x_ = 0; // положение рыбки
    size_t y_ = 0;
    int dx_ = 1; // направление движения, изначально вправо
    int dy_ = 0;

    Data quote_ = 0; // символ кавычки, если читаем строку
    Data register_ = 0; // регистр инструкции '&'
    bool register_full_ = false;
    bool finished_ = false;
};

// Возвращает символ поля, за границами поля находятся нули
Data Fish::cell(size_t x, size_t y) const
{
    if (y >= height() || x >= width())
        return 0;
    return code_[y][x];
}

// Записывает символ в поле, при необходимости расширяя его
void Fish::set_cell(size_t x, size_t y, Data value)
{
    while (height() <= y)
        code_.push_back(CodeLine(width(), ' '));

    if (width() <= x)
    {
        for (size_t row = 0; row < height(); ++row)
            code_[row].resize(x + 1, ' ');
    }
    code_[y][x] = value;
}

// Сдвигает рыбку в текущем направлении.
// Выйдя за край поля, она появляется с противоположной стороны.
void Fish::move()
{
    if (dx_ > 0)
        x_ = (x_ + 1) % width();
    else if (dx_ < 0)
        x_ = (x_ == 0) ? width() - 1 : x_ - 1;
    else if (dy_ > 0)
        y_ = (y_ + 1) % height();
    else
        y_ = (y_ == 0) ? height() - 1 : y_ - 1;
}

void Fish::execute_arithmetic(Data command)
{
    // операции снимают со стека сначала x, потом y и кладут результат "y op x"
    const Data x = pop(stack_);
    const Data y = pop(stack_);

    switch (command)
    {
    case '+': stack_.push(y + x); break;
    case '-': stack_.push(y - x); break;
    case '*': stack_.push(y * x); break;
    case ',':
    case '%':
        if (x == 0)
            throw std::runtime_error(FISH_ERROR);
        // стек хранит целые числа, поэтому деление тоже целочисленное
        stack_.push(command == ',' ? y / x : y % x);
        break;
    case '=': stack_.push(y == x ? 1 : 0); break;
    case ')': stack_.push(y > x ? 1 : 0); break;
    case '(': stack_.push(y < x ? 1 : 0); break;
    default: throw std::runtime_error(FISH_ERROR);
    }
}

void Fish::execute_stack(Data command)
{
    switch (command)
    {
    case ':': // продублировать вершину
    {
        const Data value = pop(stack_);
        stack_.push(value);
        stack_.push(value);
        break;
    }
    case '~': // удалить вершину
        pop(stack_);
        break;
    case '$': // поменять местами два верхних значения
    {
        const Data a = pop(stack_);
        const Data b = pop(stack_);
        stack_.push(a);
        stack_.push(b);
        break;
    }
    case '@': // сдвинуть три верхних значения: a b c -> c a b
    {
        const Data c = pop(stack_);
        const Data b = pop(stack_);
        const Data a = pop(stack_);
        stack_.push(c);
        stack_.push(a);
        stack_.push(b);
        break;
    }
    case '}': // сдвинуть весь стек вправо: вершина уходит на дно
    {
        const Data top = pop(stack_);
        Stack rest;
        move_all(stack_, rest);
        stack_.push(top);
        move_all(rest, stack_);
        break;
    }
    case '{': // сдвинуть весь стек влево: дно поднимается на вершину
    {
        Stack reversed;
        move_all(stack_, reversed);
        const Data bottom = pop(reversed);
        move_all(reversed, stack_);
        stack_.push(bottom);
        break;
    }
    case 'r': // перевернуть стек
    {
        Stack reversed;
        move_all(stack_, reversed);
        stack_ = reversed;
        break;
    }
    case 'l': // положить на вершину длину стека
    {
        Stack reversed;
        move_all(stack_, reversed);
        Data length = 0;
        while (!reversed.empty())
        {
            stack_.push(reversed.get());
            reversed.pop();
            ++length;
        }
        stack_.push(length);
        break;
    }
    case '&': // обмен значением с регистром
        if (register_full_)
        {
            stack_.push(register_);
            register_full_ = false;
        }
        else
        {
            register_ = pop(stack_);
            register_full_ = true;
        }
        break;
    default:
        throw std::runtime_error(FISH_ERROR);
    }
}

void Fish::execute(Data command)
{
    // В режиме строки символы просто кладутся в стек до закрывающей кавычки
    if (quote_ != 0)
    {
        if (command == quote_)
            quote_ = 0;
        else
            stack_.push(command);
        return;
    }

    switch (command)
    {
    case ' ': // пустая клетка
        break;

        // направление движения
    case '>': dx_ = 1; dy_ = 0; break;
    case '<': dx_ = -1; dy_ = 0; break;
    case 'v': dx_ = 0; dy_ = 1; break;
    case '^': dx_ = 0; dy_ = -1; break;

        // зеркала
    case '/': { const int dx = dx_; dx_ = -dy_; dy_ = -dx; break; }
    case '\\': { const int dx = dx_; dx_ = dy_; dy_ = dx; break; }
    case '|':  dx_ = -dx_; break;
    case '_':  dy_ = -dy_; break;
    case '#':  dx_ = -dx_; dy_ = -dy_; break;
    case 'x': // случайное направление
        switch (std::rand() % 4)
        {
        case 0: dx_ = 1; dy_ = 0; break;
        case 1: dx_ = -1; dy_ = 0; break;
        case 2: dx_ = 0; dy_ = 1; break;
        default: dx_ = 0; dy_ = -1; break;
        }
        break;

    case '!':// пропустить следующую клетку
        move();
        break;
    case '?': // пропустить, если снятое значение равно нулю
        if (pop(stack_) == 0)
            move();
        break;
    case '.': // прыжок в клетку (x, y)
    {
        const Data y = pop(stack_);
        const Data x = pop(stack_);
        if (x < 0 || y < 0)
            throw std::runtime_error(FISH_ERROR);
        x_ = static_cast<size_t>(x);
        y_ = static_cast<size_t>(y);
        break;
    }

    case '\'': // начало строки
    case '"':
        quote_ = command;
        break;

        // арифметика и сравнения
    case '+': case '-': case '*': case ',': case '%':
    case '=': case ')': case '(':
        execute_arithmetic(command);
        break;

        // работа со стеком
    case ':': case '~': case '$': case '@':
    case '}': case '{': case 'r': case 'l': case '&':
        execute_stack(command);
        break;

        // ввод и вывод
    case 'o': // вывести значение как символ
        std::cout << static_cast<char>(pop(stack_));
        break;
    case 'n': // вывести значение как число
        std::cout << pop(stack_);
        break;
    case 'i': // прочитать символ, -1 в конце данных
    {
        const int symbol = input_.get();
        stack_.push(symbol == std::char_traits<char>::eof() ? -1 : symbol);
        break;
    }

    // чтение и запись клеток самого поля
    case 'g':
    {
        const Data y = pop(stack_);
        const Data x = pop(stack_);
        if (x < 0 || y < 0)
            throw std::runtime_error(FISH_ERROR);
        stack_.push(cell(static_cast<size_t>(x), static_cast<size_t>(y)));
        break;
    }
    case 'p':
    {
        const Data y = pop(stack_);
        const Data x = pop(stack_);
        const Data value = pop(stack_);
        if (x < 0 || y < 0)
            throw std::runtime_error(FISH_ERROR);
        set_cell(static_cast<size_t>(x), static_cast<size_t>(y), value);
        break;
    }

    case ';': // конец работы
        finished_ = true;
        break;

    default: // неизвестная инструкция
        if (command >= '0' && command <= '9')
            stack_.push(command - '0');
        else if (command >= 'a' && command <= 'f')
            stack_.push(command - 'a' + 10);
        else
            throw std::runtime_error(FISH_ERROR);
        break;
    }
}

void Fish::run()
{
    if (width() == 0 || height() == 0)
        throw std::runtime_error(FISH_ERROR);

    while (!finished_)
    {
        execute(cell(x_, y_));
        if (!finished_)
            move();
    }
}

// Читает скрипт и дополняет все строки пробелами до одинаковой длины,
// чтобы поле было прямоугольным
static Code read_code(std::istream& input)
{
    Code code;
    size_t width = 0;
    std::string line;

    while (std::getline(input, line))
    {
        if (!line.empty() && line.back() == '\r') // перевод строки в стиле Windows
            line.pop_back();

        CodeLine row;
        for (size_t i = 0; i < line.size(); ++i)
            row.push_back(static_cast<unsigned char>(line[i]));

        if (row.size() > width)
            width = row.size();
        code.push_back(row);
    }

    for (size_t i = 0; i < code.size(); ++i)
        code[i].resize(width, ' ');

    return code;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: Lab2CPPFish <script file> [input file]\n";
        return 1;
    }

    std::ifstream script(argv[1]);
    if (!script)
    {
        std::cerr << "Cannot open file " << argv[1] << "\n";
        return 1;
    }

    // Второй файл с входными данными нужен не каждому скрипту
    std::ifstream data;
    if (argc > 2)
    {
        data.open(argv[2]);
        if (!data)
        {
            std::cerr << "Cannot open file " << argv[2] << "\n";
            return 1;
        }
    }

    try
    {
        Fish fish(read_code(script), data);
        fish.run();
    }
    catch (const std::exception&)
    {
        std::cerr << "\n" << FISH_ERROR << "\n";
        return 1;
    }

    return 0;
}
