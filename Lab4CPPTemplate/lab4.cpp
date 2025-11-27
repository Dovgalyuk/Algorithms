#include "dirgraph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

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
    for (size_t from = 0; from < graph.getVertexCount(); ++from) {
        auto it = graph.neighborsBegin(from);
        auto end = graph.neighborsEnd(from);
        for (; it != end; ++it) {
            size_t to = *it;

            if (from < to) {
                int weight = graph.getEdgeMark(from, to);
                edges.emplace_back(from, to, weight);
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

    while (getline(file, line)) {
        if (!line.empty()) {
            size_t pos1 = line.find(' ');
            if (pos1 != string::npos) {
                size_t pos2 = line.find(' ', pos1 + 1);
                if (pos2 != string::npos) {
                    string vertex1 = line.substr(0, pos1);
                    string vertex2 = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    int weight = stoi(line.substr(pos2 + 1));

                    if (vertexMap.find(vertex1) == vertexMap.end()) {
                        size_t id = graph.addVertex(vertex1);
                        vertexMap[vertex1] = id;
                    }
                    if (vertexMap.find(vertex2) == vertexMap.end()) {
                        size_t id = graph.addVertex(vertex2);
                        vertexMap[vertex2] = id;
                    }

                    size_t fromId = vertexMap[vertex1];
                    size_t toId = vertexMap[vertex2];
                    graph.addEdge(fromId, toId, weight);
                    graph.addEdge(toId, fromId, weight);
                }
            }
        }
    }

    file.close();

    vector<EdgeKruskal> mst = kruskalMST(graph);

    int totalWeight = 0;
    for (const auto& e : mst) {
        totalWeight += e.weight;
    }

    for (const auto& e : mst) {
        cout << graph.getVertexMark(e.from) << " "
            << graph.getVertexMark(e.to) << " "
            << e.weight << endl;
    }

    return 0;
}