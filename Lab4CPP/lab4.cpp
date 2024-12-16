#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include "graph.h"

using namespace std;

const int INF = numeric_limits<int>::max();

// Функция для чтения графа из файла
void readGraph(Graph<int, int>& g, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Unable to open file " << filename << endl;
        exit(1);
    }

    size_t vertices, edges;
    file >> vertices >> edges;

    for (size_t i = 0; i < vertices; ++i) {
        g.addVertex(i);
    }

    int from, to, weight;
    for (size_t i = 0; i < edges; ++i) {
        file >> from >> to >> weight;
        g.addEdge(from, to, weight);
    }
}

// Алгоритм Флойда для поиска кратчайших путей
vector<vector<int>> floydWarshall(const Graph<int, int>& g) {
    size_t n = g.getAllVertexLabels().size();
    vector<vector<int>> dist(n, vector<int>(n, INF));

    for (size_t i = 0; i < n; ++i) {
        dist[i][i] = 0;
        auto it = g.neighborsBegin(i);
        while (it != g.neighborsEnd(i)) {
            dist[i][(*it).first] = (*it).second;
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

// Функция для поиска самого длинного из кратчайших путей
int findLongestShortestPath(const vector<vector<int>>& dist) {
    int maxDist = 0;
    for (size_t i = 0; i < dist.size(); ++i) {
        for (size_t j = 0; j < dist[i].size(); ++j) {
            if (i != j && dist[i][j] != INF) {
                maxDist = max(maxDist, dist[i][j]);
            }
        }
    }
    return maxDist;
}

int main() {
    Graph<int, int> g(0);
    readGraph(g, "input.txt");

    vector<vector<int>> dist = floydWarshall(g);
    int longestShortestPath = findLongestShortestPath(dist);

    cout << "Longest shortest path: " << longestShortestPath << endl;

    return 0;
}
