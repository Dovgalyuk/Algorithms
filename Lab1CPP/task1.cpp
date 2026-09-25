#include <iostream>
#include <fstream>
#include "array.h"
// Прочитать целое число из файла, создать массив такой размерности и заполнить его числами из файла. 
// В массиве записаны оценки по иностранному языку каждого из учеников класса. 
// Определить количество пятерок, количество четверок, количество троек и количество двоек. Вывести результат на экран или в файл.

Array *array_create_and_read(std::ifstream &input)
{
    int n;
    input >> n;
    Array *arr = array_create(n);
    for (int i = 0; i < n; ++i)
    {
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{
    int count5 = 0, count4 = 0, count3 = 0, count2 = 0;
    for (size_t i = 0; i < array_size(arr); i++)
    {
        int mark = array_get(arr, i);
        if (mark == 5) count5++;
        else if (mark == 4) count4++;
        else if (mark == 3) count3++;
        else if (mark == 2) count2++;
    }
    std::cout << "Grade 5: " << count5 << "\n";
    std::cout << "Grade 4: " << count4 << "\n";
    std::cout << "Grade 3: " << count3 << "\n";
    std::cout << "Grade 2: " << count2 << "\n";
}

int main(int argc, char **argv)
{
    (void)argc;
    std::ifstream input(argv[1]);

    Array *arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    return 0;
}