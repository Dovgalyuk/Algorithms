#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "queue.h"

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    if (!input.is_open() || !output.is_open())
        return 1;

    std::vector<std::pair<std::string, std::string>> edges;

    std::string city1;
    std::string city2;

    while (input >> city1 >> city2)
        edges.push_back({ city1, city2 });

    if (edges.empty())
        return 1;

    std::string start = edges.back().first;
    std::string finish = edges.back().second;

    edges.pop_back();

    std::map<std::string, int> cityId;
    std::vector<std::string> cityNames;

    auto getCityId = [&](const std::string& name)
        {
            auto it = cityId.find(name);

            if (it != cityId.end())
                return it->second;

            int id = static_cast<int>(cityNames.size());

            cityId[name] = id;
            cityNames.push_back(name);

            return id;
        };

    int startId = getCityId(start);
    int finishId = getCityId(finish);

    std::vector<std::vector<int>> graph;

    for (const auto& edge : edges)
    {
        int from = getCityId(edge.first);
        int to = getCityId(edge.second);

        if (graph.size() < cityNames.size())
            graph.resize(cityNames.size());

        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    graph.resize(cityNames.size());

    std::vector<int> parent(cityNames.size(), -1);
    std::vector<bool> visited(cityNames.size(), false);

    Queue* queue = queue_create();

    visited[startId] = true;
    queue_insert(queue, startId);

    while (!queue_empty(queue))
    {
        int current = queue_get(queue);
        queue_remove(queue);

        if (current == finishId)
            break;

        for (int neighbor : graph[current])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                parent[neighbor] = current;

                queue_insert(queue, neighbor);
            }
        }
    }

    if (!visited[finishId])
    {
        output << "Path not found\n";
    }
    else
    {
        std::vector<int> path;

        int current = finishId;

        while (current != -1)
        {
            path.push_back(current);
            current = parent[current];
        }

        for (int i = static_cast<int>(path.size()) - 1; i >= 0; --i)
        {
            output << cityNames[path[i]];

            if (i > 0)
                output << " ";
        }

        output << "\n";
    }

    queue_delete(queue);

    return 0;
}