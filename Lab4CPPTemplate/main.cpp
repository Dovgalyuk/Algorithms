#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <vector>

#include "graph.h"

using GridGraph = Graph<std::string, double>;
using Vertex = GridGraph::VertexIndex;

static Vertex cell_index(size_t row, size_t col, size_t cols)
{
    return static_cast<Vertex>(row * cols + col);
}

struct Node
{
    double priority;
    Vertex vertex;
    bool operator>(const Node& other) const { return priority > other.priority; }
};

static bool run_astar(GridGraph& graph,
    size_t rows,
    size_t cols,
    Vertex start,
    Vertex goal,
    double min_cost,
    std::vector<Vertex>& path,
    double& total_cost)
{
    const size_t total = rows * cols;
    const double inf = std::numeric_limits<double>::infinity();
    std::vector<double> g(total, inf);
    std::vector<Vertex> parent(total, total);
    auto heuristic = [&](Vertex v) -> double {
        if (min_cost <= 0.0)
        {
            return 0.0;
        }
        size_t r1 = v / cols;
        size_t c1 = v % cols;
        size_t r2 = goal / cols;
        size_t c2 = goal % cols;
        return (std::abs(static_cast<long>(r1) - static_cast<long>(r2)) +
            std::abs(static_cast<long>(c1) - static_cast<long>(c2))) *
            min_cost;
        };

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    g[start] = 0.0;
    pq.push({ heuristic(start), start });

    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();
        if (cur.vertex == goal)
        {
            break;
        }
        if (cur.priority > g[cur.vertex] + heuristic(cur.vertex))
        {
            continue;
        }
        for (auto it = graph.neighbors(cur.vertex); it.valid(); it.next())
        {
            Vertex next = it.vertex();
            double tentative = g[cur.vertex] + it.label();
            if (tentative < g[next])
            {
                g[next] = tentative;
                parent[next] = cur.vertex;
                pq.push({ tentative + heuristic(next), next });
            }
        }
    }

    if (g[goal] == inf)
    {
        return false;
    }

    total_cost = g[goal];
    for (Vertex v = goal;; v = parent[v])
    {
        path.push_back(v);
        if (v == start)
        {
            break;
        }
        if (parent[v] >= total)
        {
            return false;
        }
    }
    std::reverse(path.begin(), path.end());
    return true;
}

int main(int argc, char** argv)
{
    std::istream* input = &std::cin;
    std::ifstream file;
    if (argc > 1)
    {
        file.open(argv[1]);
        input = &file;
    }

    size_t rows = 0;
    size_t cols = 0;
    *input >> rows >> cols;

    size_t sr = 0, sc = 0, gr = 0, gc = 0;
    *input >> sr >> sc >> gr >> gc;

    std::vector<double> costs(rows * cols, 0.0);
    double min_cost = std::numeric_limits<double>::infinity();
    for (size_t r = 0; r < rows; ++r)
    {
        for (size_t c = 0; c < cols; ++c)
        {
            double value = 0.0;
            *input >> value;
            costs[cell_index(r, c, cols)] = value;
            if (value > 0.0 && value < min_cost)
            {
                min_cost = value;
            }
        }
    }
    if (min_cost == std::numeric_limits<double>::infinity())
    {
        min_cost = 0.0;
    }

    GridGraph graph(rows * cols);
    for (size_t r = 0; r < rows; ++r)
    {
        for (size_t c = 0; c < cols; ++c)
        {
            char row_char = static_cast<char>('A' + (r % 26));
            std::string label(1, row_char);
            label += std::to_string(c + 1);
            graph.set_vertex_label(cell_index(r, c, cols), label);
        }
    }

    const int dr[4] = { -1, 1, 0, 0 };
    const int dc[4] = { 0, 0, -1, 1 };
    for (size_t r = 0; r < rows; ++r)
    {
        for (size_t c = 0; c < cols; ++c)
        {
            auto from = cell_index(r, c, cols);
            for (int dir = 0; dir < 4; ++dir)
            {
                long nr = static_cast<long>(r) + dr[dir];
                long nc = static_cast<long>(c) + dc[dir];
                if (nr < 0 || nc < 0 || nr >= static_cast<long>(rows) || nc >= static_cast<long>(cols))
                {
                    continue;
                }
                auto to = cell_index(static_cast<size_t>(nr), static_cast<size_t>(nc), cols);
                graph.add_edge(from, to, costs[to]);
            }
        }
    }

    Vertex start = cell_index(sr, sc, cols);
    Vertex goal = cell_index(gr, gc, cols);

    std::vector<Vertex> path;
    double total_cost = 0.0;
    run_astar(graph, rows, cols, start, goal, min_cost, path, total_cost);

    std::cout << "Total cost: " << total_cost << "\nPath: ";
    for (size_t i = 0; i < path.size(); ++i)
    {
        if (i)
        {
            std::cout << " -> ";
        }
        std::cout << graph.get_vertex_label(path[i]);
    }
    std::cout << "\n";
    return 0;
}
