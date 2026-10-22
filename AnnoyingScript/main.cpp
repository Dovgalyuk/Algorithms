#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include "../LibraryCPPTemplate/stack.h"

using namespace std;


// Читаем файл полностью
string readFile(const string& fileName)
{
    ifstream file(fileName);

    if (!file.is_open())
    {
        throw runtime_error("Не удалось открыть файл: " + fileName);
    }

    string result;
    string line;

    while (getline(file, line))
    {
        result += line;
    }

    return result;
}


// Получить значение после команды
string readValue(
    const string& script,
    size_t& position,
    const vector<string>& variables)
{
    if (position >= script.size())
    {
        return "";
    }

    // Строка в фигурных скобках
    if (script[position] == '{')
    {
        position++;

        string value;

        while (position < script.size() &&
               script[position] != '}')
        {
            value += script[position];
            position++;
        }

        return value;
    }

    // Значение переменной
    if (script[position] == '@')
    {
        position++;

        string number;

        while (position < script.size() &&
               script[position] >= '0' &&
               script[position] <= '9')
        {
            number += script[position];
            position++;
        }

        position--;

        if (number.empty())
        {
            return "";
        }

        int index = stoi(number);

        if (index < 1 ||
            index > static_cast<int>(variables.size()))
        {
            throw runtime_error("Неправильный номер переменной");
        }

        return variables[index - 1];
    }

    // Обычный одиночный символ
    return string(1, script[position]);
}


// Чтение числа после команды
int readNumber(const string& script, size_t& position)
{
    if (position >= script.size())
    {
        throw runtime_error("Не указано число");
    }

    string number;

    // Запись вида {15}
    if (script[position] == '{')
    {
        position++;

        while (position < script.size() &&
               script[position] != '}')
        {
            number += script[position];
            position++;
        }
    }
    else
    {
        while (position < script.size() &&
               script[position] >= '0' &&
               script[position] <= '9')
        {
            number += script[position];
            position++;
        }

        position--;
    }

    if (number.empty())
    {
        throw runtime_error("Ожидалось число");
    }

    return stoi(number);
}


// Пропуск содержимого ? ... |
void skipIf(const string& script, size_t& position)
{
    int level = 1;

    while (position + 1 < script.size() && level > 0)
    {
        position++;

        if (script[position] == '?')
        {
            level++;
        }
        else if (script[position] == '|')
        {
            level--;
        }
    }
}


// Выполнение арифметической операции
string calculate(
    const string& first,
    const string& second,
    char operation)
{
    long long a = stoll(first);
    long long b = stoll(second);

    switch (operation)
    {
        case '+':
            return to_string(a + b);

        case '-':
            return to_string(a - b);

        case '*':
            return to_string(a * b);

        case '/':
            if (b == 0)
            {
                throw runtime_error("Деление на ноль");
            }

            return to_string(a / b);

        case '%':
            if (b == 0)
            {
                throw runtime_error("Деление на ноль");
            }

            return to_string(a % b);

        default:
            throw runtime_error("Неизвестная операция");
    }
}


// Адаптер: использует только push(), get(), pop(), empty()
// из LibraryCPPTemplate/stack.h или Library/stack.h.
// Для операций с нижним элементом временно перекладывает элементы.
class ScriptStack
{
private:
    Stack<string> elements;
    size_t count = 0;

public:
    bool empty() const { return elements.empty(); }
    size_t size() const { return count; }

    void push(const string& value)
    {
        elements.push(value);
        ++count;
    }

    string get() const { return elements.get(); }

    void pop()
    {
        elements.pop();
        --count;
    }

    // Индекс 0 — вершина, как в исходном main.cpp.
    string at(size_t index)
    {
        if (index >= count)
            throw out_of_range("Invalid stack index");

        Stack<string> buffer;
        for (size_t i = 0; i < index; ++i)
        {
            buffer.push(elements.get());
            elements.pop();
        }

        string value = elements.get();

        while (!buffer.empty())
        {
            elements.push(buffer.get());
            buffer.pop();
        }
        return value;
    }

