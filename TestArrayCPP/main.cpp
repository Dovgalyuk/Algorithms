#include <iostream>
#include <stack.h>  // подключаем библиотеку для 
// использования стека
#include <fstream>
std::ifstream fileln;
fileln.open("output.txt");
using namespase std;

int main()
{
   
  
        setlocale(LC_ALL, "rus");
        char buff[50];//промежуточные
         else
    {
    fin >> buff; // считали первое слово из файла
    cout << buff << endl; // напечатали это слово

    fin.getline(buff, 50); // считали строку из файла
    fin.close(); // закрываем файл
    cout << buff << endl; // напечатали эту строку
    }











        stack <int> steck;  // создаем стек

        int i = 0;

        

            steck.push(a);  // добавляем введенные числа
            i++;
        }

        if (steck.empty()) cout << "Стек не пуст";  // проверяем пуст ли стек (нет)

        cout << "Верхний элемент стека: " << steck.top() << endl; // выводим верхний элемент
        cout << "Давайте удалим верхний элемент " << endl;

        steck.pop();  // удаляем верхний элемент

        cout << "А это новый верхний элемент: " << steck.top(); // выводим уже новый
                                                                // верхний элемент 
        system("pause");
        return 0;
    }
}
