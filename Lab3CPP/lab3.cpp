#include <iostream>
#include "queue.h"
#include "vector.h"
#include <fstream>
#include <vector>
#include <string>
#include <utility>


const int dx[4] = { -1, 1, 0, 0 };
const int dy[4] = { 0, 0, -1, 1 };

bool is_valid(size_t x, size_t y, const std::vector<std::vector<std::string>>& desk, const std::vector<std::vector<bool>>& visited) {
    return x >= 0 && x < desk.size() && y >= 0 && y < desk[0].size() && desk[x][y] != "#" && !visited[x][y];
}

int bfs(std::vector<std::vector<std::string>>& desk, int start_x, int start_y) {
    size_t rows = desk.size();
    size_t cols = desk[0].size();
    //std::cout << "Check0" << std::endl;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    Queue* queue = queue_create();

	//std::cout << "Check1" << std::endl;

    std::pair<int, int> start = { start_x, start_y };
    queue_insert(queue, start);

    //std::cout << "Check2" << std::endl;

    visited[start_x][start_y] = true;

    int steps = 1;

    while (!queue_empty(queue)) {
        std::pair<int, int> p = queue_get(queue);
        queue_remove(queue);
        //std::cout << "Check3" << std::endl;

        for (int i = 0; i < 4; i++) {
            int nx = p.first + dx[i];
			int ny = p.second + dy[i];

            if (is_valid(nx, ny, desk, visited)) {
                visited[nx][ny] = true;
                std::pair<int, int> new_point = { nx, ny };
                queue_insert(queue, new_point);
                steps++;
            }
        }
    }
    queue_delete(queue);

    for (size_t i = 0; i < desk.size(); i++) {
        for (size_t j = 0; j < desk[i].size(); j++) {
            if (visited[i][j] && desk[i][j] == "." || visited[i][j] && desk[i][j] == "X") {
                desk[i][j] = "x";
            }
        }
    }


    //std::cout << "Check4" << std::endl;

    return steps;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    std::vector<std::vector<std::string>> desk;

    std::string filename = argv[1];

    std::string str;
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cout << "File not found" << std::endl;
        return 1;
    }

    while (std::getline(inputFile, str)) {
        std::vector<std::string> row;
        for (size_t i = 0; i < str.size(); i++) {
            row.push_back(std::string(1, str[i]));
        }
        desk.push_back(row);
    }
    int start_x = -1, start_y = -1;
    for (size_t i = 0; i < desk.size(); i++) {
        for (size_t j = 0; j < desk[i].size(); j++) {
            if (desk[i][j] == "X") {
                start_x = i;
                start_y = j;
                break;
            }
        }
        if (start_x != -1) break;
    }

    if (start_x == -1) {
        std::cerr << "Start point not found!" << std::endl;
        return 1;
    }

    int steps = bfs(desk, start_x, start_y);
    std::cout << steps << std::endl;

    for (size_t i = 0; i < desk.size(); i++) {
        for (size_t j = 0; j < desk[i].size(); j++) {
            std::cout << desk[i][j];
        }
        std::cout << std::endl;
    }

    //std::cout << "Done" << std::endl;
    return 0;
}