#include <iostream>
#include <fstream>
#include "queue.h"

using namespace std;

int main(int argc, char* argv[]) {
    const char* filename = (argc > 1) ? argv[1] : "input1.txt";
    ifstream fin(filename);
    if (!fin.is_open()) return 1;
    int width = 0, height = 0, currW = 0;
    char c;
    while (fin.get(c)) {
        if (c == '\n' && currW > 0) {
            if (width == 0) width = currW;
            height++;
            currW = 0;
        }
        if (c != '\n' && c != '\r') currW++;
    }
    if (currW > 0) {
        height++;
        if (width == 0) width = currW;
    }
    fin.clear();
    fin.seekg(0, ios::beg);
    if (width == 0 || height == 0) return 1;
    char* maze = new char[width * height];
    bool* visited = new bool[width * height];
    for (int i = 0; i < width * height; i++) visited[i] = false;
    int startX = -1, startY = -1, idx = 0;
    while (fin.get(c)) {
        if (c != '\n' && c != '\r') {
            maze[idx] = c;
            if (c == 'X') {
                startX = idx % width;
                startY = idx / width;
            }
            idx++;
        }
    }
    if (startX == -1 || startY == -1) {
        delete[] maze;
        delete[] visited;
        return 1;
    }
    Queue q;
    q.insert(startY * width + startX);
    visited[startY * width + startX] = true;
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    while (!q.empty()) {
        int curr = q.get();
        q.remove();
        int x = curr % width;
        int y = curr / width;
        char cell = maze[y * width + x];
        if (cell >= '0' && cell <= '9') {
            cout << cell << '\n';
            delete[] maze;
            delete[] visited;
            return 0;
        }
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                int nIdx = ny * width + nx;
                if (!visited[nIdx] && maze[nIdx] != '#') {
                    visited[nIdx] = true;
                    q.insert(nIdx);
                }
            }
        }
    }
    cout << "No exit found\n";
    delete[] maze;
    delete[] visited;
    return 0;
}
