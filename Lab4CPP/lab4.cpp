#include <iostream>
#include "graph.h"
#include <string>

void dfs(Graph<int, int>& graph, size_t vertex, std::vector<int>& visited) {
    if (vertex >= visited.size()) {
        std::string b = "vertex out of range " + (char)vertex;
        throw std::invalid_argument(b);
    }
    visited[vertex] = 1;

    for (auto it = graph.begin(vertex); it != graph.end(vertex); it++) {
        size_t neighbor = (*it).get_mark();
        if (neighbor >= visited.size()) {
            std::string b = "neighbor out of range " + (char)neighbor;
            throw std::invalid_argument(b);
        }
        if (visited[neighbor] == 0) {
            dfs(graph, neighbor, visited);
        }
    }
}

int countConnectedComponents(Graph<int, int>& graph, size_t numVertices) {
    std::vector<int> visited;
    visited.resize(numVertices, 0);

    int components = 0;

    for (size_t i = 0; i < numVertices; i++) {
        
        if (visited[i] == 0) {
            if (i >= visited.size()) {
                std::string b = "i out of range " + (char)i;
                throw std::invalid_argument(b);
            }
            components++;
            dfs(graph, i, visited);
        }
    }

    return components;
}

int main(int argc, char **argv) {
    FILE *input;
    if (argc <= 1) {
        input = stdin;
    } else {
        input = fopen(argv[1], "r");
    }

    int numVertices, numEdges;
    if (fscanf(input, "%d %d", &numVertices, &numEdges) < 1) {
        throw std::invalid_argument("Invalid argument");
    }

    Graph<int, int> graph(numVertices);

    for (int i = 0; i < numEdges; i++) {
        int from, to;
        if (fscanf(input, "%d %d", &from, &to) < 1) {
            throw std::invalid_argument("Invalid argument");
        }   
        graph.add_edge(from, to, 1);
    }

    int components = countConnectedComponents(graph, numVertices);
    FILE* output = fopen("output.txt", "w");
    fprintf(output, "%d", components);

    fclose(input);
    fclose(output);

    return 0;
}
