#include <iostream>
#include <string>
#include <fstream>
#include "vector.h"
#include "graph.h"

using namespace std;

typedef Vector<int> IntVector;
typedef Digraph<string, int> StringGraph;

struct BFSResult {
    bool found;
    int distance;
    IntVector path;
};

BFSResult bfsShortestPath(const StringGraph& graph, int start, int target) {
    BFSResult result;
    result.found = false;
    result.distance = -1;

    size_t n = graph.countVertices();
    if (start < 0 || start >= (int)n || target < 0 || target >= (int)n) {
        return result;
    }

    if (start == target) {
        result.found = true;
        result.distance = 0;
        result.path.push_back(start);
        return result;
    }

    IntVector visited(n, 0);
    IntVector distance(n, -1);
    IntVector parent(n, -1);
    IntVector queue;

    visited[start] = 1;
    distance[start] = 0;
    queue.push_back(start);

    size_t front = 0;

    while (front < queue.size()) {
        int current = queue[front];
        ++front;

        for (auto it = graph.neighborBegin(current); it != graph.neighborEnd(current); ++it) {
            int neighbor = static_cast<int>(it.getNeighborId());

            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                distance[neighbor] = distance[current] + 1;
                parent[neighbor] = current;
                queue.push_back(neighbor);

                if (neighbor == target) {
                    result.found = true;
                    result.distance = distance[neighbor];

                    int node = target;
                    while (node != -1) {
                        result.path.push_back(node);
                        node = parent[node];
                    }

                    IntVector reversedPath(result.path.size());
                    for (size_t i = 0; i < result.path.size(); ++i) {
                        reversedPath[i] = result.path[result.path.size() - 1 - i];
                    }
                    result.path = reversedPath;

                    return result;
                }
            }
        }
    }

    return result;
}

StringGraph readGraphFromFile(const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return StringGraph(0);
    }

    size_t vertexCount;
    in >> vertexCount;

    StringGraph graph(vertexCount);

    for (size_t i = 0; i < vertexCount; ++i) {
        string label;
        in >> label;
        graph.setVertexLabel(i, label);
    }

    size_t edgeCount;
    in >> edgeCount;

    for (size_t i = 0; i < edgeCount; ++i) {
        string fromLabel, toLabel;
        int weight;
        in >> fromLabel >> toLabel >> weight;

        int fromId = graph.getVertexId(fromLabel);
        int toId = graph.getVertexId(toLabel);

        if (fromId != -1 && toId != -1) {
            graph.addEdge(fromId, toId, weight);
        }
        else {
            cerr << "Warning: Invalid vertex labels in edge " << i + 1 << endl;
        }
    }

    in.close();
    return graph;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <input_file> <start_vertex> <target_vertex>" << endl;
        cerr << "Example: " << argv[0] << " input.txt A G" << endl;
        return 1;
    }

    string inputFile = argv[1];
    string startLabel = argv[2];
    string targetLabel = argv[3];

    StringGraph graph = readGraphFromFile(inputFile);

    if (graph.countVertices() == 0) {
        cerr << "Error: Failed to read graph from file" << endl;
        return 1;
    }

    int startId = graph.getVertexId(startLabel);
    int targetId = graph.getVertexId(targetLabel);

    if (startId == -1) {
        cerr << "Error: Start vertex '" << startLabel << "' not found" << endl;
        return 1;
    }

    if (targetId == -1) {
        cerr << "Error: Target vertex '" << targetLabel << "' not found" << endl;
        return 1;
    }

    cout << "Graph loaded successfully from " << inputFile << endl;
    cout << "Number of vertices: " << graph.countVertices() << endl;
    cout << "\n";

    graph.printAdjacencyMatrix();
    cout << "\n";

    cout << "Searching shortest path from '" << startLabel << "' to '" << targetLabel << "'..." << endl;
    BFSResult result = bfsShortestPath(graph, startId, targetId);

    if (!result.found) {
        cout << "No path found from " << startLabel << " to " << targetLabel << endl;
    }
    else {
        cout << "Shortest path found!" << endl;
        cout << "Distance (number of edges): " << result.distance << endl;
        cout << "Path: ";

        for (size_t i = 0; i < result.path.size(); ++i) {
            cout << graph.getVertexLabel(result.path[i]);
            if (i != result.path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }

    return 0;
}