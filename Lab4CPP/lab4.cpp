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
    std::vector<std::vector<std::vector<size_t>>> paths(N,
        std::vector<std::vector<size_t>>(N));

    for (size_t i = 0; i < N; ++i) {
        dist[i][i] = 0;
        paths[i][i] = { i };

        for (auto it = g.beginNeighbors(i); it != g.endNeighbors(i); ++it) {
            size_t j = *it;
            auto opt = g.getEdgeLabel(i, j);
            if (opt) {
                dist[i][j] = opt.value();
                paths[i][j] = { i, j };
            }
        }
    }

    for (size_t k = 0; k < N; ++k) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF &&
                    dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];

                    paths[i][j] = paths[i][k];
                    paths[i][j].insert(paths[i][j].end(),
                        paths[k][j].begin() + 1, paths[k][j].end());
                }
            }
        }
    }

    double max_length = 0;
    std::vector<size_t> longest_path;

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (dist[i][j] < INF && dist[i][j] > max_length) {
                max_length = dist[i][j];
                longest_path = paths[i][j];
            }
        }
    }

    if (!longest_path.empty()) {
        for (size_t i = 0; i < longest_path.size(); ++i) {
            if (i > 0) std::cout << "->";
            std::cout << index_to_name[longest_path[i]];
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "No path found" << std::endl;
    }

    return 0;
}
