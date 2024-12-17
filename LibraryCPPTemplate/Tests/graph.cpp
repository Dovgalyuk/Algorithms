#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include "graph.h"

using namespace std;

const int INF = numeric_limits<int>::max();

void customAssert(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "Ошибка утверждения: " << message << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

#define CUSTOM_ASSERT(condition, message) customAssert(condition, message)

void readGraph(Graph<int, int>& g, const string& filename) {
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

    int from, to, weight;
    for (size_t i = 0; i < edges; ++i) {
        file >> from >> to >> weight;
        g.addEdge(from, to, weight);
    }
}

typedef vector<vector<int>> DistMatrix;

DistMatrix floydWarshall(const Graph<int, int>& g) {
    size_t n = g.getAllVertexLabels().size();
    DistMatrix dist(n, vector<int>(n, INF));

    for (size_t i = 0; i < n; ++i) {
        dist[i][i] = 0;
        auto it = g.neighborsBegin(i);
        while (it != g.neighborsEnd(i)) {
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

int findLongestShortestPath(const DistMatrix& dist) {
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

    DistMatrix dist = floydWarshall(g);
    int longestShortestPath = findLongestShortestPath(dist);

    cout << "Самый длинный кратчайший путь: " << longestShortestPath << endl;

    vector<int> labels = g.getAllVertexLabels();
    CUSTOM_ASSERT(labels[1] == 2, "labels[1] должно быть 2");
    CUSTOM_ASSERT(labels[2] == 3, "labels[2] должно быть 3");
    CUSTOM_ASSERT(labels[3] == 4, "labels[3] должно быть 4");
    CUSTOM_ASSERT(labels[4] == 5, "labels[4] должно быть 5");

    return 0;
}
