#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "queue.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "NO FILE ARG\n";
        return 1;
    }

    ifstream input(argv[1]);

    if (!input.is_open()) {
        cout << "FILE OPEN ERROR\n";
        return 1;
    }

    vector<vector<string>> maze;
    vector<string> layer;
    string line;

    while (getline(input, line)) {
        if (line.empty()) {
            if (!layer.empty()) {
                maze.push_back(layer);
                layer.clear();
            }
        }
        else {
            layer.push_back(line);
        }
    }

    if (!layer.empty()) {
        maze.push_back(layer);
    }

    if (maze.empty() || maze[0].empty() || maze[0][0].empty()) {
        cout << "EMPTY MAZE\n";
        return 1;
    }

    int startX = -1;
    int startY = -1;
    int startZ = -1;

    for (size_t z = 0; z < maze.size(); ++z) {
        for (size_t y = 0; y < maze[z].size(); ++y) {
            for (size_t x = 0; x < maze[z][y].size(); ++x) {
                char cell = maze[z][y][x];

                if (cell == 'X') {
                    startX = static_cast<int>(x);
                    startY = static_cast<int>(y);
                    startZ = static_cast<int>(z);
                }
            }
        }
    }

    if (startX == -1) {
        cout << "START NOT FOUND\n";
        return 1;
    }

    int D = static_cast<int>(maze.size());
    int H = static_cast<int>(maze[0].size());
    int W = static_cast<int>(maze[0][0].size());

    for (const auto& currentLayer : maze) {
        if (currentLayer.size() != static_cast<size_t>(H)) {
            cout << "INVALID MAZE\n";
            return 1;
        }

        for (const string& row : currentLayer) {
            if (row.size() != static_cast<size_t>(W)) {
                cout << "INVALID MAZE\n";
                return 1;
            }
        }
    }

    Queue* q = queue_create();

    int startIndex = startZ * H * W + startY * W + startX;

    queue_insert(q, startIndex);

    vector<bool> visited(W * H * D, false);
    visited[startIndex] = true;

    int dx[6] = { 1, -1, 0, 0, 0, 0 };
    int dy[6] = { 0, 0, 1, -1, 0, 0 };
    int dz[6] = { 0, 0, 0, 0, 1, -1 };

    while (!queue_empty(q)) {

        int current = queue_get(q);
        queue_remove(q);

        int x = current % W;
        int y = (current / W) % H;
        int z = current / (W * H);

        char cell = maze[z][y][x];

        if (cell >= '0' && cell <= '9') {
            cout << (cell - '0') << "\n";
            queue_delete(q);
            return 0;
        }

        for (int k = 0; k < 6; ++k) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            int nz = z + dz[k];

            if (nx < 0 || nx >= W) continue;
            if (ny < 0 || ny >= H) continue;
            if (nz < 0 || nz >= D) continue;

            if (maze[nz][ny][nx] == '#') continue;

            int nIndex = nz * H * W + ny * W + nx;

            if (visited[nIndex]) continue;

            visited[nIndex] = true;
            queue_insert(q, nIndex);
        }
    }

    cout << "NOT FOUND\n";
    queue_delete(q);

    return 0;
}
