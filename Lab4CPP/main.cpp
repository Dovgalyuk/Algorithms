#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "graph.h"

using graph::Graph;

static const long long INF = std::numeric_limits<long long>::max() / 4;

int main() {
    Graph<std::string, long long> g;
    try {
        g.readFrom(std::cin);
    } catch (const std::exception& e) {
        std::cerr << "Input error: " << e.what() << '\n';
        return 1;
    }

    const std::size_t n = g.vertexCount();
    std::vector<std::vector<long long>> dist(n, std::vector<long long>(n, INF));
    for (std::size_t i = 0; i < n; ++i) {
        dist[i][i] = 0;
    }

    for (std::size_t u = 0; u < n; ++u) {
        for (auto it = g.neighbors(u).begin(); it != g.neighbors(u).end(); ++it) {
            auto p = *it;
            std::size_t v = p.first;
            long long w = p.second;
            if (w < dist[u][v]) {
                dist[u][v] = w;
            }
        }
    }

    for (std::size_t k = 0; k < n; ++k) {
        for (std::size_t i = 0; i < n; ++i) {
            if (dist[i][k] == INF) continue;
            for (std::size_t j = 0; j < n; ++j) {
                if (dist[k][j] == INF) continue;
                long long cand = dist[i][k] + dist[k][j];
                if (cand < dist[i][j]) {
                    dist[i][j] = cand;
                }
            }
        }
    }

    long long best = -1;
    std::size_t bu = 0;
    std::size_t bv = 0;
    bool found = false;
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            if (i == j) continue;
            if (dist[i][j] == INF) continue;
            if (dist[i][j] > best) {
                best = dist[i][j];
                bu = i;
                bv = j;
                found = true;
            }
        }
    }

    if (!found) {
        std::cout << "No reachable pairs\n";
        return 0;
    }

    std::cout << "Longest shortest path: " << g.vertexLabel(bu) << " -> " << g.vertexLabel(bv) << " = " << best << '\n';
    return 0;
}
