#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"
#include <vector>
#include <unordered_map>

void BFS(char start, const std::unordered_map<char, std::vector<char>>& table) {
    Queue* q = queue_create();
    queue_insert(q, start);

    std::unordered_map<char, bool> visited;
    visited[start] = true;

    while (!queue_empty(q)) {
        char v = queue_get(q);
        queue_remove(q);

        if (v != start)
        {
            std::cout << v << std::endl;
        }

        for (char neighbor : table.at(v)) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue_insert(q, neighbor);
            }
        }
    }
    queue_delete(q);
}


int main(int argc, char** argv) {
    if (argc > 1)
    {
        std::ifstream input(argv[1]);
        if (!input.is_open()) {
            std::cerr << "Failed to open input file: " << "\n";
            return 1;
        }

        std::string start_line;
        std::getline(input, start_line);

        char start = start_line[0];

        std::unordered_map<char, std::vector<char>> table;
        std::string reaction;

        while (std::getline(input, reaction)) {
            char from = reaction[0];
            char in = reaction[3];
            table[from].push_back(in);

            if (table.find(in) == table.end()) {
                table[in] = {};
            }
        }

        BFS(start, table);

        input.close();
        return 0;
    }
    else {
        throw std::runtime_error("Invalid arguments");
    }
}