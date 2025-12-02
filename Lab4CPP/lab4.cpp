#include "graph.h"
#include <iostream>
#include <fstream>
#include <map>
#include <limits>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "Cannot open file" << std::endl;
        return 1;
    }

    size_t N;
    infile >> N;
    Graph<std::string, double> g(N);
    std::map<std::string, size_t> name_to_index;
    std::vector<std::string> index_to_name(N);

    for (size_t i = 0; i < N; ++i) {
        std::string name;
        infile >> name;
        g.setVertexLabel(i, name);
        name_to_index[name] = i;
        index_to_name[i] = name;
    }

    std::string from, to;
    double weight;
    while (infile >> from >> to >> weight) {
        size_t u = name_to_index[from];
        size_t v = name_to_index[to];
        g.addEdge(u, v, weight);
    }

    const double INF = std::numeric_limits<double>::infinity();
    std::vector<std::vector<double>> dist(N, std::vector<double>(N, INF));

    for (size_t i = 0; i < N; ++i) {
        dist[i][i] = 0;
        for (size_t j = 0; j < N; ++j) {
            if (i == j) continue;
            auto opt = g.getEdgeLabel(i, j);
            if (opt) {
                dist[i][j] = opt.value();
            }
            else {
                dist[i][j] = INF;
            }
        }
    }

    for (size_t k = 0; k < N; ++k) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    double max_shortest = 0;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (dist[i][j] < INF && dist[i][j] > max_shortest) {
                max_shortest = dist[i][j];
            }
        }
    }
    std::cout << max_shortest << std::endl;

    return 0;
}