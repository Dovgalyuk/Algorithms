#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <stdexcept>
#include <utility>
#include "Graph.h"
#include "PriorityQueue.h"

template <typename VertexMark, typename EdgeMark>
struct DijkstraResult
{
    bool reachable;
    EdgeMark distance;
    Vector<std::string> path;
};

template <typename VertexMark, typename EdgeMark>
DijkstraResult<VertexMark, EdgeMark> dijkstra(
    const Graph<VertexMark, EdgeMark>& graph,
    const std::string& start,
    const std::string& end)
{
    DijkstraResult<VertexMark, EdgeMark> result;
    result.reachable = false;

    graph.getVertexMark(start);
    graph.getVertexMark(end);

    if (start == end)
    {
        result.reachable = true;
        result.distance = EdgeMark();
        result.path.resize(1);
        result.path.set(0, start);
        return result;
    }

    Vector<std::string> names = graph.getVertexNames();
    size_t n = names.size();

    Vector<EdgeMark> dist;
    dist.resize(n);
    for (size_t i = 0; i < n; ++i) dist.set(i, std::numeric_limits<EdgeMark>::max());

    Vector<std::string> prev;
    prev.resize(n);
    for (size_t i = 0; i < n; ++i) prev.set(i, "");

    auto find_idx = [&](const std::string& name) {
        for (size_t i = 0; i < n; ++i) {
            if (names.get(i) == name) return i;
        }
        throw std::invalid_argument("Vertex not found in Dijkstra");
    };

    size_t start_idx = find_idx(start);
    dist.set(start_idx, EdgeMark());

    PriorityQueue<std::pair<EdgeMark, size_t>> pq;
    pq.push(std::make_pair(EdgeMark(), start_idx));

    while (!pq.empty())
    {
        std::pair<EdgeMark, size_t> current = pq.top();
        pq.pop();

        EdgeMark d = current.first;
        size_t u = current.second;

        if (d > dist.get(u)) continue;

        std::string u_name = names.get(u);

        for (auto it = graph.neighborsBegin(u_name); it != graph.neighborsEnd(u_name); ++it)
        {
            std::string v_name = *it;
            size_t v = find_idx(v_name);
            EdgeMark weight = graph.getEdgeMark(u_name, v_name);
            EdgeMark new_dist = d + weight;

            if (new_dist < dist.get(v))
            {
                dist.set(v, new_dist);
                prev.set(v, u_name);
                pq.push(std::make_pair(new_dist, v));
            }
        }
    }

    size_t end_idx = find_idx(end);
    if (dist.get(end_idx) == std::numeric_limits<EdgeMark>::max()) return result;

    result.reachable = true;
    result.distance = dist.get(end_idx);

    Vector<std::string> path;
    std::string current = end;
    while (current != start)
    {
        path.resize(path.size() + 1);
        path.set(path.size() - 1, current);
        current = prev.get(find_idx(current));
    }
    path.resize(path.size() + 1);
    path.set(path.size() - 1, start);

    result.path.resize(path.size());
    for (size_t i = 0; i < path.size(); ++i)
        result.path.set(i, path.get(path.size() - 1 - i));

    return result;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open())
    {
        std::cerr << "Cannot open file: " << argv[1] << "\n";
        return 1;
    }

    typedef Graph<std::string, int> MyGraph;

    MyGraph graph;
    input >> graph;

    std::string start, end;
    input >> start >> end;

    try
    {
        DijkstraResult<std::string, int> result = dijkstra(graph, start, end);

        if (result.reachable)
        {
            for (size_t i = 0; i < result.path.size(); ++i)
            {
                if (i > 0) std::cout << " ";
                std::cout << result.path.get(i);
            }
            std::cout << std::endl;
        }
        else
        {
            std::cout << "IMPOSSIBLE" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}