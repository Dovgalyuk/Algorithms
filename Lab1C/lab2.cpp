#include <iostream>
#include <string>
#include <fstream> //для работы с файлами

#include "stack.h"

using namespace std;

bool brackets(const string& in) {
    Stack* stack = stack_create();//создание стека

    for (char b : in) { //итерация по каждому символу из ввода
        if (b == '(' || b == '[' || b == '{' || b == '<') {
            stack_push(stack, b);//добавление открывающей скобки в стек
        }
        else if (b == ')' || b == ']' || b == '}' || b == '>') {
            if (stack_empty(stack)) {
                stack_delete(stack);
                return false;//если стек пуст и встретилась закрывающая скобка, то послед-ть неправильная
            }

            char b2 = stack_get(stack);//получение откр скобки из стека
            stack_pop(stack);//удаление откр скобки из стека

            if (!((b == ')' && b2 == '(') ||
                (b == ']' && b2 == '[') ||
                (b == '}' && b2 == '{') ||
                (b == '>' && b2 == '<'))) {
                stack_delete(stack);
                return false;//если закр скобка не соотв-ет последней откр, то посл-ть неправ-я
            }
        }
    }

    bool res = stack_empty(stack);//проверка, пуст ли стек после прохода
    stack_delete(stack);//освобождение памяти

    return res;
}

bool check(const string& input) {
    //проверка ввода на допустимые символы
    for (char ch : input) {
        if (!(ch == '(' || ch == ')' || 
            ch == '[' || ch == ']' || 
            ch == '{' || ch == '}' || 
            ch == '<' || ch == '>')) {
            return false;
        }
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "ru");
    string in;
    do {
        cout << "Введите последовательность скобок: ";
        cin >> in;

        if (!check(in)) {
            cout << "Некорректный ввод. Допустимые символы для ввода: () [] {} <>. Повторите ввод." << endl;
        }
    } while (!check(in));

    if (brackets(in)) {
        cout << "Последовательность правильная." << endl;
    }
    else {
        cout << "Последовательность неправильная." << endl;
    }

    ofstream output("output.txt");

    if (!output.is_open()) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return 1;
    }

    if (brackets(in)) {
        output << "YES" << endl;
    }
    else {
        output << "NO" << endl;
    }

    output.close();

    return 0;
}
