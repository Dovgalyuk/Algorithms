#include <algorithm>
#include <cmath>
#include <functional>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <vector>

#include "graph.h"

using GridGraph = Graph<std::string, double>;

struct AStarResult
{
    bool found = false;
    double cost = 0.0;
    std::vector<GridGraph::VertexIndex> path;
};

static GridGraph::VertexIndex cell_index(size_t row, size_t col, size_t cols)
{
    return row * cols + col;
}

static std::string cell_name(size_t row, size_t col)
{
    return "cell_" + std::to_string(row) + "_" + std::to_string(col);
}

static AStarResult run_astar(GridGraph &graph,
                             const std::vector<std::vector<double>> &costs,
                             size_t rows,
                             size_t cols,
                             GridGraph::VertexIndex start,
                             GridGraph::VertexIndex goal)
{
    const size_t total = rows * cols;
    const double inf = std::numeric_limits<double>::infinity();

    std::vector<double> g_score(total, inf);
    std::vector<double> f_score(total, inf);
    std::vector<GridGraph::VertexIndex> came_from(total, total);

    double min_move_cost = inf;
    for (const auto &row : costs)
    {
        for (double value : row)
        {
            if (value > 0.0 && value < min_move_cost)
            {
                min_move_cost = value;
            }
        }
    }
    if (!std::isfinite(min_move_cost))
    {
        min_move_cost = 0.0;
    }

    auto heuristic = [&](GridGraph::VertexIndex idx) {
        size_t row = idx / cols;
        size_t col = idx % cols;
        size_t goal_row = goal / cols;
        size_t goal_col = goal % cols;
        double manhattan = std::abs(static_cast<double>(static_cast<long long>(row) - static_cast<long long>(goal_row))) +
                           std::abs(static_cast<double>(static_cast<long long>(col) - static_cast<long long>(goal_col)));
        return manhattan * min_move_cost;
    };

    struct Node
    {
        double f;
        GridGraph::VertexIndex idx;
        bool operator>(const Node &other) const { return f > other.f; }
    };

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open_set;

    g_score[start] = 0.0;
    f_score[start] = heuristic(start);
    open_set.push({f_score[start], start});

    while (!open_set.empty())
    {
        Node current = open_set.top();
        open_set.pop();

        if (current.idx == goal)
        {
            break;
        }
        if (current.f > f_score[current.idx])
        {
            continue;
        }

        for (auto it = graph.neighbors(current.idx); it.valid(); it.next())
        {
            auto neighbor = it.vertex();
            double tentative_g = g_score[current.idx] + it.label();
            if (tentative_g < g_score[neighbor])
            {
                came_from[neighbor] = current.idx;
                g_score[neighbor] = tentative_g;
                f_score[neighbor] = tentative_g + heuristic(neighbor);
                open_set.push({f_score[neighbor], neighbor});
            }
        }
    }

    AStarResult result;
    if (!std::isfinite(g_score[goal]))
    {
        return result;
    }

    result.found = true;
    result.cost = g_score[goal];

    std::vector<GridGraph::VertexIndex> path;
    for (GridGraph::VertexIndex v = goal;; v = came_from[v])
    {
        path.push_back(v);
        if (v == start)
        {
            break;
        }
        if (came_from[v] >= total)
        {
            result.found = false;
            return result;
        }
    }
    std::reverse(path.begin(), path.end());
    result.path = std::move(path);
    return result;
}

int main(int argc, char **argv)
{
    std::istream *input = &std::cin;
    std::ifstream file;
    if (argc > 1)
    {
        file.open(argv[1]);
        if (!file)
        {
            std::cout << "Failed to open input file\n";
            return 1;
        }
        input = &file;
    }

    size_t rows = 0;
    size_t cols = 0;
    if (!(*input >> rows >> cols) || rows == 0 || cols == 0)
    {
        std::cout << "Invalid matrix size\n";
        return 1;
    }

    size_t start_row = 0;
    size_t start_col = 0;
    size_t goal_row = 0;
    size_t goal_col = 0;
    if (!(*input >> start_row >> start_col >> goal_row >> goal_col))
    {
        std::cout << "Invalid start/goal coordinates\n";
        return 1;
    }
    if (start_row >= rows || start_col >= cols || goal_row >= rows || goal_col >= cols)
    {
        std::cout << "Start or goal out of bounds\n";
        return 1;
    }

    std::vector<std::vector<double>> costs(rows, std::vector<double>(cols, 0.0));
    for (size_t r = 0; r < rows; ++r)
    {
        for (size_t c = 0; c < cols; ++c)
        {
            if (!(*input >> costs[r][c]))
            {
                std::cout << "Failed to read matrix\n";
                return 1;
            }
            if (costs[r][c] < 0.0)
            {
                std::cout << "Negative costs are not supported\n";
                return 1;
            }
        }
    }

    GridGraph graph(rows * cols);
    for (size_t r = 0; r < rows; ++r)
    {
        for (size_t c = 0; c < cols; ++c)
        {
            graph.set_vertex_label(cell_index(r, c, cols), cell_name(r, c));
        }
    }

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
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
                size_t nr_idx = static_cast<size_t>(nr);
                size_t nc_idx = static_cast<size_t>(nc);
                auto to = cell_index(nr_idx, nc_idx, cols);
                graph.add_edge(from, to, costs[nr_idx][nc_idx]);
            }
        }
    }

    GridGraph::VertexIndex start = cell_index(start_row, start_col, cols);
    GridGraph::VertexIndex goal = cell_index(goal_row, goal_col, cols);

    AStarResult result = run_astar(graph, costs, rows, cols, start, goal);
    if (!result.found)
    {
        std::cout << "Path not found\n";
        return 1;
    }

    std::cout << "Total cost: " << result.cost << "\n";
    std::cout << "Path: ";
    for (size_t i = 0; i < result.path.size(); ++i)
    {
        if (i)
        {
            std::cout << " -> ";
        }
        std::cout << graph.get_vertex_label(result.path[i]);
    }
    std::cout << "\n";
    return 0;
}
