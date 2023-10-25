#include <iostream>
#include <cstdlib>
#include <cstring>
#include "stack.h"

int main() {
    Stack* stack = stack_create();

    char input[1000];
    std::cin.getline(input, sizeof(input));
    char* token = std::strtok(input, " ");

    while (token != nullptr) {
        if (std::isdigit(token[0]) || (token[0] == '-' && std::isdigit(token[1]))) {
            Data num = std::atoi(token);
            stack_push(stack, num);
        } else {
            if (std::strcmp(token, "+") == 0) {
                // сложение
                Data a = stack_get(stack);
                stack_pop(stack);
                Data b = stack_get(stack);
                stack_pop(stack);
                stack_push(stack, a + b);
            } else if (std::strcmp(token, "-") == 0) {
                // вычитание
                Data a = stack_get(stack);
                stack_pop(stack);
                Data b = stack_get(stack);
                stack_pop(stack);
                stack_push(stack, b - a);
            } else if (std::strcmp(token, "*") == 0) {
                // умножение
                Data a = stack_get(stack);
                stack_pop(stack);
                Data b = stack_get(stack);
                stack_pop(stack);
                stack_push(stack, a * b);
            } else if (std::strcmp(token, "/") == 0) {
                // деление
                Data a = stack_get(stack);
                stack_pop(stack);
                Data b = stack_get(stack);
                stack_pop(stack);
                if (a != 0) {
                    stack_push(stack, b / a);
                } else {
                    std::cerr << "Ошибка: деление на ноль" << std::endl;
                    return 1;
                }
            } else if (std::strcmp(token, "%") == 0) {
                // остаток от деления
                Data a = stack_get(stack);
                stack_pop(stack);
                Data b = stack_get(stack);
                stack_pop(stack);
                if (a != 0) {
                    stack_push(stack, b % a);
                } else {
                    std::cerr << "Ошибка: деление на ноль" << std::endl;
                    return 1;
                }
            } else if (std::strcmp(token, "dup") == 0) {
                // дублирование верхнего элемента стека
                Data top = stack_get(stack);
                stack_push(stack, top);
            } else if (std::strcmp(token, "drop") == 0) {
                // удаление верхнего элемента стека
                stack_pop(stack);
            } else if (std::strcmp(token, "swap") == 0) {
                // обмен двух верхних элементов стека
                Data a = stack_get(stack);
                stack_pop(stack);
                Data b = stack_get(stack);
                stack_pop(stack);
                stack_push(stack, a);
                stack_push(stack, b);
            } else if (std::strcmp(token, "over") == 0) {
                // добавление элемента под вершиной стека в стек
                Data second = stack_get(stack);
                stack_pop(stack);
                Data top = stack_get(stack);
                stack_push(stack, second);
                stack_push(stack, top);
            } else if (std::strcmp(token, "rot") == 0) {
                // перемещение "по кругу" верхних трех элементов стека
                Data a = stack_get(stack);
                stack_pop(stack);
                Data b = stack_get(stack);
                stack_pop(stack);
                Data c = stack_get(stack);
                stack_pop(stack);
                stack_push(stack, b);
                stack_push(stack, a);
                stack_push(stack, c);
            } else if (std::strcmp(token, ".") == 0) {
                // вывод верхнего элемента стека
                Data top = stack_get(stack);
                std::cout << top << std::endl;
                stack_pop(stack);
            } else {
                std::cerr << "Ошибка: неизвестная команда " << token << std::endl;
                return 1;
            }
        }

        token = std::strtok(nullptr, " ");
    }

    stack_delete(stack);
    return 0;
}