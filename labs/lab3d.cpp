#include <iostream>
#include <fstream>
#include <string>
#include "vector.h"
#include "queue.h"
using namespace std;

bool checkCoordinate(int x, int y, int M, int N) {
    if (x >= 1 && x <= M) {
        if (y >= 1 && y <= N) {
            return true;
        }
        else {
            cout << "\n\n Error: You have entered wrong y-coordinate";
            throw "Wrong y-coordinate";
        }
    }
    else {
        cout << "\n\n Error: You have entered wrong x-coordinate";
        throw "Wrong x-coordinate";
    }
}
void printMatrix(int** matrix, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
        {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
}

void checkLeft(int** matrix, Queue* queue, int x, int y, int k) {
    x--;
    if (x >= 0 && matrix[y][x] == 0) {
        matrix[y][x] = k + 1;
        queue_insert(queue, y);
        queue_insert(queue, x);
    }
}
void checkTop(int** matrix, Queue* queue, int x, int y, int k) {
    y--;
    if (y >= 0 && matrix[y][x] == 0) {
        matrix[y][x] = k+1;
        queue_insert(queue, y);
        queue_insert(queue, x);
    }
}
void checkRight(int** matrix, Queue* queue, int x, int y, int M, int k) {
    x++;
    if (x < M && matrix[y][x] == 0) {
        matrix[y][x] = k + 1;
        queue_insert(queue, y);
        queue_insert(queue, x);
    }
}
void checkBottom(int** matrix, Queue* queue, int x, int y, int N, int k) {
    y++;
    if (y < N && matrix[y][x] == 0) {
        matrix[y][x] = k + 1;
        queue_insert(queue, y);
        queue_insert(queue, x);
    }
}
bool checkMatrixFill(int** matrix, int M, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
        {
            if (matrix[i][j] == 0) return false;
        }
    }
    return true;
}
int setColors(int** matrix, Queue* queue, int M, int N) {

    int k = 0;

    while (!checkMatrixFill(matrix, M, N))
    {
        int y = queue_get(queue);
        queue_remove(queue);

        int x = queue_get(queue);
        queue_remove(queue);

        k = matrix[y][x]; //Записываем в переменную k единицу, которую ранее присвоили элементу по введенным координатам из введенных координат

        checkLeft(matrix, queue, x, y, k);
        checkTop(matrix, queue, x, y, k);
        checkRight(matrix, queue, x, y, M, k);
        checkBottom(matrix, queue, x, y, N, k);
    }

    return k;
}

int main()
{
    Queue* queue = queue_create();

    int N, M;
    int xCoordinate, yCoordinate;

    string pathToFile;
    cout << "Enter path to .txt file:";
    getline(cin, pathToFile);

    ifstream file(pathToFile);

    if (!file.is_open()) {
        cout << "You entered the wrong path";
        throw "You entered the wrong path";
    }
    else {
        file >> N;
        file >> M;

        int** matrix = new int* [N] {0};//Создаем матрицу[N][M]
        for (int i = 0; i < N; i++) matrix[i] = new int[M] {0};

        while (!file.eof()) {
            file >> xCoordinate;
            file >> yCoordinate;

            checkCoordinate(xCoordinate, yCoordinate, M, N);
            xCoordinate--;//Убавляем у координат единицу, для работы с матрицей (т.к. по заданию нам необходимо подавать координаты от 1 до M/N)
            yCoordinate--;

            matrix[yCoordinate][xCoordinate] = 1;
            queue_insert(queue, yCoordinate);
            queue_insert(queue, xCoordinate);
        }

        int k = 0;

        k = setColors(matrix, queue, M, N) + 1;

        printMatrix(matrix, N, M);
        cout << "\n\nThe board have been painted in " << k << " colors" << "\n";

        //Чистка памяти
        for (int i = 0; i < N; i++) delete[] matrix[i];
        delete[] matrix;
        queue_delete(queue);
    }
    
}