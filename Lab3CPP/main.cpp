#include "queue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>
#include <cctype>
#include <cstdio>
#include <cstdlib>

using namespace std;

using Maze = vector<string>;
using DistMap = vector<vector<int>>;

int encode(int q, int r) {
    return q * 1000 + r;
}

void decode(int code, int& q, int& r) {
    q = code / 1000;
    r = code % 1000;
}

Maze read_maze(const string& filename, int& start_q, int& start_r) {
    Maze maze;
    ifstream input(filename);
    if (!input.is_open()) {
        exit(1);
    }
    string line;
    while (getline(input, line) ) {
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
            }
        }
    }
    return maze;
}

void get_neighbors(int r, int dirs[6][2]) {
    dirs[0][0] = 1;  dirs[0][1] = 0;
    dirs[1][0] = -1; dirs[1][1] = 0;

    if (r % 2 == 0) {
        dirs[2][0] = 0; dirs[2][1] = -1;
        dirs[3][0] = 1; dirs[3][1] = -1;
        dirs[4][0] = 0; dirs[4][1] = 1;
        dirs[5][0] = 1; dirs[5][1] = 1;
    } else {
        dirs[2][0] = -1; dirs[2][1] = -1;
        dirs[3][0] = 0; dirs[3][1] = -1;
        dirs[4][0] = -1; dirs[4][1] = 1;
        dirs[5][0] = 0; dirs[5][1] = 1;
    }
}

bool is_slit_blocked(const Maze& maze, int cq, int cr, int nq, int nr) {
    if (abs(cq - nq) != 1 || abs(cr - nr) != 1) return false;

    int rows = maze.size();
    int cols = maze[0].size();

    int r_wall1, q_wall1;
    int r_wall2, q_wall2;

    if (cr % 2 == 0) {
        r_wall1 = cr;
        q_wall1 = min(cq, nq) + 1;
        r_wall2 = nr;
        q_wall2 = min(cq, nq);
    } else {
        r_wall1 = cr;
        q_wall1 = min(cq, nq);
        r_wall2 = nr;
        q_wall2 = min(cq, nq) + 1;
    }

    bool wall1_blocked = (r_wall1 >= 0 && r_wall1 < rows && q_wall1 >= 0 && q_wall1 < cols) && maze[r_wall1][q_wall1] == '#';
    bool wall2_blocked = (r_wall2 >= 0 && r_wall2 < rows && q_wall2 >= 0 && q_wall2 < cols) && maze[r_wall2][q_wall2] == '#';

    return wall1_blocked && wall2_blocked;
}

bool is_valid(const Maze& maze, int q, int r, const DistMap& dist) {
    int rows = maze.size();
    if (rows == 0) return false;
    int cols = maze[0].size();
    if (q < 0 || q >= cols || r < 0 || r >= rows) return false;
    if (maze[r][q] == '#') return false;
    if (dist[r][q] != -1) return false;
    return true;
}

vector<pair<int, int>> reconstruct_path(const DistMap& dist, int end_q, int end_r) {
    vector<pair<int, int>> path;
    int cq = end_q, cr = end_r;
    while (dist[cr][cq] != -1) {
        path.emplace_back(cq, cr);
        if (dist[cr][cq] == 0) break;
        int dirs[6][2];
        get_neighbors(cr, dirs);
        bool found = false;
        for (int d = 0; d < 6; ++d) {
            int nq = cq + dirs[d][0];
            int nr = cr + dirs[d][1];
            if (nq >= 0 && nq < (int)dist[0].size() && nr >= 0 && nr < (int)dist.size() &&
                dist[nr][nq] == dist[cr][cq] - 1) {
                cq = nq; cr = nr;
                found = true;
                break;
            }
        }
        if (!found) break;
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<pair<int, int>>& path) {
    cout << "Path:";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) cout << " ->";
        cout << " (" << path[i].first << "," << path[i].second << ")";
    }
    cout << endl;
}

void print_hex_maze(const Maze& maze, const vector<pair<int, int>>& path) {
    int rows = maze.size();
    if (rows == 0) return;
    int cols = maze[0].size();
    vector<vector<char>> display(rows, vector<char>(cols));
    for (int r = 0; r < rows; ++r) {
        for (int q = 0; q < cols; ++q) {
            display[r][q] = maze[r][q];
        }
    }
    for (const auto& p : path) {
        int q = p.first;
        int r = p.second;
        if (display[r][q] != 'S' && display[r][q] != 'E') {
            display[r][q] = 'x';
        }
    }
    // Верхняя граница
    cout << " ";
    for (int q = 0; q < cols; ++q) {
        cout << "/ \\ ";
    }
    cout << endl;
    // Основное содержимое
    for (int r = 0; r < rows; ++r) {
        // Отступ
        string indent(r, ' ');
        cout << indent << " /";
        for (int q = 0; q < cols; ++q) {
            cout << " " << display[r][q] << " ";
            cout << "\\";
        }
        cout << endl;
        cout << indent << "  /";
        for (int q = 0; q < cols; ++q) {
            cout << " \\ /";
        }
        cout << endl;
    }
}

void bfs_hex(const Maze& maze, int start_q, int start_r) {
    int rows = maze.size();
    if (rows == 0) {
        cout << -1 << endl;
        return;
    }
    int cols = maze[0].size();
    DistMap dist(rows, vector<int>(cols, -1));
    Queue* q = queue_create();
    queue_insert(q, encode(start_q, start_r));
    dist[start_r][start_q] = 0;
    int end_q = -1, end_r = -1;
    bool found = false;
    int dirs[6][2];
    while (!queue_empty(q)) {
        int code = queue_get(q);
        queue_remove(q);
        int cq, cr;
        decode(code, cq, cr);
        if (maze[cr][cq] == 'E') {
            found = true;
            end_q = cq;
            end_r = cr;
            break;
        }
        get_neighbors(cr, dirs);
        for (int d = 0; d < 6; ++d) {
            int nq = cq + dirs[d][0];
            int nr = cr + dirs[d][1];
            if (is_valid(maze, nq, nr, dist)) {
                if (is_slit_blocked(maze, cq, cr, nq, nr)) {
                    continue;
                }
                dist[nr][nq] = dist[cr][cq] + 1;
                queue_insert(q, encode(nq, nr));
            }
        }
    }
    queue_delete(q);
    if (found) {
        cout << dist[end_r][end_q] << endl;
        auto path = reconstruct_path(dist, end_q, end_r);
        print_path(path);
        cout << "Maze with path:" << endl;
        print_hex_maze(maze, path);
    } else {
        cout << -1 << endl;
    }
}

int main(int argc, char* argv[]) {
    const char* test_output = getenv("TEST_OUTPUT");
    if (test_output) {
        FILE* result = freopen(test_output, "w", stdout);
        if (!result) {
            std::cerr << "Error: Failed to redirect stdout to " << test_output << std::endl;
            return 1;
        }
    }
    
    string input_filename = (argc > 1) ? argv[1] : "input.txt";
    int start_q = 0, start_r = 0;
    
    Maze maze = read_maze(input_filename, start_q, start_r);
    bfs_hex(maze, start_q, start_r);
    
    return 0;
}