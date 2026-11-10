#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

#include "graph.h"

using GraphType = Graph<std::string, double>;

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

static void floydWarshall(GraphType& g)
{
    const std::size_t n = g.vertexCount();

    for (std::size_t k = 0; k < n; ++k) {
        const std::string vk = g.getVertexLabel(k);

        for (std::size_t i = 0; i < n; ++i) {
            if (i == k)
                continue;
            const std::string vi = g.getVertexLabel(i);
            if (!g.hasEdge(vi, vk))
                continue;
            const double dik = g.getEdgeLabel(vi, vk);

            for (std::size_t j = 0; j < n; ++j) {
                if (j == k)
                    continue;
                const std::string vj = g.getVertexLabel(j);
                if (!g.hasEdge(vk, vj))
                    continue;
                const double dkj = g.getEdgeLabel(vk, vj);

                const double sum = dik + dkj;

                if (i == j) {
                    if (sum < 0.0)
                        g.setEdgeLabel(vi, vj, sum);
                    continue;
                }

                if (!g.hasEdge(vi, vj) || sum < g.getEdgeLabel(vi, vj))
                    g.setEdgeLabel(vi, vj, sum);
            }
        }
    }

    for (std::size_t i = 0; i < n; ++i) {
        const std::string vi = g.getVertexLabel(i);
        if (g.hasEdge(vi, vi) && g.getEdgeLabel(vi, vi) < 0.0)
            throw std::runtime_error("Graph contains a negative cycle");
    }
}

struct Result
{
    bool found;
    double length;
    std::size_t from;
    std::size_t to;
};

static Result findLongestShortest(const GraphType& g)
{
    const std::size_t n = g.vertexCount();
    const double NEG_INF = -std::numeric_limits<double>::infinity();

    Result r{ false, NEG_INF, 0, 0 };
    for (std::size_t i = 0; i < n; ++i) {
        const std::string vi = g.getVertexLabel(i);
        for (std::size_t j = 0; j < n; ++j) {
            if (i == j)
                continue;
            const std::string vj = g.getVertexLabel(j);
            if (!g.hasEdge(vi, vj))
                continue;

            const double current = g.getEdgeLabel(vi, vj);
            if (current > r.length) {
                r.found = true;
                r.length = current;
                r.from = i;
                r.to = j;
            }
        }
    }
    return r;
}

static int solve(GraphType g)
{
    const std::size_t n = g.vertexCount();
    if (n == 0) {
        std::cout << "Empty graph: no vertices\n";
        return 0;
    }

    floydWarshall(g);
    const Result r = findLongestShortest(g);

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
