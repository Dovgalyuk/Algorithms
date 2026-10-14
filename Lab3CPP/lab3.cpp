#include <fstream>
#include <iostream>
#include <string>
#include "queue.h"

using namespace std;

const int MAXN = 200;

int rows = 0;
int cols = 0;
char grid[MAXN][MAXN];
int dist[MAXN][MAXN];
int parent[MAXN][MAXN]; // хранит позицию предыдущей клетки (r * cols + c)

// 8 возможных направлений хода ферзя
const int dr[8] = { -1, -1, -1,  0,  0,  1,  1,  1 };
const int dc[8] = { -1,  0,  1, -1,  1, -1,  0,  1 };


// Поиск в ширину (волновой алгоритм)
void bfs(int start_r, int start_c)
{
    Queue* q = queue_create();

    dist[start_r][start_c] = 0;
    parent[start_r][start_c] = -1;
    queue_insert(q, start_r * cols + start_c);

    while (!queue_empty(q))
    {
        int pos = queue_get(q);
        queue_remove(q);

        int r = pos / cols;
        int c = pos % cols;

        // Пробуем все 8 направлений
        for (int d = 0; d < 8; d++)
        {
            int nr = r + dr[d];
            int nc = c + dc[d];

            // Идём по лучу, пока не упрёмся в стену или край поля
            while (nr >= 0 && nr < rows &&
                nc >= 0 && nc < cols &&
                grid[nr][nc] != '#')
            {
                if (dist[nr][nc] == -1) // клетка ещё не посещена
                {
                    dist[nr][nc] = dist[r][c] + 1;
                    parent[nr][nc] = pos;
                    queue_insert(q, nr * cols + nc);
                }

                nr += dr[d];
                nc += dc[d];
            }
        }
    }

    queue_delete(q);
}


// Восстанавливаем путь и ставим цифры
void restore_path(int start_r, int start_c, int end_r, int end_c)
{
    int cur = end_r * cols + end_c;
    int start = start_r * cols + start_c;

    while (cur != start)
    {
        int r = cur / cols;
        int c = cur % cols;

        grid[r][c] = '0' + (dist[r][c] % 10); // записываем цифру
        cur = parent[r][c];
    }

    grid[start_r][start_c] = '0'; // старт тоже помечаем
}


int main(int argc, char** argv)
{
    if (argc < 2)
        return 1;

    // Чтение лабиринта 
    ifstream file(argv[1]);
    if (!file.is_open())
        return 1;

    string line;
    while (getline(file, line) && !line.empty())
    {
        int len = (int)line.size();
        if (len > MAXN - 1)
            len = MAXN - 1;

        for (int j = 0; j < len; j++)
            grid[rows][j] = line[j];

        grid[rows][len] = '\0';
        rows++;
    }
    file.close();

    // Определяем количество столбцов
    cols = 0;
    while (grid[0][cols])
        cols++;

    // Поиск старта и финиша
    int start_r = 0, start_c = 0;
    int end_r = 0, end_c = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] == 'Q')
            {
                start_r = i;
                start_c = j;
            }
            if (grid[i][j] == 'E')
            {
                end_r = i;
                end_c = j;
            }

            dist[i][j] = -1;        // -1 = не посещена
            parent[i][j] = -1;
        }
    }

    // Поиск пути
    bfs(start_r, start_c);

    if (dist[end_r][end_c] != -1)
        restore_path(start_r, start_c, end_r, end_c);

    // Вывод результата
    for (int i = 0; i < rows; i++)
        cout << grid[i] << "\n";

    return 0;
}