    string bottom()
    {
        if (empty())
            throw out_of_range("Stack is empty");
        return at(count - 1);
    }

    void popBottom()
    {
        if (empty())
            throw out_of_range("Stack is empty");

        Stack<string> buffer;
        // Оставляем нижний элемент в исходном стеке.
        for (size_t i = 1; i < count; ++i)
        {
            buffer.push(elements.get());
            elements.pop();
        }
        elements.pop(); // Удаляем нижний.
        while (!buffer.empty())
        {
            elements.push(buffer.get());
            buffer.pop();
        }
        --count;
    }

    void pushBottom(const string& value)
    {
        Stack<string> buffer;
        while (!elements.empty())
        {
            buffer.push(elements.get());
            elements.pop();
        }
        elements.push(value);
        while (!buffer.empty())
        {
            elements.push(buffer.get());
            buffer.pop();
        }
        ++count;
    }

    void reverse()
    {
        // Извлечённые значения идут от старой вершины к старому дну.
        vector<string> values;
        while (!elements.empty())
        {
            values.push_back(elements.get());
            elements.pop();
        }
        // После добавления в этом же порядке вершина станет прежним дном.
        for (const string& value : values)
            elements.push(value);
    }

    void clear()
    {
        while (!elements.empty())
            elements.pop();
        count = 0;
    }
};

