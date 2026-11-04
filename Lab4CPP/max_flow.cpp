#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

#include "graph.h"
#include "../LibraryCPP/queue.h"

using namespace std;

typedef Graph<long long, string> FlowGraph;
typedef Vector<size_t> Parents;

bool find_path(const FlowGraph &graph, size_t source, size_t sink, Parents &parent)
{
    parent.resize(graph.size());
    for (size_t i = 0; i < graph.size(); ++i)
        parent[i] = graph.size();

    Queue *queue = queue_create();
    queue_insert(queue, static_cast<int>(source));
    parent[source] = source;

    while (!queue_empty(queue) && parent[sink] == graph.size())
    {
        size_t from = static_cast<size_t>(queue_get(queue));
        queue_remove(queue);

        for (auto edge = graph.neighbors(from); edge.valid(); edge.next())
        {
            size_t to = edge.vertex();
            if (parent[to] == graph.size() && edge.label() > 0)
            {
                parent[to] = from;
                queue_insert(queue, static_cast<int>(to));
            }
        }
    }

    queue_delete(queue);
    return parent[sink] != graph.size();
}

long long max_flow(const FlowGraph &graph, size_t source, size_t sink)
{
    FlowGraph residual = graph;
    for (size_t from = 0; from < graph.size(); ++from)
    {
        for (auto edge = graph.neighbors(from); edge.valid(); edge.next())
        {
            if (edge.label() < 0)
                throw invalid_argument("Отрицательная пропускная способность");
            if (!residual.has_edge(edge.vertex(), from))
                residual.add_edge(edge.vertex(), from, 0);
        }
    }

    Parents parent;
    long long flow = 0;
    while (find_path(residual, source, sink, parent))
    {
        long long added = numeric_limits<long long>::max();
        for (size_t to = sink; to != source; to = parent[to])
        {
            long long capacity = residual.get_edge(parent[to], to);
            if (capacity < added)
                added = capacity;
        }

        if (flow > numeric_limits<long long>::max() - added)
            throw overflow_error("Слишком большой поток");

        for (size_t to = sink; to != source; to = parent[to])
        {
            size_t from = parent[to];
            long long reverse = residual.get_edge(to, from);
            if (reverse > numeric_limits<long long>::max() - added)
                throw overflow_error("Слишком большая остаточная пропускная способность");
            residual.set_edge(from, to, residual.get_edge(from, to) - added);
            residual.set_edge(to, from, reverse + added);
        }
        flow += added;
    }
    return flow;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Использование: Lab4CPPMaxFlow входной_файл.txt\n";
        return 1;
    }

    ifstream input(argv[1]);
    if (!input)
    {
        cerr << "Ошибка: не удалось открыть входной файл\n";
        return 1;
    }

    try
    {
        FlowGraph graph;
        graph.read(input);
        string source, sink;
        if (!(input >> source >> sink))
            throw invalid_argument("Не указаны исток и сток");
        input >> ws;
        if (!input.eof())
            throw invalid_argument("Лишние входные данные");

        size_t from = graph.find_vertex(source);
        size_t to = graph.find_vertex(sink);
        if (from == graph.size() || to == graph.size() || from == to)
            throw invalid_argument("Неверные исток и сток");

        cout << max_flow(graph, from, to) << '\n';
    }
    catch (const exception &error)
    {
        cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
