#include <iostream>
#include <fstream>
#include <string>

#include "array.h"
#include "list.h"
#include "vector.h"
#include "queue.h"
#include "stack.h"

typedef Vector<std::string> StringVector;
typedef Array<int> IntArray;
typedef List<int> CityList;
typedef Queue<int> CityQueue;
typedef Stack<int> CityStack;

struct Road
{
    int first;
    int second;
};

typedef Vector<Road> RoadVector;

int city_index(StringVector& cities, const std::string& name)
{
    for (size_t i = 0; i < cities.size(); ++i)
    {
        if (cities.get(i) == name)
        {
            return (int)i;
        }
    }

    size_t index = cities.size();
    cities.resize(index + 1);
    cities.set(index, name);
    return (int)index;
}

bool read_roads(std::ifstream& input, StringVector& cities, RoadVector& roads, Road& request)
{
    std::string first;
    std::string second;

    if (!(input >> first >> second))
    {
        return false;
    }

    request.first = city_index(cities, first);
    request.second = city_index(cities, second);

    while (input >> first)
    {
        if (!(input >> second))
        {
            return false;
        }

        roads.resize(roads.size() + 1);
        roads.set(roads.size() - 1, request);

        request.first = city_index(cities, first);
        request.second = city_index(cities, second);
    }

    return input.eof() && !input.bad();
}

int search_layer(CityList* neighbors, CityQueue& queue, size_t& layer_size, IntArray& parents, const IntArray& other_parents)
{
    size_t next_layer_size = 0;

    for (size_t i = 0; i < layer_size; ++i)
    {
        int city = queue.get();
        queue.remove();

        for (auto item = neighbors[city].first(); item != nullptr; item = item->next())
        {
            int neighbor = item->data();

            if (parents.get(neighbor) != -1)
            {
                continue;
            }

            parents.set(neighbor, city);

            if (other_parents.get(neighbor) != -1)
            {
                return neighbor;
            }

            queue.insert(neighbor);
            ++next_layer_size;
        }
    }

    layer_size = next_layer_size;
    return -1;
}

int find_meeting(CityList* neighbors, int start, int end, IntArray& from_start, IntArray& from_end)
{
    for (size_t i = 0; i < from_start.size(); ++i)
    {
        from_start.set(i, -1);
        from_end.set(i, -1);
    }

    from_start.set(start, start);
    from_end.set(end, end);

    if (start == end)
    {
        return start;
    }

    CityQueue start_queue;
    CityQueue end_queue;
    start_queue.insert(start);
    end_queue.insert(end);

    size_t start_layer = 1;
    size_t end_layer = 1;

    while (!start_queue.empty() && !end_queue.empty())
    {
        int meeting = search_layer(neighbors, start_queue, start_layer, from_start, from_end);
        if (meeting != -1)
        {
            return meeting;
        }

        meeting = search_layer(neighbors, end_queue, end_layer, from_end, from_start);
        if (meeting != -1)
        {
            return meeting;
        }
    }

    return -1;
}

void write_path(std::ostream& output, const StringVector& cities, int meeting, const IntArray& from_start, const IntArray& from_end)
{
    CityStack path;
    int city = meeting;

    while (city != from_start.get(city))
    {
        path.push(city);
        city = from_start.get(city);
    }

    output << cities.get(city);
    while (!path.empty())
    {
        output << ' ' << cities.get(path.get());
        path.pop();
    }

    city = meeting;
    while (city != from_end.get(city))
    {
        city = from_end.get(city);
        output << ' ' << cities.get(city);
    }

    output << '\n';
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: ShortestPath <input-file> <output-file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    StringVector cities;
    RoadVector roads;
    Road request;

    if (!read_roads(input, cities, roads, request))
    {
        std::cerr << "Cannot read roads or route request\n";
        return 1;
    }

    IntArray from_start(cities.size());
    IntArray from_end(cities.size());

    CityList* neighbors = new CityList[cities.size()];
    for (size_t i = 0; i < roads.size(); ++i)
    {
        Road road = roads.get(i);
        neighbors[road.first].insert_after(neighbors[road.first].last(), road.second);
        neighbors[road.second].insert_after(neighbors[road.second].last(), road.first);
    }

    int meeting = find_meeting(neighbors, request.first, request.second, from_start, from_end);
    delete[] neighbors;

    std::ofstream output(argv[2]);
    if (!output)
    {
        std::cerr << "Cannot open output file\n";
        return 1;
    }

    if (meeting != -1)
    {
        write_path(output, cities, meeting, from_start, from_end);
    }

    output.close();
    if (!output)
    {
        std::cerr << "Cannot write output file\n";
        return 1;
    }

    if (meeting != -1)
    {
        write_path(std::cout, cities, meeting, from_start, from_end);
    }
    else
    {
        std::cout << "No path\n";
    }

    return 0;
}
