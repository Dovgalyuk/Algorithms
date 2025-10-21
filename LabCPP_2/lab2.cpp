//     Реализовать в проекте Library модуль vector для массива переменного размера и стек на основе этого модуля (модуль stack).
//     Решить задачу, используя реализованный стек.
//     Добавить пример входных данных и описать тест в CMakeLists.txt, который запускает разработанную программу и использует входные данные.
//     Придумать несколько собственных тестов и также добавить их в CMakeLists.txt.

// Вычислить значение корректного арифметического выражения, использующего операции сложения, вычитания, умножения и деления. 
// Программа должна учитывать приоритет операторов умножения и деления и использовать стек для хранения промежуточных результатов. 
// Операндами в выражении являются неотрицательные целые числа.

// Входные данные
// 1+2*3-1

// Выходные данные
// 6

// Входные данные
// 1*(2+3)

// Выходные данные
// 5

#include <iostream>
#include <fstream>
#include "stack.h"

using namespace std;

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int priority(char op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '~') return 3;
    return 0;
}

string infixToPostfix(string& expression)
{ 
    // Создаем стек для операторов
    Stack *operatorStack = stack_create();
    if(!operatorStack)
    {
        cerr << "Ошибка при создании стека" << endl;
        return "";
    }

    // Создаем строку с постфиксным выражением
    string postfix = "";

    bool isUnaryMinus = false;

    for (size_t i = 0; i < expression.length(); ++i)
    {
        char ch = expression[i];
        if (isspace(ch))
            continue;

        if (ch == '-')
        {
            if (i == 0 || (i > 0 && expression[i-1] == '(')) // Для случая x * (-(a-b))
                isUnaryMinus = true;
            else
                isUnaryMinus = false;
        }

        if (isdigit(ch))
        {
            std::string number(1, ch);
            // Читаем последующие цифры
            while (i + 1 < expression.length() && isdigit(expression[i + 1]))
            {
                number += expression[i + 1];
                ++i;
            }
            postfix += number + ' ';
        }
        else if (ch == '(')
        {
            stack_push(operatorStack, ch);
        }
        else if (ch == ')')
        {
            while (!stack_empty(operatorStack) && stack_get(operatorStack) != '(')
            {
                postfix += stack_get(operatorStack);
                // postfix += ' ';
                stack_pop(operatorStack);
            }
            if (!stack_empty(operatorStack))
                stack_pop(operatorStack);
        }
        else if (isOperator(ch))
        {
            if (ch == '-' && isUnaryMinus)
            {
                stack_push(operatorStack, '~');
                isUnaryMinus = false;
            }
            else
            {
                while (!stack_empty(operatorStack) && priority(stack_get(operatorStack)) >= priority(ch))
                {
                    postfix += stack_get(operatorStack);
                    // postfix += ' ';
                    stack_pop(operatorStack);
                }
                stack_push(operatorStack, ch);
            }
        }
        else
            isUnaryMinus = false;
    }

    while (!stack_empty(operatorStack))
    {
        postfix += stack_get(operatorStack);
        // postfix += ' ';
        stack_pop(operatorStack);
    }

    stack_delete(operatorStack);

    return postfix;
}

double Calc(const string& pfxExpr)
{ 
    Stack *value = stack_create();
    if (!value)
    {
        cerr << "Ошибка создания стека value" << endl;
        return 0;
    }

    size_t i = 0;
    while (i < pfxExpr.size())
    {
        // // Пропускаем пробелы
        // if (isspace(pfxExpr[i])) {
        //     ++i;
        //     continue;
        // }

        // Если число
        if (isdigit(pfxExpr[i]))
        {
            // Читаем число
            size_t start = i;
            while (i < pfxExpr.size() && isdigit(pfxExpr[i]))
                ++i;
            double num = stod(pfxExpr.substr(start, i - start));
            stack_push(value, num);
        }
        //Если оператор
        else if (isOperator(pfxExpr[i]) || pfxExpr[i] == '~')
        {
            if (pfxExpr[i] == '~')
            {
                // Унарный минус: получаем число из стека и меняем знак
                double a = stack_get(value);
                stack_pop(value);
                stack_push(value, -a);
                ++i;
            }
            else
            {
                double a = stack_get(value);
                stack_pop(value);
                double b = stack_get(value);
                stack_pop(value);
                double res;

                switch (pfxExpr[i])
                {
                    case '+': res = b + a; break;
                    case '-': res = b - a; break;
                    case '*': res = b * a; break;
                    case '/': res = b / a; break;
                    default: res = 0; break;
                }
            

                stack_push(value, res);
                ++i;
            }
        }
        // Если неизвестный символ
        else
            ++i;
    }

    double result = stack_get(value);
    stack_delete(value);

    return result;
}


int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Использование: " << argv[0] << " <имя файла>" << endl;
        return 1;
    }
    
    ifstream input (argv[1]);
    if (!input.is_open())
    {
        cerr << "Ошибка открытия файла" << endl;
        return 1;
    }

    string line; // строки с выражениями
    while (getline(input, line))
    {
        if (line.empty()) continue; // пропускаем пустые строки

        string infixExpr = line;
        string postfixExpr = infixToPostfix(infixExpr);
        cout << "Постфиксное выражение: " << postfixExpr << endl;
        cout << "Результат: " << Calc(postfixExpr) << endl;
    }
    return 0;
}
