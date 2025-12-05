#include "dirgraph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>

using namespace std;

struct EdgeKruskal {
    size_t from;
    size_t to;
    int weight;

    EdgeKruskal(size_t f, size_t t, int w) : from(f), to(t), weight(w) {}

    bool operator<(const EdgeKruskal& other) const {
        return weight < other.weight;
    }
};

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

    size_t find(size_t x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(size_t x, size_t y) {
        size_t px = find(x);
        size_t py = find(y);

        if (px == py) {
            return false;
        }

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

vector<EdgeKruskal> getAllEdges(const DirGraph<string, int>& graph) {
    vector<EdgeKruskal> edges;
    for (size_t i = 0; i < graph.getVertexCount(); ++i) {
        for (auto it = graph.neighborsBegin(i); it != graph.neighborsEnd(i); ++it) {
            size_t j = *it;
            if (i < j) { 
                int weight = graph.getEdgeMark(i, j);
                edges.emplace_back(i, j, weight);
            }
        }
    }
    return edges;
}


vector<EdgeKruskal> kruskalMST(DirGraph<string, int>& graph) {
    size_t n = graph.getVertexCount();
    if (n < 2) return {};

    vector<EdgeKruskal> edges = getAllEdges(graph);
    sort(edges.begin(), edges.end());

    DisjointSet dsu(n);
    vector<EdgeKruskal> mst;

    for (const auto& edge : edges) {
        if (dsu.unite(edge.from, edge.to)) {
            mst.push_back(edge);
            if (mst.size() == n - 1) {
                break;
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

    DirGraph<string, int> graph;
    map<string, size_t> vertexMap;
    string line;

    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string v1, v2;
        int weight;

        if (iss >> v1 >> v2 >> weight) {

            if (vertexMap.find(v1) == vertexMap.end()) {
                vertexMap[v1] = graph.addVertex(v1);
            }

            if (vertexMap.find(v2) == vertexMap.end()) {
                vertexMap[v2] = graph.addVertex(v2);
            }

            size_t fromId = vertexMap[v1];
            size_t toId = vertexMap[v2];
            graph.addEdge(fromId, toId, weight);
            graph.addEdge(toId, fromId, weight);
        }
    }

    file.close();

    vector<EdgeKruskal> mst = kruskalMST(graph);

    for (const auto& e : mst) {
        cout << graph.getVertexMark(e.from) << " "
            << graph.getVertexMark(e.to) << " "
            << e.weight << endl;
    }

    return 0;
}

