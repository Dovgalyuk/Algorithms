#include <iostream>
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

    int y = queue_get(queue);
    queue_remove(queue);

    int x = queue_get(queue);
    queue_remove(queue);

    int k = matrix[y][x]; //Записываем в переменную k единицу, которую ранее присвоили элементу по введенным координатам из введенных координат

    checkLeft(matrix, queue, x, y, k);
    checkTop(matrix, queue, x, y,k);
    checkRight(matrix, queue, x, y, M,k);
    checkBottom(matrix, queue, x, y,N,k);

    if (!checkMatrixFill(matrix, M, N)) k = setColors(matrix, queue, M, N);
    else return k;
}

int main()
{
    Queue* queue = queue_create();

    int N, M;

    cout << "Enter count of rows:"; //Количество строк
    cin >> N;

    cout << "Enter count of columns:"; //Количество столбцов
    cin >> M; 

    int** matrix = new int*[N]{0};//Создаем матрицу[N][M]
    for (int i = 0; i < N; i++) matrix[i] = new int[M]{0};

    int xCoordinate, yCoordinate, countOfCoordinates;

    cout << "Enter count of coordinates:";
    cin >> countOfCoordinates;

    for (int i = 0; i < countOfCoordinates; i++)
    {
        cout << "\nEntering " << i + 1 << " coordinate: \n";

        cout << "Enter X coordinate of first element:";
        cin >> xCoordinate;

        cout << "Enter Y coordinate of first element:";
        cin >> yCoordinate;

        checkCoordinate(xCoordinate, yCoordinate, M, N);
        xCoordinate--;//Убавляем у координат еденицу, для работы с матрицей (т.к. по заданию нам необходимо подавать координаты от 1 до M/N)
        yCoordinate--;

        matrix[yCoordinate][xCoordinate] = 1;
        queue_insert(queue, yCoordinate);
        queue_insert(queue, xCoordinate);

        cout << "\n";
    } 

    int k = setColors(matrix, queue, M, N)+1;
    printMatrix(matrix, N, M);
    cout << "\n\nThe board have been painted in " << k << " colors" << "\n";


    //Чистка памяти
    for (int i = 0; i < N; i++) delete matrix[i];
    delete[] matrix;
    queue_delete(queue);

}