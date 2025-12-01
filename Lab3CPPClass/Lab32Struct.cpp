#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include "queue.h"

using namespace std;

struct Position {
    int x, y;
    int prev_index;
    char move;
};

const int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
const char moves[8] = { '1', '2', '3', '4', '5', '6', '7', '8' };

vector<string> readMaze(const string& filename) {
    vector<string> maze;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return maze;
    }

    while (getline(file, line)) {
        maze.push_back(line);
    }

    return maze;
}

pair<int, int> findPosition(const vector<string>& maze, char target) {
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            if (maze[i][j] == target) {
                return { i, j };
            }
        }
    }
    return { -1, -1 };
}

bool isValid(int x, int y, const vector<string>& maze) {
    return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() && maze[x][y] != '#';
}

string getPath(const vector<Position>& positions, int index) {
    string path;
    while (index != -1 && positions[index].move != '\0') {
        path = positions[index].move + path;
        index = positions[index].prev_index;
    }
    return path;
}

vector<Position> findPath(const vector<string>& maze) {
    int rows = maze.size();
    if (rows == 0) return {};
    int cols = maze[0].size();

    auto start = findPosition(maze, 'Q');
    auto end = findPosition(maze, 'E');

    if (start.first == -1 || end.first == -1) {
        return {};
    }

    Queue queue;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<Position> positions;

    positions.push_back({ start.first, start.second, -1, '\0' });
    queue.insert(positions.size() - 1);
    visited[start.first][start.second] = true;

    while (!queue.empty()) {
        int current_index = queue.get();
        queue.remove();

        Position current = positions[current_index];

        if (current.x == end.first && current.y == end.second) {
            return positions;
        }

        for (int i = 0; i < 8; ++i) {
            int new_x = current.x + dx[i];
            int new_y = current.y + dy[i];

            while (isValid(new_x, new_y, maze)) {
                if (!visited[new_x][new_y]) {
                    visited[new_x][new_y] = true;
                    positions.push_back({ new_x, new_y, current_index, moves[i] });
                    queue.insert(positions.size() - 1);

                    if (new_x == end.first && new_y == end.second) {
                        return positions;
                    }
                }
                new_x += dx[i];
                new_y += dy[i];
            }
        }
    }

    return {};
}

void printSolution(const vector<string>& maze, const vector<Position>& positions, const pair<int, int>& end_pos, const string& output_file) {
    int end_index = -1;
    for (int i = 0; i < positions.size(); ++i) {
        if (positions[i].x == end_pos.first && positions[i].y == end_pos.second) {
            end_index = i;
            break;
        }
    }

    if (end_index == -1) {
        cout << "Путь не найден" << endl;
        ofstream out(output_file);
        if (out.is_open()) {
            out << "Путь не найден" << endl;
        }
        return;
    }

    string path = getPath(positions, end_index);
    cout << "Путь найден: " << path << endl;
    cout << "Длина пути: " << path.length() << " ходов" << endl;

    vector<string> maze_with_path = maze;
    int current_index = end_index;

    while (current_index != -1) {
        Position pos = positions[current_index];
        if (maze_with_path[pos.x][pos.y] != 'Q' && maze_with_path[pos.x][pos.y] != 'E') {
            maze_with_path[pos.x][pos.y] = '*';
        }
        current_index = pos.prev_index;
    }

    cout << "Лабиринт с путем:" << endl;
    for (const auto& row : maze_with_path) {
        cout << row << endl;
    }

    ofstream out(output_file);
    if (out.is_open()) {
        out << "Путь: " << path << endl;
        out << "Длина пути: " << path.length() << " ходов" << endl;
        out << "Лабиринт с путем:" << endl;
        for (const auto& row : maze_with_path) {
            out << row << endl;
        }
        out.close();
    }
    else {
        cerr << "Ошибка: не удалось открыть файл для записи: " << output_file << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Использование: " << argv[0] << " <входной_файл> <выходной_файл>" << endl;
        return 1;
    }

    string input_file = argv[1];
    string output_file = argv[2];

    cout << "Чтение лабиринта из файла: " << input_file << endl;
    vector<string> maze = readMaze(input_file);

    if (maze.empty()) {
        cout << "Ошибка: не удалось прочитать лабиринт или файл пуст." << endl;
        return 1;
    }

    cout << "Размер лабиринта: " << maze.size() << "x" << maze[0].size() << endl;

    auto start = findPosition(maze, 'Q');
    auto end = findPosition(maze, 'E');

    if (start.first == -1) {
        cout << "Ошибка: стартовая позиция 'Q' не найдена" << endl;
        return 1;
    }

    if (end.first == -1) {
        cout << "Ошибка: конечная позиция 'E' не найдена" << endl;
        return 1;
    }

    cout << "Старт: (" << start.first << ", " << start.second << ")" << endl;
    cout << "Финиш: (" << end.first << ", " << end.second << ")" << endl;

    cout << "Поиск пути..." << endl;
    vector<Position> positions = findPath(maze);

    printSolution(maze, positions, end, output_file);

    return 0;
}