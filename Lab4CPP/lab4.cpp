#include "graph.h"
#include "vector.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
using namespace std;

typedef Graph<string, int> StringIntGraph;

void primMST(const StringIntGraph& graph) {  
    size_t n = graph.getVertexCount();
    if (n == 0) {
        cout << "Graph is empty!" << endl;
        return;
    }

    Vector<bool> inMST(n, false);
    Vector<int> key(n, numeric_limits<int>::max());
    Vector<size_t> parent(n, static_cast<size_t>(-1));

    key.set(0, 0);

    for (size_t count = 0; count < n; ++count) {
        int minKey = numeric_limits<int>::max();
        size_t minIndex = 0;

        for (size_t v = 0; v < n; ++v) {
            if (!inMST.get(v) && key.get(v) < minKey) {
                minKey = key.get(v);
                minIndex = v;
            }
        }

        inMST.set(minIndex, true);

        auto it = graph.getIterator(minIndex);
        while (it.hasNext()) {
            size_t neighbor = it.next();
            int weight = graph.getEdgeLabel(minIndex, neighbor);

            if (!inMST.get(neighbor) && weight < key.get(neighbor)) {
                parent.set(neighbor, minIndex);
                key.set(neighbor, weight);
            }
        }
    }

    int totalWeight = 0;
    for (size_t i = 1; i < n; ++i) {
        if (parent.get(i) != static_cast<size_t>(-1)) {
            totalWeight += graph.getEdgeLabel(parent.get(i), i);
        }
    }
    cout << totalWeight << endl;
}

int main(int argc, char* argv[]) {
    const char* filename = "input.txt";

    if (argc > 1) {
        filename = argv[1];
    }

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error: cannot open file " << filename << endl;
        return 1;
    }

    size_t vertexCount;
    inputFile >> vertexCount;
    inputFile.ignore();

    StringIntGraph graph(vertexCount);  

    for (size_t i = 0; i < vertexCount; ++i) {
        string label;
        getline(inputFile, label);
        graph.setVertexLabel(i, label);
    }

    string line;
    while (getline(inputFile, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        size_t from, to;
        int weight;

        if (!(iss >> from >> to >> weight)) {
            cerr << "Error: invalid edge format in line: " << line << endl;
            continue;
        }

        if (from >= vertexCount || to >= vertexCount) {
            cerr << "Error: vertex index out of range in line: " << line << endl;
            continue;
        }

        graph.addEdge(from, to, weight);
    }

    primMST(graph);

    return 0;
}