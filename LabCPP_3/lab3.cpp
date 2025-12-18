// Реализовать в проекте Library односвязный список (модуль list) и очередь на основе этого списка (модуль queue).
// Решить задачу, используя реализованную очередь.
// Добавить пример входных данных и описать тест в CMakeLists.txt, который запускает разработанную программу и использует входные данные.

// На шахматной доске построен лабиринт и задана позиция шахматного коня.
// Найти кратчайший путь коня в целевую точку.

// Позиция коня обозначена буквой 'K', выход буквой 'E', а препятствие символом '#'.
// Вывести такую же доску с клетками, пронумерованными в порядке их посещения.

// Входные данные

// K.######
// ..#E....
// ..#.....
// ..#.###.
// ..#.....
// .....###
// .#####..
// ##......

// Выходные данные

// 0.######
// ..#2....
// .1#.....
// ..#.###.
// ..#.....
// .....###
// .#####..
// ##......

#include <iostream>
#include <fstream>
#include "queue.h"

using namespace std;

const int BOARD_SIZE = 8;
const int BOARD_AREA = BOARD_SIZE * BOARD_SIZE;

// Создает очередь с возможными ходами коня из данной клетки
Queue *getKnightMoves(int startPos, bool obstacles[])
{
    Queue *q = queue_create();

    int moves[8][2] = {{1,2}, {2,1}, {-1,2}, {-2,1}, {1,-2}, {2,-1}, {-1,-2}, {-2,-1}};

    for (int i=0; i<8; i++)
    {
        int dx = moves[i][0];
        int dy = moves[i][1];
        int newX = (startPos % 8) + dx;
        int newY = (startPos / 8) + dy;
        if (newX>=0 && newX<8 && newY>=0 && newY<8)
        {
            int newPos = newY*8 + newX;
            if (!obstacles[newPos])
                queue_insert(q, newPos);
        }
    }

    return q;
}

// Восстановливает путь
void reconstructPath(int start, int end, int *parents, int *path, int &pathLen)
{
    int current = end;
    int idx = 0;

    while (current != -1)
    {
        path[idx++] = current;
        current = parents[current];
    }

    // реверсируем
    for (int i=0; i<idx/2; i++)
    {
        int tmp = path[i];
        path[i] = path[idx - 1 - i];
        path[idx - 1 - i] = tmp;
    }
    pathLen = idx;
}

// Считывает поле из файла
string createField(ifstream &file)
{
    if (!file)
    {
        cerr << "Ошибка считывания файла" << endl;
        return "";
    }

    string field;
    string line;

    while (getline(file, line))
        field += line;

    return field;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Использование: " << argv[0] << " <имя файла>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open())
    {
        cerr << "Ошибка открытия файла" << endl;
        return 1;
    }

    string fieldStr = createField(input);
    input.close();

    int startPos = -1;
    int endPos = -1;
    bool obstacles[BOARD_AREA] = {};
    char symbols[BOARD_AREA];

    // Анализируем строку и заполняем массив
    for (int i=0; i<BOARD_AREA; i++)
    {
        char c = fieldStr[i];
        symbols[i] = c;
        if (c == '#')
            obstacles[i] = true;
        else if (c == 'K')
            startPos = i;
        else if (c == 'E')
            endPos = i;
    }

    if (startPos == -1 || endPos == -1)
    {
        cerr << "Не найдена стартовая позиция или выход (K или E)." << endl;
        return 1;
    }

    // Переменные для BFS
    int parents[BOARD_AREA];
    for (int i=0; i<BOARD_AREA; i++)
        parents[i] = -1;

    bool visited[BOARD_AREA] = {}; // -

    // Очередь BFS
    Queue *q = queue_create();
    queue_insert(q, startPos);
    visited[startPos] = true; // -
    parents[startPos] = -1;
    int path[BOARD_AREA];
    int pathLen = 0;
    bool found = false;

    // BFS поиск
    while (!queue_empty(q))
    {
        int current = queue_get(q);
        queue_remove(q);
        if (current == endPos)
        {
            // нашли путь
            reconstructPath(startPos, endPos, parents, path, pathLen);
            found = true;
            break;
        }

        Queue *movesQ = getKnightMoves(current, obstacles);

        while (!queue_empty(movesQ))
        {
            int nextPos = queue_get(movesQ);
            queue_remove(movesQ);
            if (!visited[nextPos]) // проверка parent
            {
                visited[nextPos] = true; // -
                parents[nextPos] = current;
                queue_insert(q, nextPos);
            }
        }
        queue_delete(movesQ);
    }

    // Вывод результата
    int pathVisitNumbers[BOARD_AREA];
    for (int i=0; i<BOARD_AREA; i++)
        pathVisitNumbers[i] = -1;

    if (found)
    {
        for (int i=0; i<pathLen; i++)
        {
            int idx = path[i];
            pathVisitNumbers[idx] = i; // номера посещений с 0, включительно
        }
    }

    // Вывод доски
    cout << "Доска с порядком ходов:\n";
    for (int y=0; y<8; y++)
    {
        for (int x=0; x<8; x++)
        {
            int idx = y*8 + x;
            if (symbols[idx] == '#')
                cout << symbols[idx];
            else if (pathVisitNumbers[idx] != -1)
                cout << pathVisitNumbers[idx];
            else
                cout << '.'; // не посещена
        }
        cout << endl;
    }

    queue_delete(q);
    return 0;
}