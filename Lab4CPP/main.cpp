#include "graph.h"

#include <algorithm>
#include <clocale>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <optional>
#include <queue>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
#include <locale>
using namespace std;

using Cost = uint64_t;
using CostGraph = Graph<Cost, Cost>;
using QueueItem = tuple<Cost, Cost, GridVertex>;  // Оценка, стоимость, клетка.

constexpr Cost maxCost = numeric_limits<Cost>::max();

struct Path
{
    Cost cost;
    vector<GridVertex> vertices;
};

Cost saturatedAdd(Cost a, Cost b)
{
    return a > maxCost - b ? maxCost : a + b;
}

Path findPath(const CostGraph &graph, GridVertex start, GridVertex goal, Cost minCost)
{
    struct State
    {
        optional<Cost> cost;
        GridVertex parent{};
    };

    vector<State> states(graph.rows() * graph.columns());
    const auto state = [&](GridVertex vertex) -> State &
    {
        return states[vertex.first * graph.columns() + vertex.second];
    };

    // Оценка оставшейся стоимости по манхэттенскому расстоянию.
    const auto heuristic = [&](GridVertex vertex) -> Cost
    {
        const auto dy = max(vertex.first, goal.first) - min(vertex.first, goal.first);
        const auto dx = max(vertex.second, goal.second) - min(vertex.second, goal.second);
        const Cost steps = dy + dx;

        return steps != 0 && minCost > maxCost / steps ? maxCost : steps * minCost;
    };

    priority_queue<QueueItem, vector<QueueItem>, greater<QueueItem>> pending;
    state(start).cost = 0;
    pending.push({heuristic(start), 0, start});

    while (!pending.empty())
    {
        const auto [estimate, cost, vertex] = pending.top();
        pending.pop();

        if (state(vertex).cost != cost)
            continue;

        if (vertex == goal)
        {
            // Восстанавливаем маршрут от цели к старту.
            Path result{cost, {goal}};
            auto step = goal;

            while (step != start)
            {
                step = state(step).parent;
                result.vertices.push_back(step);
            }

            reverse(result.vertices.begin(), result.vertices.end());
            return result;
        }

        for (const auto &neighbor : graph.neighbors(vertex))
        {
            const Cost weight = graph.edgeLabel(vertex, neighbor);
            if (cost > maxCost - weight)
                continue;

            const Cost candidate = cost + weight;
            auto &next = state(neighbor);

            if (next.cost && candidate >= *next.cost)
                continue;

            next = {candidate, vertex};
            pending.push({saturatedAdd(candidate, heuristic(neighbor)), candidate, neighbor});
        }
    }

    throw overflow_error("Стоимость маршрута превышает допустимый предел");
}

GridVertex readVertex(istream &input, long long rows, long long columns)
{
    long long row = 0, column = 0;

    if (!(input >> row >> column) ||
        row < 0 || row >= rows || column < 0 || column >= columns)
    {
        throw invalid_argument("Некорректные координаты начала или цели");
    }

    return {static_cast<size_t>(row), static_cast<size_t>(column)};
}

Path solve(istream &input)
{
    long long rows = 0, columns = 0;

    if (!(input >> rows >> columns) || rows <= 0 || columns <= 0 ||
        static_cast<uintmax_t>(rows) > numeric_limits<size_t>::max() ||
        static_cast<uintmax_t>(columns) > numeric_limits<size_t>::max())
    {
        throw invalid_argument("Некорректные размеры матрицы");
    }

    CostGraph graph(static_cast<size_t>(rows), static_cast<size_t>(columns));
    Cost minCost = maxCost;

    for (size_t row = 0; row < graph.rows(); ++row)
    {
        for (size_t column = 0; column < graph.columns(); ++column)
        {
            long long value = 0;
            if (!(input >> value) || value < 0)
                throw invalid_argument("Стоимость клетки должна быть неотрицательным целым числом");

            const auto cost = static_cast<Cost>(value);
            graph.setVertexLabel({row, column}, cost);
            minCost = min(minCost, cost);
        }
    }

    const auto start = readVertex(input, rows, columns);
    const auto goal = readVertex(input, rows, columns);

    string extra;
    if (input >> extra)
        throw invalid_argument("Лишние данные после координат цели");

    for (size_t row = 0; row < graph.rows(); ++row)
    {
        for (size_t column = 0; column < graph.columns(); ++column)
        {
            const GridVertex from{row, column};

            // Цена перехода равна стоимости клетки назначения.
            const auto addMove = [&](GridVertex to)
            {
                graph.addEdge(from, to, graph.vertexLabel(to));
            };

            if (row > 0)
                addMove({row - 1, column});
            if (row + 1 < graph.rows())
                addMove({row + 1, column});
            if (column > 0)
                addMove({row, column - 1});
            if (column + 1 < graph.columns())
                addMove({row, column + 1});
        }
    }

    return findPath(graph, start, goal, minCost);
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    try
    {
        if (argc > 2)
            throw invalid_argument("Укажите путь только к одному входному файлу");

        ifstream file;
        if (argc == 2)
        {
            file.open(argv[1]);
            if (!file)
                throw runtime_error("Не удалось открыть входной файл");
        }

        const auto path = solve(argc == 2 ? file : cin);

        cout << path.cost << '\n';

        for (const auto &vertex : path.vertices)
            cout << vertex.first << ' ' << vertex.second << '\n';
    }
    catch (const exception &error)
    {
        cerr << error.what() << '\n';
        return 1;
    }
}