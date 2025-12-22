#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>

#include "graph.h"

using WeightedGraph = Graph<std::string, double>;
using Vertex = WeightedGraph::Vertex;
using DistanceVector = Vector<double>;

struct QueueEntry
{
    Vertex vertex;
    double distance;

    bool operator>(const QueueEntry& other) const
    {
        return distance > other.distance;
    }
};

using PriorityQueue = std::priority_queue<QueueEntry, std::vector<QueueEntry>, std::greater<QueueEntry>>;

struct GraphInput
{
    WeightedGraph graph;
    std::unordered_map<std::string, Vertex> nameToIndex;
    std::string source;
    std::string target;
};

static GraphInput readGraph(std::istream& input)
{
    std::size_t vertexCount = 0;
    std::size_t edgeCount = 0;
    if (!(input >> vertexCount >> edgeCount))
    {
        throw std::runtime_error("Error read graph sizes");
    }

    GraphInput graphInput{ WeightedGraph(vertexCount), {}, {}, {} };

    for (std::size_t i = 0; i < vertexCount; ++i)
    {
        std::string name;
        input >> name;
        graphInput.graph.setVertexLabel(i, name);
        graphInput.nameToIndex[name] = i;
    }

    for (std::size_t i = 0; i < edgeCount; ++i)
    {
        std::string from;
        std::string to;
        double weight = 0.0;
        input >> from >> to >> weight;
        graphInput.graph.addEdge(graphInput.nameToIndex.at(from), graphInput.nameToIndex.at(to), weight);
    }

    input >> graphInput.source >> graphInput.target;

    return graphInput;
}

static DistanceVector dijkstra(const WeightedGraph& graph, Vertex source)
{
    constexpr auto inf = std::numeric_limits<double>::infinity();
    const Vertex n = graph.verticesCount();

    DistanceVector dist(n);
    for (Vertex i = 0; i < n; ++i) dist.set(i, inf);
    dist.set(source, 0.0);

    PriorityQueue pq;
    pq.push(QueueEntry{ source, 0.0 });

    while (!pq.empty())
    {
        QueueEntry entry = pq.top();
        pq.pop();

        const Vertex v = entry.vertex;
        const double d = entry.distance;

        if (d > dist.get(v)) continue;

        for (auto it = graph.neighbours(v); it.valid(); it.next())
        {
            const Vertex to = it.vertex();
            const double w = it.edgeLabel();
            const double cand = d + w;

            if (cand < dist.get(to))
            {
                dist.set(to, cand);
                pq.push(QueueEntry{ to, cand });
            }
        }
    }

    return dist;
}

static void printResult(const DistanceVector& distances, Vertex target)
{
    const double distance = distances[target];

    if (distance == std::numeric_limits<double>::infinity())
    {
        std::cout << "No path\n";
        return;
    }

    std::cout << distance << "\n";
}

int main(int argc, char* argv[])
{
    try
    {
        std::ifstream file;
        std::istream* source = &std::cin;

        if (argc > 1)
        {
            file.open(argv[1]);
            if (!file.is_open())
            {
                throw std::runtime_error("Not open input file");
            }
            source = &file;
        }

        GraphInput input = readGraph(*source);
        auto distances = dijkstra(input.graph, input.nameToIndex.at(input.source));
        printResult(distances, input.nameToIndex.at(input.target));
    }
    catch (const std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}