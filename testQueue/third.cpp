#include <iostream>
#include "fstream"
#include "queue.h"
#include "stdlib.h"
using namespace std;

typedef Queue<int> MyQueue;
int main(){
    MyQueue testY, testX;
    const int row = 6, col = 14;
    char arr[row][col];
    int num = 1, num2, num3, num4;
    char *str = new char[1];
    itoa(num, str, 10);
    bool full = true;
    bool imposible = true;
    ifstream file("C:\\Users\\vasya\\OneDrive\\Desktop\\file2.txt");
    if(file.is_open()) {
        while (!file.eof()) {
            for (int i = 0; i < row; ++i) {
                file.getline(arr[i], col + 1, '\n');
            }
        }

        cout << "Intermediate output: " << endl;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                cout << arr[i][j];
            }

            cout << endl;
        } // Промежуточный вывод

        cout << endl << endl;

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (arr[i][j] == 'X' && arr[i - 1][j] == '.') {
                    arr[i - 1][j] = *str;
                }
                if (arr[i][j] == 'X' && arr[i + 1][j] == '.') {
                    arr[i + 1][j] = *str;
                }
                if (arr[i][j] == 'X' && arr[i][j - 1] == '.') {
                    arr[i][j - 1] = *str;
                }
                if (arr[i][j] == 'X' && arr[i][j + 1] == '.') {
                    arr[i][j + 1] = *str;
                }
            }
        } // Отмечает первый шаг с начала пути

        while(full) {
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < col; ++j) {
                    if (arr[i][j] == *str && arr[i - 1][j] == '.') {
                        if(arr[i][j] != *itoa(num + 1, str, 10)) {
                            arr[i - 1][j] = *itoa(num + 1, str, 10);
                            itoa(num, str, 10);
                        }
                    }
                    if (arr[i][j] == *str && arr[i + 1][j] == '.') {
                        if(arr[i][j] != *itoa(num + 1, str, 10)) {
                            arr[i + 1][j] = *itoa(num + 1, str, 10);
                            itoa(num, str, 10);
                        }
                    }
                    if (arr[i][j] == *str && arr[i][j - 1] == '.') {
                        if(arr[i][j] != *itoa(num + 1, str, 10)) {
                            arr[i][j - 1] = *itoa(num + 1, str, 10);
                            itoa(num, str, 10);
                        }
                    }
                    if (arr[i][j] == *str && arr[i][j + 1] == '.') {
                        if(arr[i][j] != *itoa(num + 1, str, 10)) {
                            arr[i][j + 1] = *itoa(num + 1, str, 10);
                            itoa(num, str, 10);
                        }
                    }

                    if (arr[i][j] == 'Y' && arr[i - 1][j] != '.' && arr[i + 1][j] != '.' && arr[i][j - 1] != '.' && arr[i][j + 1] != '.')
                        full = false;
                }
            }
            num = num + 1;
            str = itoa(num, str, 10);
            if(num > 100)
            {
                full = false;
                imposible = false;

            }
        } // Отмечечает число шагов до выхода в лабиринте где несколько путей к выходу

        switch (imposible) {
            case false:
                cout << "IMPOSIBLE!!!";
                break;
            case true:
                cout << "Intermediate output: " << endl;
                for (int i = 0; i < row; ++i) {
                    for (int j = 0; j < col; ++j) {
                        cout << arr[i][j];
                    }

                    cout << endl;
                } // Промежуточный вывод

                cout << endl << endl;

                for (int i = 0; i < row; ++i) {
                    for (int j = 0; j < col; ++j) {
                        if (arr[i][j] == 'Y' && arr[i - 1][j] != '#') {
                            *str = arr[i - 1][j];
                            num = atoi(str);
                        }
                        if (arr[i][j] == 'Y' && arr[i + 1][j] != '#') {
                            *str = arr[i + 1][j];
                            num2 = atoi(str);
                        }
                        if (arr[i][j] == 'Y' && arr[i][j - 1] != '#') {
                            *str = arr[i][j - 1];
                            num3 = atoi(str);
                        }
                        if (arr[i][j] == 'Y' && arr[i][j + 1] != '#') {
                            *str = arr[i][j + 1];
                            num4 = atoi(str);
                        }
                    }

                } // Выводит в переменные последние шаги до выхода

                if (num2 < num)
                    num = num2;
                if (num3 < num)
                    num = num3;
                if (num4 < num)
                    num = num4;

                int y, x;

                for (int i = 0; i < row; ++i) {
                    for (int j = 0; j < col; ++j) {
                        if (arr[i][j] == 'Y' && arr[i][j - 1] == *itoa(num, str, 10)) {
                            x = j - 1;
                            y = i;
                            full = false;
                        }
                        if (arr[i][j] == 'Y' && arr[i - 1][j] == *itoa(num, str, 10)) {
                            x = j;
                            y = i - 1;
                        }
                        if (arr[i][j] == 'Y' && arr[i][j + 1] == *itoa(num, str, 10)) {
                            x = j + 1;
                            y = i;
                        }
                        if (arr[i][j] == 'Y' && arr[i + 1][j] == *itoa(num, str, 10)) {
                            x = j;
                            y = i + 1;
                        }
                    }
                } // Находит координаты последней точки кратчайшего пути

                full = true;
                testY.insert(y);
                testX.insert(x);

                int size = num;

                while (full) {
                    if (arr[y - 1][x] == *itoa(num - 1, str, 10)) {
                        y--;
                        num--;
                        testY.insert(y);
                        testX.insert(x);
                    }
                    if (arr[y + 1][x] == *itoa(num - 1, str, 10)) {
                        y++;
                        num--;
                        testY.insert(y);
                        testX.insert(x);
                    }
                    if (arr[y][x - 1] == *itoa(num - 1, str, 10)) {
                        x--;
                        num--;
                        testY.insert(y);
                        testX.insert(x);
                    }
                    if (arr[y][x + 1] == *itoa(num - 1, str, 10)) {
                        x++;
                        num--;
                        testY.insert(y);
                        testX.insert(x);
                    }
                    if (arr[y][x + 1] == 'X')
                        full = false;
                    if (arr[y][x - 1] == 'X')
                        full = false;
                    if (arr[y - 1][x] == 'X')
                        full = false;
                    if (arr[y + 1][x] == 'X')
                        full = false;
                } // Запоминаем координаты в очередь

                for (int i = 0; i < row; ++i) {
                    for (int j = 0; j < col; ++j) {
                        if (arr[i][j] != '#' && arr[i][j] != 'X' && arr[i][j] != 'Y')
                            arr[i][j] = '.';
                    }
                } // выводит первоначальный лабиринт

                cout << "Intermediate output: " << endl;
                for (int i = 0; i < row; ++i) {
                    for (int j = 0; j < col; ++j) {
                        cout << arr[i][j];
                    }

                    cout << endl;
                } // Промежуточный вывод

                cout << endl << endl;


                for (int i = 0; i < size; ++i) {
                    arr[testY.get()][testX.get()] = 'x';
                    testX.remove();
                    testY.remove();
                }


                cout << "The shortest path: " << endl;
                for (int i = 0; i < row; ++i) {
                    for (int j = 0; j < col; ++j) {
                        cout << arr[i][j];
                    }

                    cout << endl;
                } // Выводит кратчайший путь до выхода
                 break;
        }
    }




    return 0;
}