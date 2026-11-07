#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "queue.h"

int get_city_id(
    std::vector<std::string>& city_names,
    std::vector<std::vector<int>>& roads,
    const std::string& name)
{
    for (size_t i = 0; i < city_names.size(); ++i)
    {
        if (city_names[i] == name)
            return static_cast<int>(i);
    }

    city_names.push_back(name);
    roads.push_back(std::vector<int>());
    return static_cast<int>(city_names.size() - 1);
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: Lab3CPP input.txt output.txt\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open input file\n";
        return 1;
    }

    std::vector<std::string> first_cities;
    std::vector<std::string> second_cities;
    std::string first;
    std::string second;

    while (input >> first)
    {
        if (!(input >> second))
        {
            std::cerr << "Invalid input\n";
            return 1;
        }

        first_cities.push_back(first);
        second_cities.push_back(second);
    }

    if (first_cities.empty())
    {
        std::cerr << "Input file is empty\n";
        return 1;
    }

    const std::string start_name = first_cities.back();
    const std::string finish_name = second_cities.back();
    first_cities.pop_back();
    second_cities.pop_back();

    std::vector<std::string> city_names;
    std::vector<std::vector<int>> roads;

    for (size_t i = 0; i < first_cities.size(); ++i)
    {
        int first_id = get_city_id(city_names, roads, first_cities[i]);
        int second_id = get_city_id(city_names, roads, second_cities[i]);

        roads[first_id].push_back(second_id);
        roads[second_id].push_back(first_id);
    }

    const int start = get_city_id(city_names, roads, start_name);
    const int finish = get_city_id(city_names, roads, finish_name);

    std::vector<bool> visited(city_names.size(), false);
    std::vector<int> previous(city_names.size(), -1);

    Queue* queue = queue_create();
    visited[start] = true;
    queue_insert(queue, start);

    while (!queue_empty(queue))
    {
        int current = queue_get(queue);
        queue_remove(queue);

        if (current == finish)
            break;

        for (size_t i = 0; i < roads[current].size(); ++i)
        {
            int next = roads[current][i];

            if (!visited[next])
            {
                visited[next] = true;
                previous[next] = current;
                queue_insert(queue, next);
            }
        }
    }

    queue_delete(queue);

    std::ofstream output(argv[2], std::ios::binary);
    if (!output)
    {
        std::cerr << "Cannot create output file\n";
        return 1;
    }

    if (!visited[finish])
    {
        output << "No path\n";
        return 0;
    }

    std::vector<int> path;
    int current = finish;

    while (current != -1)
    {
        path.push_back(current);
        current = previous[current];
    }

    for (size_t i = path.size(); i > 0; --i)
    {
        output << city_names[path[i - 1]];
        if (i > 1)
            output << ' ';
    }

    output << '\n';
    return 0;
}
