#include <iostream>
#include "graph.h"
#include <string>

void dfs(Graph<int, int>& graph, size_t vertex, std::vector<int>& visited) {
    if (vertex >= visited.size()) {
        throw std::invalid_argument("vertex out of bounds");
    }
    std::cout << "Visiting vertex: " << vertex << std::endl;
    visited[vertex] = 1;

    for (auto it = graph.begin(vertex); it != graph.end(vertex); it++) {
        try {
            size_t neighbor = (*it).get_mark();
            std::cout << "Checking neighbor: " << neighbor << " from vertex: " << vertex << std::endl;

            if (neighbor >= visited.size()) {
                std::cerr << "Invalid neighbor: " << neighbor << " for vertex: " << vertex << std::endl;
                throw std::invalid_argument("neighbor out of bounds");
            }

            if (visited[neighbor] == 0) {
                dfs(graph, neighbor, visited);
            }
        } catch (const std::exception& e) {
            std::cerr << "Error while processing neighbor: " << e.what() << std::endl;
            throw;
        }
    }
}


int countConnectedComponents(Graph<int, int>& graph, size_t numVertices) {
    std::vector<int> visited;
    visited.resize(numVertices, 0);

    int components = 0;

    for (size_t i = 0; i < numVertices; i++) {
        if (i >= visited.size()) {
            throw std::invalid_argument("i out of bounds");
        }
        if (visited[i] == 0) {
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
    if (fscanf(input, "%d %d", &numVertices, &numEdges) < 2) {
        throw std::invalid_argument("Invalid input format");
    }

    Graph<int, int> graph(numVertices);

    for (int i = 0; i < numEdges; i++) {
        int from, to;
        if (fscanf(input, "%d %d", &from, &to) < 2) {
            throw std::invalid_argument("Invalid edge input");
        }
        if (from < 0 || to < 0 || from >= numVertices || to >= numVertices) {
            throw std::out_of_range("Edge indices out of bounds");
        }
        graph.add_edge(from, to, 1);
    }

    graph.print_graph();

    int components = countConnectedComponents(graph, numVertices);
    FILE* output = fopen("output.txt", "w");
    fprintf(output, "%d", components);

    fclose(input);
    fclose(output);

    return 0;
}
