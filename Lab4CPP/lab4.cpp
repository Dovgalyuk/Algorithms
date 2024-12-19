#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include "graph.h"

using namespace std;

using Data = int;

const Data INF = numeric_limits<Data>::max();

void readGraph(Graph<Data, Data>& g, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Невозможно открыть файл " << filename << endl;
        exit(1);
    }
    size_t vertices, edges;
    file >> vertices >> edges;
    for (size_t i = 0; i < vertices; ++i) {
        g.addVertex(i);
    }
    Data from, to, weight;
    for (size_t i = 0; i < edges; ++i) {
        file >> from >> to >> weight;
        g.addEdge(from, to, weight);
    }
}

vector<vector<Data>> floydWarshall(const Graph<Data, Data>& g) {
    typedef Graph<Data, Data> GraphType; 
    typedef vector<vector<Data>> DistMatrix;

    const GraphType& graph = g; 
    size_t n = graph.getAllVertexLabels().size();
    DistMatrix dist(n, vector<Data>(n, INF));
    for (size_t i = 0; i < n; ++i) {
        dist[i][i] = 0;
        auto it = graph.neighborsBegin(i);
        while (it != graph.neighborsEnd(i)) {
            dist[i][(*it).to] = (*it).label;
            ++it;
        }
    }
    for (size_t k = 0; k < n; ++k) {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    return dist;
}

Data findLongestShortestPath(const vector<vector<Data>>& dist) {
    Data maxDist = 0;
    for (size_t i = 0; i < dist.size(); ++i) {
        for (size_t j = 0; j < dist[i].size(); ++j) {
            if (i != j && dist[i][j] != INF) {
                maxDist = max(maxDist, dist[i][j]);
            }
        }
    }
    return maxDist;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Использование: " << argv[0] << " <имя_файла>" << endl;
        return 1;
    }

    string filename = argv[1];
    Graph<Data, Data> g(0);
    readGraph(g, filename);
    vector<vector<Data>> dist = floydWarshall(g);
    Data longestShortestPath = findLongestShortestPath(dist);
    cout << "Длиннейший кратчайший путь: " << longestShortestPath << endl;
    return 0;
}