// Печать состояния стека
void printStack(ScriptStack& stack)
{
    cout << "\nSTACK: [";

    for (size_t i = 0; i < stack.size(); i++)
    {
        cout << stack.at(i);

        if (i + 1 < stack.size())
        {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Использование:" << endl;
        cout << "annoying script.txt input.txt" << endl;

        return 1;
    }

    try
    {
        string script = readFile(argv[1]);

        ifstream input(argv[2]);

        if (!input.is_open())
        {
            cout << "Не удалось открыть файл входных данных" << endl;
            return 1;
        }

        ScriptStack stack;

        // Значение регистра ~
        string tilde;

        // Переменные AnnoyingScript
        vector<string> variables;

        srand(static_cast<unsigned int>(time(nullptr)));

        for (size_t i = 0; i < script.size(); i++)
        {
            char command = script[i];

            // + value
            if (command == '+')
            {
                i++;

                string value = readValue(
                    script,
                    i,
                    variables);

                stack.push(value);
            }

            // - удалить нижний элемент
            else if (command == '-')
            {
                if (!stack.empty())
                {
                    stack.popBottom();
                }
            }

            // ~
            else if (command == '~')
            {
                // Команда ~\//
                if (i + 1 < script.size() &&
                    script[i + 1] == '\\')
                {
                    tilde.clear();
                    i++;
                }

                // Команда ~(
                else if (i + 1 < script.size() && script[i + 1] == '(')
                {
                    i += 2;

                    int number = readNumber(script, i);

                    if (number < 1 ||
                        number > static_cast<int>(variables.size()))
                    {
                        throw runtime_error(
                            "Неправильный номер переменной");
                    }

                    tilde = variables[number - 1];
                }

                // Простая команда ~
                else
                {
                    if (!stack.empty())
                    {
                        tilde = stack.bottom();
                    }
                }
            }

            // > вывод
            else if (command == '>')
            {
                if (i + 1 >= script.size())
                {
                    continue;
                }

                i++;

                // Вывод ~
                if (script[i] == '~')
                {
                    cout << tilde;
                }
                else
                {
                    string value = readValue(
                        script,
                        i,
                        variables);

                    cout << value;
                }
            }

            // < переворот
            else if (command == '<')
            {
                stack.reverse();
            }

            // : объединить стек
            else if (command == ':')
            {
                string text;

                for (size_t j = 0;
                     j < stack.size();
                     j++)
                {
                    text += stack.at(j);
                }

                stack.clear();
                stack.push(text);
            }

            // _
            else if (command == '_')
            {
                string line;

                if (getline(input, line))
                {
                    stack.pushBottom(line);
                }
                else
                {
                    stack.pushBottom("");
                }
            }

            // =
            else if (command == '=')
            {
                // =(
                if (i + 1 < script.size() &&
                    script[i + 1] == '(')
                {
                    i += 2;

                    int number = readNumber(script, i);

                    if (number < 1 ||
                        number > static_cast<int>(variables.size()))
                    {
                        throw runtime_error(
                            "Неправильный номер переменной");
                    }

                    variables[number - 1] = tilde;
                }

                // =)
                else if (i + 1 < script.size() &&
                         script[i + 1] == ')')
                {
                    i += 2;

                    int number = readNumber(script, i);

                    if (number < 1 ||
                        number > static_cast<int>(variables.size()))
                    {
                        throw runtime_error(
                            "Неправильный номер переменной");
                    }

                    variables.erase(
                        variables.begin() + number - 1);
                }

                // =
                else
                {
                    variables.push_back(tilde);
                }
            }

            // @ номер переменной -> в стек
            else if (command == '@')
            {
                i++;

                int number = readNumber(script, i);

                if (number < 1 ||
                    number > static_cast<int>(variables.size()))
                {
                    throw runtime_error(
                        "Неправильный номер переменной");
                }

                stack.push(variables[number - 1]);
            }

            // $
            else if (command == '$')
            {
                i++;

                int maximum = readNumber(script, i);

                if (maximum <= 0)
                {
                    throw runtime_error(
                        "Неправильная граница случайного числа");
                }

                int number = rand() % maximum + 1;

                stack.push(to_string(number));
            }

            // &
            else if (command == '&')
            {
                if (stack.size() < 2)
                {
                    throw runtime_error(
                        "Недостаточно элементов для операции");
                }

                i++;

                char operation;

                // Оператор находится в переменной
                if (script[i] == '@')
                {
                    i++;

                    int number = readNumber(script, i);

                    if (number < 1 ||
                        number > static_cast<int>(variables.size()))
                    {
                        throw runtime_error(
                            "Неправильный номер переменной");
                    }

                    if (variables[number - 1].empty())
                    {
                        throw runtime_error(
                            "Пустой оператор");
                    }

                    operation = variables[number - 1][0];
                }
                else
                {
                    operation = script[i];
                }

                string second = stack.bottom();
                stack.popBottom();

                string first = stack.bottom();
                stack.popBottom();

                string result =
                    calculate(first, second, operation);

                stack.pushBottom(result);
            }

            // ?
            else if (command == '?')
            {
                bool notEqual = false;

                if (i + 1 < script.size() &&
                    script[i + 1] == '!')
                {
                    notEqual = true;
                    i++;
                }

                i++;

                string value = readValue(
                    script,
                    i,
                    variables);

                bool condition;

                if (notEqual)
                {
                    condition = (tilde != value);
                }
                else
                {
                    condition = (tilde == value);
                }

                if (!condition)
                {
                    skipIf(script, i);
                }
            }

            // |
            else if (command == '|')
            {
                // конец условного блока
            }

            // !
            else if (command == '!')
            {
                i++;

                int position = readNumber(script, i);

                if (position < 1 ||
                    position > static_cast<int>(script.size()))
                {
                    throw runtime_error(
                        "Неправильная позиция перехода");
                }

                // Позиции AnnoyingScript считаем с 1
                i = position - 2;
            }

            // ;
            else if (command == ';')
            {
                i++;

                int seconds = readNumber(script, i);

                this_thread::sleep_for(
                    chrono::seconds(seconds));
            }

            // ^
            else if (command == '^')
            {
                // ANSI очистка терминала
                cout << "\033[2J\033[1;1H";
            }

            // #
            else if (command == '#')
            {
                break;
            }
        }

        printStack(stack);
    }
    catch (const exception& error)
    {
        cout << "Ошибка: "
             << error.what()
             << endl;

        return 1;
    }

    return 0;
}
