#include <iostream>
#include <ctime>
#include <climits>
#include "array.h"
using namespace std;

void fill_array(Array* arr) {
    for (int i = 0; i < array_size(arr); i++) {
        array_set(arr, i, rand() % 100 + 1);
    }
}

void sort_array(Array* arr) {
    for (int i = array_size(arr) - 1; i > 0; --i) {
        for (int j = 0; j < i; j++) {
            Data v1 = array_get(arr, j);
            Data v2 = array_get(arr, j + 1);
            if (v1 > v2) {
                array_set(arr, j, v2);
                array_set(arr, j + 1, v1);
            }
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RU");
	srand(time(NULL));
    cout << "Введите размер массива: ";
    int M;
    std::cin >> M;
    
    Array* A = array_create(M);
    fill_array(A);
    int ch = 0;

    for (int i = 1; i < M; i++)
    {
        if ((array_get(A, i - 1) >= 0) != (array_get(A, i) >= 0))
        {
            ch++;
        }
    }

    std::cout << ch;
    
    array_delete(A);
    system("pause");
}
