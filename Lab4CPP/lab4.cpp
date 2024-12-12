#include <iostream>
#include "graph.h"
#include "vector.h"

void dfs(Graph<int, int>& graph, size_t vertex, Vector<bool>& visited) {
    visited[vertex] = true;

    for (auto it = graph.begin(vertex); it != graph.end(vertex); ++it) {
        const Graph<int, int>::vertex& neighborVertex = *it;
        size_t neighbor = neighborVertex.get_mark();
        if (!visited[neighbor]) {
            dfs(graph, neighbor, visited);
        }
    }
}

int countConnectedComponents(Graph<int, int>& graph, size_t numVertices) {
    Vector<bool> visited;
    visited.resize(numVertices, false);

    int components = 0;

    for (size_t i = 0; i < numVertices; ++i) {
        if (!visited[i]) {
            ++components;
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

    for (int i = 0; i < numVertices; i++) {
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
