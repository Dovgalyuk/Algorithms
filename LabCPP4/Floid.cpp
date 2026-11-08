#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <optional>
#include <vector>

#include "graph.h"

using GraphType = Graph<std::string, double>;
using Matrix = Vector<Vector<std::optional<double>>>;

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
        if (dist.get(i).get(i).has_value() && *dist.get(i).get(i) < 0.0)
            throw std::runtime_error("Graph contains a negative cycle");
}

static void floydWarshall(Matrix& dist)
{
    const std::size_t n = dist.size();
    for (std::size_t k = 0; k < n; ++k)
        for (std::size_t i = 0; i < n; ++i) {
            const std::optional<double> dik = dist.get(i).get(k);
            if (!dik.has_value())
                continue;

            for (std::size_t j = 0; j < n; ++j) {
                const std::optional<double> dkj = dist.get(k).get(j);
                if (!dkj.has_value())
                    continue;

                const double sum = *dik + *dkj;
                const std::optional<double> dij = dist.get(i).get(j);
                if (!dij.has_value() || sum < *dij) {
                    Vector<std::optional<double>> row = dist.get(i);
                    row.set(j, sum);
                    dist.set(i, row);
                }
            }
        }
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
    const double NEG_INF = -std::numeric_limits<double>::infinity();

    Result r{ false, NEG_INF, 0, 0 };
    for (std::size_t i = 0; i < n; ++i)
        for (std::size_t j = 0; j < n; ++j) {
            if (i == j)
                continue;
            if (!dist.get(i).get(j).has_value())
                continue;
            if (*dist.get(i).get(j) > r.length) {
                r.found = true;
                r.length = *dist.get(i).get(j);
                r.from = i;
                r.to = j;
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

    GraphType temp = g;
    const std::vector<std::string> labels = temp.getAllVertexLabels();
    for (const std::string& v : labels)
        if (!temp.hasEdge(v, v))
            temp.setEdgeLabel(v, v, 0.0);
    Matrix dist = temp.adjacencyMatrix();
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