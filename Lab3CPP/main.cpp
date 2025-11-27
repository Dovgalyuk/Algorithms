#include "queue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>  // Для pair

using namespace std;

typedef pair<int, int> Pos;  // q, r

vector<string> read_maze(const string& filename, int& start_q, int& start_r, int& end_q, int& end_r) {  // Добавлены параметры для end
    vector<string> maze;
    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Cannot open " << filename << endl;
        exit(1);
    }
    string line;
    while (getline(input, line)) {
        maze.push_back(line);
    }
    if (maze.empty()) return maze;
    int rows = maze.size();
    int cols = maze[0].size();
    for (int r = 0; r < rows; ++r) {
        if (maze[r].size() != static_cast<size_t>(cols)) {
            cerr << "Invalid maze: uneven row lengths" << endl;
            exit(1);
        }
        for (int q = 0; q < cols; ++q) {
            if (maze[r][q] == 'S') {
                start_q = q;
                start_r = r;
                maze[r][q] = '.';
            } else if (maze[r][q] == 'E') {  // Обработка E
                end_q = q;
                end_r = r;
                maze[r][q] = '.';  // Освободить для прохода
            }
        }
    }
    return maze;
}

bool is_valid(const vector<string>& maze, int q, int r, vector<vector<bool>>& visited) {
    int rows = maze.size();
    if (rows == 0) return false;
    int cols = maze[0].size();
    if (q < 0 || q >= cols || r < 0 || r >= rows) return false;
    if (maze[r][q] == '#') return false;
    if (visited[r][q]) return false;
    return true;
}

int bfs_hex(const vector<string>& maze, int start_q, int start_r, int end_q, int end_r) {  // Добавлены параметры для end
    int rows = maze.size();
    if (rows == 0) return -1;
    int cols = maze[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<int>> dist(rows, vector<int>(cols, -1));
    Queue *q = queue_create();
    queue_insert(q, start_q * 1000 + start_r);  // Кодируем позицию как int (q*1000 + r)
    visited[start_r][start_q] = true;
    dist[start_r][start_q] = 0;

    int dirs[6][2] = {{1, 0}, {0, -1}, {-1, 1}, {-1, 0}, {0, 1}, {1, -1}};  // Шестиугольные соседи

    while (!queue_empty(q)) {
        int code = queue_get(q);
        queue_remove(q);
        int cq = code / 1000;
        int cr = code % 1000;
        int cd = dist[cr][cq];
        if (cr == end_r && cq == end_q) return cd;  // Проверка по координатам E

        for (int d = 0; d < 6; ++d) {
            int nq = cq + dirs[d][0];
            int nr = cr + dirs[d][1];
            if (is_valid(maze, nq, nr, visited)) {
                visited[nr][nq] = true;
                dist[nr][nq] = cd + 1;
                queue_insert(q, nq * 1000 + nr);
            }
        }
    }
    queue_delete(q);
    return -1;  // Нет пути
}

int main(int argc, char* argv[]) {
    string input_filename = (argc > 1) ? argv[1] : "input.txt";
    int start_q = 0, start_r = 0, end_q = 0, end_r = 0;  // Объявление end_q и end_r
    auto maze = read_maze(input_filename, start_q, start_r, end_q, end_r);  // Передача 4 аргументов
    int path_len = bfs_hex(maze, start_q, start_r, end_q, end_r);  // Передача end в bfs_hex
    cout << path_len << endl;
    return 0;
}