#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <cmath>
#include <vector>

#include "graph.h"

using GraphType = Graph<std::string, double>;
using Matrix = std::vector<std::vector<double>>;

static GraphType readGraph(int argc, char** argv)
{
    GraphType g;
    if (argc > 1) {
        std::ifstream file(argv[1]);
        if (!file)
            throw std::runtime_error(std::string("Cannot open file: ") + argv[1]);
        g.readFromStream(file);
    }
    else {
        g.readFromStream(std::cin);
    }
    return g;
}

static void checkNoNegativeCycle(const Matrix& dist)
{
    for (std::size_t i = 0; i < dist.size(); ++i)
        if (std::isnan(dist[i][i]) || dist[i][i] < 0.0)
            throw std::runtime_error("Graph contains a negative cycle");
}

static Matrix buildWeightMatrix(const GraphType& g) 
{
    const std::size_t n = g.vertexCount();
    const double INF = std::numeric_limits<double>::infinity();

    Matrix dist(n, std::vector<double>(n, INF));
    for (std::size_t i = 0; i < n; ++i)
        dist[i][i] = 0.0;

    g.forEachEdge([&](std::size_t i, std::size_t j, double w) {
        if (w < dist[i][j])
            dist[i][j] = w;
        });
    return dist;
}

static void floydWarshall(Matrix& dist)
{
    const std::size_t n = dist.size();
    for (std::size_t k = 0; k < n; ++k)
        for (std::size_t i = 0; i < n; ++i)
            for (std::size_t j = 0; j < n; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

struct Result
{
    bool found;
    double length;
    std::size_t from;
    std::size_t to;
};

static Result findLongestShortest(const Matrix& dist)
{
    const std::size_t n = dist.size();
    const double INF = std::numeric_limits<double>::infinity();
    const double NEG_INF = -std::numeric_limits<double>::infinity();

    Result r{ false, NEG_INF, 0, 0 };
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            if (i == j) continue;
            if (dist[i][j] == INF) continue;
            if (dist[i][j] > r.length) {
                r.found = true;
                r.length = dist[i][j];
                r.from = i;
                r.to = j;
            }
        }
    }
    return r;
}

static int solve(const GraphType& g)
{
    const std::size_t n = g.vertexCount();
    if (n == 0) {
        std::cout << "Empty graph: no vertices\n";
        return 0;
    }

    Matrix dist = buildWeightMatrix(g);
    floydWarshall(dist);
    checkNoNegativeCycle(dist);
    Result r = findLongestShortest(dist);

    if (!r.found) {
        std::cout << "No paths between distinct vertices\n";
        return 0;
    }

    std::cout << "Longest of shortest paths: " << r.length << "\n"
        << "Between: " << g.getVertexLabel(r.from)
        << " and " << g.getVertexLabel(r.to) << "\n";
    return 0;
}

int main(int argc, char** argv)
{
    std::ios::sync_with_stdio(false);
    try {
        GraphType g = readGraph(argc, argv);
        return solve(g);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}