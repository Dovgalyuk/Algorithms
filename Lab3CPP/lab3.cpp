#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "queue.h"

using namespace std;

struct Cell {
    int r, c;
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream in(argv[1]);
    if (!in.is_open()) {
        cerr << "Error: Cannot open input file " << argv[1] << endl;
        return 1;
    }

    vector<string> maze;
    string line;
    while (getline(in, line)) {
        if (!line.empty() && line.back() == '\r') // на всякий случай для Windows-строк
            line.pop_back();
        if (!line.empty())
            maze.push_back(line);
    }
    in.close();

    if (maze.empty())
        return 0;

    int rows = (int)maze.size();
    int cols = (int)maze[0].size();

    Cell start{ -1, -1 };
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] == 'X') {
                start = { i, j };
                break;
            }
        }
        if (start.r != -1) break;
    }

    if (start.r == -1) {
        return 0;
    }

    vector<vector<int>> dist(rows, vector<int>(cols, -1));

    Queue* q = queue_create();
    queue_insert(q, start.r * cols + start.c);
    dist[start.r][start.c] = 0;

    int dr[4] = { -1, 1, 0, 0 };
    int dc[4] = { 0, 0, -1, 1 };

    char answer = '?';
    int bestDist = -1;

    while (!queue_empty(q)) {
        int v = queue_get(q);
        queue_remove(q);
        int r = v / cols;
        int c = v % cols;

        if (maze[r][c] >= '0' && maze[r][c] <= '9') {
            if (bestDist == -1 || dist[r][c] < bestDist) {
                bestDist = dist[r][c];
                answer = maze[r][c];
            }
        }

        for (int k = 0; k < 4; ++k) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
                continue;
            if (maze[nr][nc] == '#')
                continue;
            if (dist[nr][nc] != -1)
                continue;
            dist[nr][nc] = dist[r][c] + 1;
            queue_insert(q, nr * cols + nc);
        }
    }

    queue_delete(q);

    if (answer != '?')
        cout << answer << endl;

    return 0;
}
