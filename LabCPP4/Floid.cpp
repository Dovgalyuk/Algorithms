#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "graph.h"

using GraphType = Graph<std::string, double>;
using Matrix = std::vector<std::vector<double>>;
using IndexMap = std::unordered_map<std::string, std::size_t>;

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

static IndexMap buildIndexMap(const GraphType& g)
{
    IndexMap index;
    for (std::size_t i = 0; i < g.vertexCount(); ++i)
        index[g.getVertexLabel(i)] = i;
    return index;
}

static Matrix buildWeightMatrix(const GraphType& g, const IndexMap& index)
{
    const std::size_t n = g.vertexCount();
    const double INF = std::numeric_limits<double>::infinity();

    Matrix dist(n, std::vector<double>(n, INF));
    for (std::size_t i = 0; i < n; ++i)
        dist[i][i] = 0.0;

    for (std::size_t i = 0; i < n; ++i) {
        const std::string from = g.getVertexLabel(i);
        for (auto it = g.neighborsBegin(from); it != g.neighborsEnd(from); ++it) {
            std::string to = *it;
            double w = g.getEdgeLabel(from, to);
            std::size_t j = index.at(to);
            dist[i][j] = w;
        }
    }
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

    IndexMap index = buildIndexMap(g);
    Matrix dist = buildWeightMatrix(g, index);
    floydWarshall(dist);
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