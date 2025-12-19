#include "dirgraph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>

using namespace std;

typedef DirGraph<string, int> Graph;
typedef Graph::VertexId VertexId;

// Structure to store edge info for Kruskal's algorithm
struct EdgeKruskal {
    size_t from;    // start vertex id
    size_t to;      // end vertex id
    int weight;     // edge weight

    EdgeKruskal(size_t f, size_t t, int w) : from(f), to(t), weight(w) {}

    // For sorting edges by weight
    bool operator<(const EdgeKruskal& other) const {
        return weight < other.weight;
    }
};

typedef vector<EdgeKruskal> EdgeVector;

// Disjoint set (union-find) data structure for Kruskal
class DisjointSet {
private:
    vector<size_t> parent;
    vector<size_t> rank;

public:
    DisjointSet(size_t size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (size_t i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    // Find root of set containing x with path compression
    size_t find(size_t x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Unite two sets, return true if merged
    bool unite(size_t x, size_t y) {
        size_t px = find(x);
        size_t py = find(y);

        if (px == py) {
            return false; // already in same set
        }

        // Union by rank
        if (rank[px] < rank[py]) {
            parent[px] = py;
        }
        else {
            parent[py] = px;
            if (rank[px] == rank[py]) {
                ++rank[px];
            }
        }
        return true;
    }
};

EdgeVector getAllEdges(const Graph& graph) {
    EdgeVector edges;  
    size_t n = graph.getVertexCount();

    // Iterate over all vertices
    for (size_t i = 0; i < n; ++i) {
        for (auto it = graph.neighborsBegin(i); it != graph.neighborsEnd(i); ++it) {
            VertexId j = *it;
            int weight = graph.getEdgeMark(i, j);
            edges.emplace_back(i, j, weight);
        }
    }
    return edges;
}

EdgeVector kruskalMST(Graph& graph) {
    size_t n = graph.getVertexCount();
    if (n < 2) return {};

    // Get all edges and sort by weight ascending (stonks)
    EdgeVector edges = getAllEdges(graph);  
    sort(edges.begin(), edges.end());

    DisjointSet dsu(n);
    EdgeVector mst;  

    // Iterate edges, add to MST if they connect two different sets
    for (const auto& edge : edges) {
        if (dsu.unite(edge.from, edge.to)) {
            mst.push_back(edge);
            if (mst.size() == n - 1) {
                break; // MST complete
            }
        }
    }
    return mst;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        return 1;
    }

    Graph graph;
    map<string, VertexId> vertexMap;
    string line;

    // Read each line: "vertex1 vertex2 weight"
    while (getline(file, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string v1, v2;
        int weight;

        if (iss >> v1 >> v2 >> weight) {
            // Add vertex if not exists
            if (vertexMap.find(v1) == vertexMap.end()) {
                vertexMap[v1] = graph.addVertex(v1);
            }
            if (vertexMap.find(v2) == vertexMap.end()) {
                vertexMap[v2] = graph.addVertex(v2);
            }

            VertexId fromId = vertexMap[v1];
            VertexId toId = vertexMap[v2];
            // Add edge in both directions to simulate undirected graph!!!
            graph.addEdge(fromId, toId, weight);
            graph.addEdge(toId, fromId, weight);
        }
    }
    file.close();

    // Find minimal spanning tree edges with Kruskal
    EdgeVector mst = kruskalMST(graph);  

    // Output MST edges with vertex names and weights
    for (const auto& e : mst) {
        cout << graph.getVertexMark(e.from) << " "
            << graph.getVertexMark(e.to) << " "
            << e.weight << endl;
    }

    return 0;
}
