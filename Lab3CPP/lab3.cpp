#include <iostream>
#include <string>
#include <fstream>
#include "queue.h"

const int INF = 1000000000;

struct Point {
    int x, y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
};

const int move_size = 4;
const Point move[move_size] = { Point(-1,0), Point(1,0), Point(0,-1), Point(0,1) };

char fnd(char* maze, int height, int width, Point start) {
    int* dist = new int[height * width];
    for (int i = 0; i < height * width; ++i) {
        dist[i] = INF;
    }

    Queue* queue = queue_create();

    int startIndex = start.y * width + start.x;
    dist[startIndex] = 0;
    queue_insert(queue, startIndex);

    char result = '-';

    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove(queue);

        int cur_x = current % width;
        int cur_y = current / width;

        char current_char = maze[current];
        if (current_char >= '0' && current_char <= '9') {
            result = current_char;
            break;
        }

        int cur_dist = dist[current];

        for (int i = 0; i < move_size; i++) {
            int new_x = cur_x + move[i].x;
            int new_y = cur_y + move[i].y;

            if (new_x < 0 || new_x >= width || new_y < 0 || new_y >= height) {
                continue;
            }

            int newIndex = new_y * width + new_x;
            char c = maze[newIndex];

            if (c == '#') {
                continue;
            }

            int new_dist = cur_dist + 1;
            if (new_dist < dist[newIndex]) {
                dist[newIndex] = new_dist;
                queue_insert(queue, newIndex);
            }
        }
    }

    queue_delete(queue);
    delete[] dist;
    return result;
}

void task(std::ifstream& file) {
    std::string line;
    size_t width = 0, height = 0;
    std::string maze_str;

    Point start(-1, -1);

    while (std::getline(file, line)) {
        if (line.empty()) break;
        if (width == 0) width = line.size();
        maze_str += line;
        for (size_t x = 0; x < width; ++x) {
            if (line[x] == 'X') {
                start = Point(static_cast<int>(x), static_cast<int>(height));
            }
        }
        height++;
    }

    int w = static_cast<int>(width);
    int h = static_cast<int>(height);

    char* maze = new char[w * h];
    for (int i = 0; i < w * h; ++i) {
        maze[i] = maze_str[i];
    }

    char result = fnd(maze, h, w, start);
    std::cout << result << std::endl;

    delete[] maze;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }
    std::ifstream file(argv[1]);
    task(file);
    file.close();
}
