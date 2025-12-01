#include "queue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // Для reverse

using namespace std;

// Typedefs
using Maze = vector<string>;
using DistMap = vector<vector<int>>;


int encode(int q, int r) {
    return q * 1000 + r;
}

void decode(int code, int &q, int &r) {
    q = code / 1000;
    r = code % 1000;
}

Maze read_maze(const string& filename, int& start_q, int& start_r, int& end_q, int& end_r) {
    Maze maze;
    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Cannot open " << filename << endl;
        exit(1);
    }
    string line;
    while (getline(input, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        maze.push_back(line);
    }
    if (maze.empty()) return maze;

    int rows = maze.size();
    int cols = maze[0].size();

    for (int r = 0; r < rows; ++r) {
        for (int q = 0; q < cols; ++q) {
            if (maze[r][q] == 'S') {
                start_q = q;
                start_r = r;
            } else if (maze[r][q] == 'E') {
                end_q = q;
                end_r = r;
            }
        }
    }
    return maze;
}

bool is_valid(const Maze& maze, int q, int r, const DistMap& dist) {
    int rows = maze.size();
    if (rows == 0) return false;
    int cols = maze[0].size();
    
    if (q < 0 || q >= cols || r < 0 || r >= rows) return false;
    if (maze[r][q] == '#') return false;
    if (dist[r][q] != -1) return false; // Уже посетили
    
    return true;
}

void print_path(int end_q, int end_r, const DistMap& dist) {
    // 6 соседей 
    int dirs[6][2] = {{1, 0}, {0, -1}, {-1, 1}, {-1, 0}, {0, 1}, {1, -1}};
    
    vector<string> path_coords;
    int curr_q = end_q;
    int curr_r = end_r;
    int curr_dist = dist[curr_r][curr_q];

    if (curr_dist == -1) {
        cout << "No path found" << endl;
        return;
    }

    while (curr_dist > 0) {
        path_coords.push_back("(" + to_string(curr_q) + "," + to_string(curr_r) + ")");
        
        // Ищем родителя(клетки, от которой пришли)
        bool found_prev = false;
        for (int d = 0; d < 6; ++d) {
            int nq = curr_q + dirs[d][0];
            int nr = curr_r + dirs[d][1];
            
            // Проверка границ
            if (nr >= 0 && nr < (int)dist.size() && nq >= 0 && nq < (int)dist[0].size()) {
                if (dist[nr][nq] == curr_dist - 1) {
                    curr_q = nq;
                    curr_r = nr;
                    curr_dist--;
                    found_prev = true;
                    break;
                }
            }
        }
        if (!found_prev) break;
    }
    
    path_coords.push_back("(" + to_string(curr_q) + "," + to_string(curr_r) + ")"); // старт

    //путь от старта к концу
    cout << "Path: ";
    for (int i = path_coords.size() - 1; i >= 0; --i) {
        cout << path_coords[i] << (i > 0 ? " -> " : "");
    }
    cout << endl;
}

void bfs_hex(const Maze& maze, int start_q, int start_r, int end_q, int end_r) {
    int rows = maze.size();
    if (rows == 0) return;
    int cols = maze[0].size();

    // visited удален
    DistMap dist(rows, vector<int>(cols, -1));

    Queue *q = queue_create();
    queue_insert(q, encode(start_q, start_r));
    dist[start_r][start_q] = 0;

    int dirs[6][2] = {{1, 0}, {0, -1}, {-1, 1}, {-1, 0}, {0, 1}, {1, -1}};
    bool found = false;

    while (!queue_empty(q)) {
        int code = queue_get(q);
        queue_remove(q);
        
        int cq, cr;
        decode(code, cq, cr);

        if (cq == end_q && cr == end_r) {
            found = true;
            break;
        }
        

        for (int d = 0; d < 6; ++d) {
            int nq = cq + dirs[d][0];
            int nr = cr + dirs[d][1];

            if (is_valid(maze, nq, nr, dist)) {
                dist[nr][nq] = dist[cr][cq] + 1;
                queue_insert(q, encode(nq, nr));
            }
        }
    }
    queue_delete(q);

    if (found) {
        cout << dist[end_r][end_q] << endl; // длина пути
        print_path(end_q, end_r, dist);     // координаты пути
    } else {
        cout << "No path found" << endl;
    }
}

int main(int argc, char* argv[]) {
    string input_filename = (argc > 1) ? argv[1] : "input.txt";
    int start_q = 0, start_r = 0, end_q = 0, end_r = 0;
    
    Maze maze = read_maze(input_filename, start_q, start_r, end_q, end_r);
    bfs_hex(maze, start_q, start_r, end_q, end_r);
    
    return 0;
}