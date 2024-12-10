#include "graph.h"
#include "vector.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class ComponentCounter {
public:
    ComponentCounter(Graph<std::string, std::string>& graph)
        : graph(graph), visited(graph.get_VertexAmount(), false) {}

    int countComponents() {
        int count = 0;
        for (size_t i = 0; i < graph.get_VertexAmount(); ++i) {
            if (!visited[i]) {
                dfs(i);
                count++;
            }
        }
        return count;
    }

private:
    void dfs(size_t vertex) {
        visited[vertex] = true;
        Graph<std::string, std::string>::Iterator it = graph.get_Iterator(vertex);
        while (it.hasNext()) {
            size_t adjacent = it.next();
            if (!visited[adjacent]) {
                dfs(adjacent);
            }
        }
    }

    Graph<std::string, std::string>& graph;
    std::vector<bool> visited;
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    size_t vertexCount, edgeCount;
    inputFile >> vertexCount >> edgeCount;

    Graph<std::string, std::string> graph;

    for (size_t i = 0; i < vertexCount; ++i) {
        std::string vertexLabel;
        inputFile >> vertexLabel;
        graph.add_Vertex(vertexLabel);
    }

    for (size_t i = 0; i < edgeCount; ++i) {
        size_t from, to;
        inputFile >> from >> to;
        if (from < vertexCount && to < vertexCount) {
            graph.add_Edge(from, to, "");
        }
        else {
            std::cout << "Invalid vertex index in edges. Skipping this edge." << std::endl;
        }
    }

    inputFile.close();

    ComponentCounter counter(graph);
    int components = counter.countComponents();
    std::cout << "Number of related components: " << components << std::endl;

    return 0;
}
