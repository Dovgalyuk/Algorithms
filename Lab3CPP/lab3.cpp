#include <iostream>
#include "queue.h"
#include <fstream>
#include <string>
#include <vector>


using namespace std;


void BFS(char start, const std::unordered_map<char, std::vector<char>>& graph) {
    Queue* q = queue_create();

    std::unordered_map<char, bool> visited;

    queue_insert(q, start);
    visited[start] = true;

    while (!queue_empty(q)) {
        char v = queue_get(q);
        queue_remove(q);

        if(v != start)
        {
            std::cout << v << std::endl;
        }

        for (char neighbor : graph.at(v)) {
            if (!visited[neighbor]) {
              visited[neighbor] = true;
                queue_insert(q, neighbor);
            }
        }
    }

    queue_delete(q);
}

int main(int argc, char **argv) {
    std::ifstream file(argv[1]);

    std::unordered_map<char, std::vector<char>> graph;
    std::string start;
    std::string input;

    getline(file, start);

    while (std::getline(file, input)){
        char from = input[0];
        char to = input[3];

        graph[from].push_back(to);

        if (graph.find(to) == graph.end()) {
            graph[to] = {};
        }
    }


    BFS(start[0], graph);


    return 0;
}

