#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "queue.h"

using namespace std;

int main(int argc, char* argv[]) {
    vector<string> maze;
    string line;
    ifstream fileStream;
    istream* inputSource = &cin;

    if (argc > 1) {
        fileStream.open(argv[1]);
        if (fileStream.is_open()) {
            inputSource = &fileStream;
        }
    }

    while (getline(*inputSource, line)) {
        if (!line.empty()) {
            if (line.back() == '\r') line.pop_back();
            maze.push_back(line);
        }
    }

    if (maze.empty()) return 1;
    int height = maze.size();
    int width = maze[0].size();
    int startX = -1, startY = -1;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (maze[y][x] == 'X') {
                startX = x;
                startY = y;
                break;
            }
        }
    }

    if (startX == -1) return 1;
    Queue* queue = queue_create();
    queue_insert(queue, startY * width + startX);
    int reachableCount = 1;
    maze[startY][startX] = 'x';
    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };
    while (!queue_empty(queue)) {
        int currentPacked = queue_get(queue);
        queue_remove(queue);
        int cy = currentPacked / width;
        int cx = currentPacked % width;
        for (int i = 0; i < 4; ++i) {
            int ny = cy + dy[i];
            int nx = cx + dx[i];
            if (ny >= 0 && ny < height && nx >= 0 && nx < width) {
                if (maze[ny][nx] == '.') {
                    maze[ny][nx] = 'x';
                    reachableCount++;
                    queue_insert(queue, ny * width + nx);
                }
            }
        }
    }
    queue_delete(queue);
    cout << reachableCount << endl;
    for (const auto& row : maze) {
        cout << row << endl;
    }
    return 0;
}