#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "queue.h"

using namespace std;

typedef vector<string> Maze;
typedef vector<int> Cells;

bool findStartAndFinishes(const Maze &maze, int width, int height, int &start, Cells &finishes) {
    for (int row = 0; row < height; row++) {
        if (static_cast<int>(maze[row].size()) != width) {
            cerr << "Error: row " << row << " has a different length." << endl;
            return false;
        }
        for (int col = 0; col < width; col++) {
            char c = maze[row][col];
            if (c == 'X') {
                if (start != -1) {
                    cerr << "Error: more than one start position 'X'." << endl;
                    return false;
                }
                start = row * width + col;
            } else if (c >= '0' && c <= '9') {
                finishes.push_back(row * width + col);
            } else if (c != '#' && c != '.') {
                cerr << "Error: Invalid character '" << c << "' in maze." << endl;
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <maze_file>" << endl;
        return 2;
    }

    Maze maze;
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (!line.empty()) {
            maze.push_back(line); 
        }
    }
    file.close();

    if (maze.empty()) {
        cerr << "Error: The maze is empty." << endl;
        return 1;
    }

    int width = static_cast<int>(maze[0].size());
    int height = static_cast<int>(maze.size());

    Cells finishes;
    int start = -1;
    if (!findStartAndFinishes(maze, width, height, start, finishes)) {
        return 1;
    }

    if (start == -1) {
        cerr << "Error: there is no start position 'X'" << endl;
        return 1;
    }
    if (finishes.empty()) {
        cerr << "Error: there are no finish positions (digits)" << endl;
        return 1;
    }

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    int cells = width * height;
    Cells dist(cells, -1);
    Cells side(cells, 0); // 0 = не посещена, 1 = волна от старта, 2 = волна от финишей
    Cells digit(cells, -1); // для волны 2: цифра, от которой она идёт

    Queue *fromStart = queue_create();
    Queue *fromFinish = queue_create();

    side[start] = 1;
    dist[start] = 0;
    queue_insert(fromStart, start);

    for (int d = 0; d <= 9; d++) { // Сортировка по значению цифры
        for (int finish : finishes) {
            if (maze[finish / width][finish % width] - '0' == d) {
                side[finish] = 2;
                dist[finish] = 0;
                digit[finish] = d;
                queue_insert(fromFinish, finish);
            }   
        }
    }

    int answer = -1;
    while (answer == -1 && !queue_empty(fromStart) && !queue_empty(fromFinish)) {
        for (int turn = 0; turn < 2 && answer == -1; turn++) {
            Queue *q = (turn == 0) ? fromStart : fromFinish;
            int level = dist[queue_get(q)];

            while (!queue_empty(q) && dist[queue_get(q)] == level) {
                int cell = queue_get(q);
                queue_remove(q);
                
                int row = cell / width;
                int col = cell % width;
                int mySide = side[cell];
                for (int k = 0; k < 4; k++) {
                    int new_row = row + dr[k];
                    int new_col = col + dc[k];

                    if (new_row >= height || new_row < 0 || new_col >= width || new_col < 0) continue;
                    if (maze[new_row][new_col] == '#') continue;

                    int next = new_row * width + new_col;
                    if (side[next] == mySide) continue;

                    if (side[next] != 0) {
                        int candidate = (mySide == 1) ? digit[next] : digit[cell];
                        if (answer == -1 || candidate < answer) answer = candidate;
                    } else {
                        side[next] = mySide;
                        dist[next] = dist[cell] + 1;
                        digit[next] = digit[cell];

                        queue_insert(q, next);
                    }
                }
            }       
        }
    }
    queue_delete(fromStart);
    queue_delete(fromFinish);

    if (answer == -1) {
        cerr << "No path found" << endl;
        return 1;
    } 
    cout << answer << endl;

    return 0;
}
