#include <iostream>
#include <string>
#include <fstream>
#include "vector.h"
#include "graph.h"
#include "queue.h"

using namespace std;

typedef Vector<int> IntVector;
typedef Digraph<string, int> StringGraph;

struct BFSResult {
    bool found;
    int distance;
    IntVector path;
};

struct AllShortestPathsResult {
    IntVector distances;
    Vector<IntVector> parents;
    int pathCount;
};

AllShortestPathsResult bfsAllShortestPathsBetween(const StringGraph& graph, int start, int target) {
    AllShortestPathsResult result;
    size_t n = graph.countVertices();
    result.pathCount = 0;
    
    if (start < 0 || start >= static_cast<int>(n) || target < 0 || target >= static_cast<int>(n)) {
        result.distances = IntVector(n, -1);
        result.parents = Vector<IntVector>(n);
        return result;
    }
    
    result.distances = IntVector(n, -1);
    result.parents = Vector<IntVector>(n);
    
    Queue<int> queue;
    result.distances[start] = 0;
    queue.insert(start);
    
    bool targetFound = false;
    int targetDistance = -1;
    
    while (!queue.empty() && !(targetFound && queue.get() > targetDistance)) {
        int current = queue.get();
        queue.remove();
        
        if (targetFound && result.distances[current] > targetDistance) {
            break;
        }
        
        for (auto it = graph.neighborBegin(current); it != graph.neighborEnd(current); ++it) {
            int neighbor = static_cast<int>(it.getNeighborId());
            
            if (result.distances[neighbor] == -1) {
                result.distances[neighbor] = result.distances[current] + 1;
                result.parents[neighbor].push_back(current);
                queue.insert(neighbor);
                
                if (neighbor == target) {
                    targetFound = true;
                    targetDistance = result.distances[neighbor];
                }
            } 
            else if (result.distances[neighbor] == result.distances[current] + 1) {
                result.parents[neighbor].push_back(current);
            }
        }
    }
    
    return result;
}

void countPathsRecursive(const AllShortestPathsResult& result, int current, int start, int& count) {
    if (current == start) {
        count++;
        return;
    }
    
    for (size_t i = 0; i < result.parents[current].size(); ++i) {
        int parent = result.parents[current][i];
        countPathsRecursive(result, parent, start, count);
    }
}

int countAllShortestPaths(const AllShortestPathsResult& result, int start, int target) {
    if (result.distances[target] == -1) {
        return 0;
    }
    
    int count = 0;
    countPathsRecursive(result, target, start, count);
    return count;
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
        cerr << "Example: " << argv[0] << " input.txt A D" << endl;
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

    AllShortestPathsResult result = bfsAllShortestPathsBetween(graph, startId, targetId);

    int pathCount = countAllShortestPaths(result, startId, targetId);

    if (result.distances[targetId] == -1) {
        cout << "No path found from " << startLabel << " to " << targetLabel << endl;
    }
    else {
        cout << "Shortest distance: " << result.distances[targetId] << " edge(s)" << endl;
        cout << "Number of shortest paths: " << pathCount << endl;
    }

    return 0;
}
