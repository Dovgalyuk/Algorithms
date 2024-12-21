#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include "queue.h"
using namespace std;

// Функция для поиска пути с помощью BFS
bool bfs(vector<string>& maze, int start_x, int start_y, int end_x, int end_y) {
    int n = maze.size();
    int m = maze[0].size();

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<int>> dist(n, vector<int>(m, -1));

    queue<pair<int, int>> q;
    q.push({ start_x, start_y });
    visited[start_x][start_y] = true;
    dist[start_x][start_y] = 0;

    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < n && ny < m && !visited[nx][ny] && maze[nx][ny] != '#') {
                visited[nx][ny] = true;
                dist[nx][ny] = dist[x][y] + 1;
                q.push({ nx, ny });

                if (nx == end_x && ny == end_y) {
                    int cx = end_x, cy = end_y;
                    while (dist[cx][cy] != 0) {
                        maze[cx][cy] = 'x';
                        for (int j = 0; j < 4; ++j) {
                            int px = cx - dx[j];
                            int py = cy - dy[j];
                            if (px >= 0 && py >= 0 && px < n && py < m && dist[px][py] == dist[cx][cy] - 1) {
                                cx = px;
                                cy = py;
                                break;
                            }
                        }
                    }
                    maze[start_x][start_y] = 'X';
                    maze[end_x][end_y] = 'Y';
                    return true;
                }
            }
        }
    }

    return false;
}

// Функция для вывода лабиринта в консоль
void print_maze(const vector<string>& maze) {
    for (const auto& row : maze) {
        cout << row << endl;
    }
}

// Функция для чтения лабиринта из файла
bool read_maze_from_file(const string& filename, vector<string>& maze, int& start_x, int& start_y, int& end_x, int& end_y) {
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Ошибка при открытии файла!" << endl;
        return false;
    }

    string line;
    maze.clear();
    int row = 0;

    while (getline(input_file, line)) {
        maze.push_back(line);
        for (std::string::size_type col = 0; col < line.size(); ++col) { // Изменили тип на size_t
            if (line[col] == 'X') {
                start_x = row;
                start_y = col;
            }
            if (line[col] == 'Y') {
                end_x = row;
                end_y = col;
            }
        }
        row++;
    }

    input_file.close();
    return true;
}


// Основная функция
int main() {
    string input_filename = "input.txt"; // Имя входного файла

    // Переменные для координат старта и финиша
    int start_x = -1, start_y = -1, end_x = -1, end_y = -1;
    vector<string> maze;

    // Чтение лабиринта из файла
    if (!read_maze_from_file(input_filename, maze, start_x, start_y, end_x, end_y)) {
        return 1;
    }

    // Выводим исходный лабиринт на экран
    cout << "Исходный лабиринт:" << endl;
    print_maze(maze);

    // Применяем BFS для нахождения пути
    if (bfs(maze, start_x, start_y, end_x, end_y)) {
        cout << "\nМинимальный путь найден:" << endl;
        print_maze(maze);
    }
    else {
        cout << "\nIMPOSSIBLE" << endl;
    }

    return 0;
}


