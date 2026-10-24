
#include "../LibraryCPPClass/stack.h"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

constexpr int SCALE = 10000;

// Перевод числа в формат стека
Data toData(long double x)
{
    if (!std::isfinite(x))
        throw std::runtime_error("Invalid number");

    long double scaled = std::round(x * SCALE);

    if (scaled < std::numeric_limits<Data>::min() ||
        scaled > std::numeric_limits<Data>::max())
        throw std::runtime_error("Number out of range");

    return static_cast<Data>(scaled);
}

// Проверка, является ли команда числом
bool parseNumber(const std::string &word, Data &result)
{
    try
    {
        std::size_t count = 0;
        long double x = std::stold(word, &count);

        if (count != word.size())
            return false;

        result = toData(x);
        return true;
    }
    catch (const std::invalid_argument &)
    {
        return false;
    }
    catch (const std::out_of_range &)
    {
        throw std::runtime_error("Number out of range");
    }
}

// Получение обычного числа
long double value(Data x)
{
    return static_cast<long double>(x) / SCALE;
}

// Извлечение элемента из стека
Data take(Stack &stack)
{
    Data x = stack.get();
    stack.pop();
    return x;
}

// Форматирование числа для вывода
std::string format(Data x)
{
    long long n = x;
    bool negative = n < 0;

    if (negative)
        n = -n;

    std::ostringstream out;

    if (negative)
        out << '-';

    out << n / SCALE;

    if (n % SCALE != 0)
    {
        std::ostringstream fractional;

        fractional << std::setw(4)
                   << std::setfill('0')
                   << n % SCALE;

        std::string s = fractional.str();

        while (!s.empty() && s.back() == '0')
            s.pop_back();

        out << '.' << s;
    }

    return out.str();
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: Calculon <script.txt> <input.txt>\n";
        return 1;
    }

    std::ifstream script(argv[1]);
    std::ifstream input(argv[2]);

    if (!script || !input)
    {
        std::cerr << "Cannot open script or input file\n";
        return 1;
    }

    try
    {
        std::vector<std::string> commands;
        std::string word;

        while (script >> word)
            commands.push_back(word);

        // Поиск соответствующих cond и end
        std::vector<std::size_t> matchingEnd(
            commands.size(), commands.size()
        );

        std::vector<std::size_t> opened;

        for (std::size_t i = 0; i < commands.size(); ++i)
        {
            if (commands[i] == "cond")
            {
                opened.push_back(i);
            }
            else if (commands[i] == "end")
            {
                if (opened.empty())
                    throw std::runtime_error("Unexpected end");

                matchingEnd[opened.back()] = i;
                opened.pop_back();
            }
        }

        if (!opened.empty())
            throw std::runtime_error("Missing end");

        Stack stack;

        int repeatsLeft = 0;
        std::size_t repeatFrom = commands.size();
        bool firstOutput = true;

        for (std::size_t i = 0; i < commands.size();)
        {
            const std::string &cmd = commands[i];
            Data number = 0;

            // Добавление числа в стек
            if (parseNumber(cmd, number))
            {
                stack.push(number);
            }

            // Чтение входного числа
            else if (cmd == "get")
            {
                long double x;

                if (!(input >> x))
                    throw std::runtime_error("Missing input number");

                stack.push(toData(x));
            }

            // Вывод вершины стека
            else if (cmd == "peek")
            {
                if (!firstOutput)
                    std::cout << ' ';

                std::cout << format(stack.get());
                firstOutput = false;
            }

            // Установка счётчика повторений
            else if (cmd == "setr")
            {
                Data count = take(stack);

                if (count % SCALE != 0)
                    throw std::runtime_error("Non-integer loop count");

                repeatsLeft = count / SCALE;
                repeatFrom = i + 1;
            }

            // Повторение команд
            else if (cmd == "repeat")
            {
                if (repeatFrom == commands.size())
                    throw std::runtime_error("repeat without setr");

                if (repeatsLeft > 0)
                {
                    --repeatsLeft;
                    i = repeatFrom;
                    continue;
                }
            }

            // Арифметические операции
            else if (cmd == "add" || cmd == "sub" ||
                     cmd == "mul" || cmd == "div")
            {
                long double a = value(take(stack));
                long double b = value(take(stack));

                if (cmd == "add")
                {
                    stack.push(toData(a + b));
                }
                else if (cmd == "sub")
                {
                    stack.push(toData(a - b));
                }
                else if (cmd == "mul")
                {
                    stack.push(toData(a * b));
                }
                else
                {
                    if (b == 0)
                        throw std::runtime_error("Division by zero");

                    stack.push(toData(a / b));
                }
            }

            // Квадрат и квадратный корень
            else if (cmd == "sq" || cmd == "sqrt")
            {
                long double a = value(take(stack));

                if (cmd == "sqrt" && a < 0)
                    throw std::runtime_error(
                        "Square root of negative number"
                    );

                stack.push(toData(
                    cmd == "sq" ? a * a : std::sqrt(a)
                ));
            }

            // Условное выполнение
            else if (cmd == "cond")
            {
                Data a = take(stack);

                if (stack.empty())
                    throw std::runtime_error(
                        "cond needs two numbers"
                    );

                if (a == stack.get())
                {
                    stack.pop();
                }
                else
                {
                    i = matchingEnd[i] + 1;
                    continue;
                }
            }

            // Завершение условия
            else if (cmd != "end")
            {
                throw std::runtime_error(
                    "Unknown command: " + cmd
                );
            }

            ++i;
        }

        std::cout << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
