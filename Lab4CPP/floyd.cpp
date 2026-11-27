#include "graph.h"

#include <fstream>
#include <iostream>
#include <limits>

void printShortestPaths(const Graph<int, int>& graph)
{
    const auto count = graph.vertexCount();
    constexpr auto infinity = std::numeric_limits<long long>::max();
    constexpr auto minimum = std::numeric_limits<long long>::min();

    Vector<Vector<long long>> dist;
    Vector<Vector<size_t>> next;
    dist.resize(count);
    next.resize(count);

    for (size_t i = 0; i < count; ++i)
    {
        dist[i].resize(count);
        next[i].resize(count);
        for (size_t j = 0; j < count; ++j)
        {
            dist[i][j] = i == j ? 0 : infinity;
            if (graph.hasEdge(graph.vertexName(i), graph.vertexName(j)))
            {
                int weight = graph.edgeLabel(graph.vertexName(i), graph.vertexName(j));
                if (weight < dist[i][j])
                {
                    dist[i][j] = weight;
                    next[i][j] = j;
                }
            }
        }
    }

    //алгоритм флойда
    for (size_t k = 0; k < count; ++k)
        for (size_t i = 0; i < count; ++i)
            for (size_t j = 0; j < count; ++j)
            {
                const auto left = dist[i][k];
                const auto right = dist[k][j];
                if (left == infinity || right == infinity)
                    continue;
                if (right > 0 && left >= infinity - right)
                    continue;

                const auto candidate = right < 0 && left < minimum - right
                    ? minimum : left + right;
                if (candidate < dist[i][j])
                {
                    dist[i][j] = candidate;
                    next[i][j] = next[i][k];
                }
            }

    for (size_t i = 0; i < count; ++i)
        for (size_t j = 0; j < count; ++j)
        {
            std::cout << graph.vertexName(i) << " -> " << graph.vertexName(j) << ": ";
            if (dist[i][j] == infinity)
            {
                std::cout << "нет пути\n";
                continue;
            }

            bool negativeCycle = false;
            for (size_t k = 0; k < count; ++k)
                if (dist[k][k] < 0 && dist[i][k] != infinity && dist[k][j] != infinity)
                {
                    negativeCycle = true;
                    break;
                }
            if (negativeCycle)
            {
                std::cout << "отрицательный цикл\n";
                continue;
            }

            std::cout << dist[i][j] << ", " << graph.vertexName(i);
            for (auto current = i; current != j;)
            {
                current = next[current][j];
                std::cout << " -> " << graph.vertexName(current);
            }
            std::cout << '\n';
        }
}

int main(int argc, char* argv[])
{
    if (argc > 2)
    {
        std::cerr << "Использование:Floyd [input.txt]\n";
        return 1;
    }

    std::ifstream file;
    if (argc == 2)
    {
        file.open(argv[1]);
        if (!file)
        {
            std::cerr << "Неполучается открыть: " << argv[1] << '\n';
            return 1;
        }
    }

    std::istream& input = argc == 2 ? file : std::cin;
    try
    {
        Graph<int, int> graph;
        if (!(input >> graph))
        {
            std::cerr << "Некорректное описание графа\n";
            return 1;
        }
        printShortestPaths(graph);
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
