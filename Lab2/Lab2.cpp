#include "stack.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int particles, cord;
    Stack* stack = stack_create();
    char charge;
    //Открываем файл для чтения
    ifstream fin("input.txt");
    //Вводим количество частиц
    fin >> particles;
    for (int i = 0; i < particles; i++)
    {
        //Вводим координату частицы
        fin >> cord;
        //Вводим заряд
        fin >> charge;
        //Если заряд положительный, помещаем в стэк
        if (charge == '+')
        {
            stack_push(stack, cord);
        }
        //Иначе, если заряд отрицательный и стэк не пустой, выводим элемент стэка и тот, который ввели только что
        else if (!stack_empty(stack))
        {
            cout << stack_get(stack) << " " << cord<<endl;
        }
    }
    //Закрываем файл для чтения
    fin.close();
    //Удаляем стэк
    stack_delete(stack);
}
