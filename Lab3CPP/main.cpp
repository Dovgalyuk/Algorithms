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

void decode(int code, int &q, int &r) {
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
        dirs[3][0] = 0;  dirs[3][1] = -1;
        dirs[4][0] = -1; dirs[4][1] = 1;
        dirs[5][0] = 0;  dirs[5][1] = 1;
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
        q_wall1 = nq; 
        
        r_wall2 = nr; 
        q_wall2 = cq;
    } else {
        r_wall1 = cr; 
        q_wall1 = cq; 
        
        r_wall2 = nr; 
        q_wall2 = nq;
    }

    auto is_wall = [&](int r, int q) {
        if (r < 0 || r >= rows || q < 0 || q >= cols) return false;
        return maze[r][q] == '#';
    };

    if (is_wall(r_wall1, q_wall1) && is_wall(r_wall2, q_wall2)) {
        return true;
    }
    
    return false;
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
vector<pair<int,int>> reconstruct_path(const DistMap& dist, int end_q, int end_r) {
    vector<pair<int,int>> path;
    int cq = end_q, cr = end_r;
    while (dist[cr][cq] != -1) {
        path.emplace_back(cq, cr);
        if (dist[cr][cq] == 0) break;

        int dirs[6][2] = {{1,0},{0,-1},{-1,1},{-1,0},{0,1},{1,-1}};
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
    reverse(path.begin(), path.end()); // от S к E
    return path;
}

vector<pair<int, int>> get_path(int end_q, int end_r, const DistMap& dist) {
    vector<pair<int, int>> path;
    int curr_q = end_q;
    int curr_r = end_r;
    int curr_dist = dist[curr_r][curr_q];
    int dirs[6][2];

    while (curr_dist > 0) {
        path.push_back({curr_q, curr_r});
        get_neighbors(curr_r, dirs);
        bool found_prev = false;
        for (int d = 0; d < 6; ++d) {
            int nq = curr_q + dirs[d][0];
            int nr = curr_r + dirs[d][1];
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
    path.push_back({curr_q, curr_r});
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<pair<int, int>>& path) {
    cout << "Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << "(" << path[i].first << "," << path[i].second << ")";
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

void print_hex_maze(const Maze& maze, const vector<pair<int,int>>& path) {
    int rows = maze.size();
    int cols = maze[0].size();
    vector<string> grid = maze;
    for (auto [q, r] : path) {
        if (grid[r][q] != 'S' && grid[r][q] != 'E') {
            grid[r][q] = 'x';
        }
    }

    // Верхняя граница
    cout << " ";
    for (int q = 0; q < cols; ++q) cout << "/ \\";
    cout << " " << endl;

    for (int r = 0; r < rows; ++r) {
        //нечёт стрк
        if (r % 2 == 1) cout << " ";
        cout << "|";
        for (int q = 0; q < cols; ++q) {
            cout << " " << grid[r][q] << " |";
        }
        cout << endl;

        // Нижняя граница
        cout << " ";
        for (int q = 0; q < cols; ++q) {
            cout << "\\ /";
        }
        cout << " " << endl;
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

    Queue *q = queue_create();
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
        cout << "Path:";
        for (size_t i = 0; i < path.size(); ++i) {
            auto [q, r] = path[i];
            cout << " (" << q << "," << r << ")";
        }
        cout << endl;
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