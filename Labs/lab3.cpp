#include <iostream>
#include <fstream>
#include <sstream>
#include "queue.h"

struct Maze
{
    int width = 0;
    int height = 0;
    char** map = nullptr;
    bool** tag_map = nullptr;
    int** routes = nullptr;

    void Read() {
        std::ifstream file("maze.txt");
        std::string buff;
        std::string result;

        if (!file.is_open()) {
            std::cout << "File not found" << std::endl;
            return;
        }

        while (!file.eof()) {
            std::getline(file, buff);
            height++;
            for (size_t i = 0; i < buff.size(); i++)
                result += buff[i];
        }

        width = static_cast<int>(buff.size());
        file.close();
        buff.clear();

        tag_map = new bool* [height];
        routes = new int* [height];
        for (int i = 0; i < height; i++) {
            tag_map[i] = new bool[width];
            routes[i] = new int[width];
            for (int j = 0; j < width; j++) {
                tag_map[i][j] = false;
                routes[i][j] = -1;
            }
        }

        int k = 0;
        map = new char* [height];
        for (int i = 0; i < height; i++) {
            map[i] = new char[width];
            for (int j = 0; j < width; j++) {
                map[i][j] = result[k];
                k++;
            }
        }
    }
    void Delete() {
        for (int i = 0; i < height; i++) {
            delete[] map[i];
            delete[] tag_map[i];
            delete[] routes[i];
        }
        delete[] routes;
        routes = nullptr;
        delete[] map;
        map = nullptr;
        delete[] tag_map;
        tag_map = nullptr;
    }
    void Way(const int x, const int y, Queue* queue) {
        if (!tag_map[x][y]) {
            if ((map[x + 1][y] == '.' || map[x + 1][y] == 'Y') && !tag_map[x + 1][y]) {
                routes[x + 1][y] = routes[x][y] + 1;
                queue_insert(queue, x + 1);
                queue_insert(queue, y);
            }
            if ((map[x - 1][y] == '.' || map[x - 1][y] == 'Y') && !tag_map[x - 1][y]) {
                routes[x - 1][y] = routes[x][y] + 1;
                queue_insert(queue, x - 1);
                queue_insert(queue, y);
            }
            if ((map[x][y + 1] == '.' || map[x][y + 1] == 'Y') && !tag_map[x][y + 1]) {
                routes[x][y + 1] = routes[x][y] + 1;
                queue_insert(queue, x);
                queue_insert(queue, y + 1);
            }
            if ((map[x][y - 1] == '.' || map[x][y - 1] == 'Y') && !tag_map[x][y - 1]) {
                routes[x][y - 1] = routes[x][y] + 1;
                queue_insert(queue, x);
                queue_insert(queue, y - 1);
            }
            tag_map[x][y] = true;
        }
    }
    void Draw(const int x_end, const int y_end) {
        int x = x_end;
        int y = y_end;
        map[x][y] = 'Y';

        while (routes[x][y] != 2) {
            if (routes[x - 1][y] == routes[x][y] - 1) {
                x--;
                map[x][y] = 'x';
            }
            else if (routes[x + 1][y] == routes[x][y] - 1) {
                x++;
                map[x][y] = 'x';
            }
            else if (routes[x][y - 1] == routes[x][y] - 1) {
                y--;
                map[x][y] = 'x';
            }
            else if (routes[x][y + 1] == routes[x][y] - 1) {
                y++;
                map[x][y] = 'x';
            }
        }
    }
    void Find() {
        Queue* queue = queue_create();
        int x_start, y_start;
        int x_end = 0;
        int y_end = 0;
        int x, y;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (map[i][j] == 'X') {
                    x_start = i; y_start = j;
                    queue_insert(queue, x_start);
                    queue_insert(queue, y_start);

                    routes[i][j] = 1;
                }
                else if (map[i][j] == 'Y') {
                    x_end = i; y_end = j;
                }
            }
        }

        while (!queue_empty(queue)) {
            x = queue_get(queue);
            queue_remove(queue);
            y = queue_get(queue);
            queue_remove(queue);

            Way(x, y, queue);
        }

        if (!tag_map[x_end][y_end]) {
            std::cout << "IMPOSSIBLE" << std::endl;
            return;
        }
        else {
            Draw(x_end, y_end);
            Print();
        }
    }
    void Print() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++)
                std::cout << map[i][j];
            std::cout << "\n";
        }
        std::cout << std::endl;
    }
};

int main() {
    Maze Maze;
    Maze.Read();
    Maze.Print();
    Maze.Find();
    Maze.Delete();
}