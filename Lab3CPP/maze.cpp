#include <iostream>
#include <fstream>
#include "queue.h"
#include "vector.h"

using namespace std;

int main(int argc, char* argv[]) {
    const char* filename = (argc > 1) ? argv[1] : "input1.txt";
    ifstream fin(filename);
    if (!fin.is_open()) return 1;
    int width = 0;
    int height = 0;
    int currW = 0;
    char c;
    while (fin.get(c)) {
        if (c == '\n') {
            if (currW > 0) {
                if (width == 0) width = currW;
                height++;
                currW = 0;
            }
        }
        else if (c != '\r') currW++;
    }
    if (currW > 0) {
        height++;
        if (width == 0) width = currW;
    }
    fin.clear();
    fin.seekg(0, ios::beg);
    Vector maze;
    maze.resize(width * height);
    Vector visited;
    visited.resize(width * height);
    for (size_t i = 0; i < visited.size(); i++) visited.set(i, 0);
    int startX = -1;
    int startY = -1;
    int idx = 0;
    while (fin.get(c)) {
        if (c != '\n' && c != '\r') {
            maze.set(idx, c);
            if (c == 'X') {
                startX = idx % width;
                startY = idx / width;
            }
            idx++;
        }
    }
    if (startX == -1 || startY == -1) return 1;
    Queue q;
    q.insert(startY * width + startX);
    visited.set(startY * width + startX, 1);
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    while (!q.empty()) {
        int curr = q.get();
        q.remove();
        int x = curr % width;
        int y = curr / width;
        char cell = (char)maze.get(y * width + x);
        if (cell >= '0' && cell <= '9') {
            cout << cell << '\n';
            return 0;
        }
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                int nIdx = ny * width + nx;
                if (visited.get(nIdx) == 0 && (char)maze.get(nIdx) != '#') {
                    visited.set(nIdx, 1);
                    q.insert(nIdx);
                }
            }
        }
    }
    cout << "No exit found\n";
    return 0;
}
