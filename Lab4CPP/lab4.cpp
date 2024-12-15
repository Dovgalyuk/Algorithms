#include <vector>
#include <limits>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "graph.h"

using namespace std;

// Упрощение типа графа
typedef GraphStructure<std::string, int> Graph;

void Prim(const Graph& graph) {
    size_t vertexCount = graph.getNodeCount();
    vector<bool> inMST(vertexCount, false);
    vector<int> minEdge(vertexCount, numeric_limits<int>::max());
    vector<size_t> parent(vertexCount, numeric_limits<size_t>::max());

    minEdge[0] = 0; // Начинаем с первого узла
    for (size_t count = 0; count < vertexCount - 1; count++) {
        int minWeight = numeric_limits<int>::max();
        size_t u = numeric_limits<size_t>::max();

        for (size_t v = 0; v < vertexCount; v++) {
            if (!inMST[v] && minEdge[v] < minWeight) {
                minWeight = minEdge[v];
                u = v;
            }
        }

        inMST[u] = true;

        // Итератор для обхода соседей
        auto it = graph.getIterator(u);
        while (it.hasNext()) {
            size_t v = it.next();
            int weight = graph.getConnection(u, v)->label;

            if (!inMST[v] && weight < minEdge[v]) {
                parent[v] = u;
                minEdge[v] = weight;
            }
        }
    }

    cout << "Edges in the Minimum Spanning Tree:\n";
    for (size_t i = 1; i < vertexCount; i++) {
        if (parent[i] != numeric_limits<size_t>::max()) {
            cout << "Vertex " << parent[i] << " -> Vertex " << i << " with weight " << minEdge[i] << endl;
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    int qty_vertex;
    try {
        std::ifstream inputFile(argv[1]);
        if (!inputFile.is_open()) {
            throw std::out_of_range("File opening error");
        }

        if (inputFile.peek() == std::ifstream::traits_type::eof()) {
            throw std::runtime_error("File is empty");
        }

        Graph::StructureType type = Graph::StructureType::Undirected;
        Graph graph(type);

        inputFile >> qty_vertex;
        for (int i = 0; i < qty_vertex; i++) {
            std::string vertexLabel;
            inputFile >> vertexLabel;
            graph.addNode(vertexLabel);
        }

        while (true) {
            int start, end, weight;
            inputFile >> start;
            if (start == -1) break;
            inputFile >> end >> weight;

            graph.addConnection(start, end, weight);
        }

        inputFile.close();
        Prim(graph);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}