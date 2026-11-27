#include <cmath>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include "vector.h"
#include "directed_graph.h"

static void print_field(const Directed_Graph<int, int> &graph, const Vector<size_t> &path)
{
    const size_t count = graph.size_graph();
 
    size_t rows = 0;
    while (rows * rows < count)
    {
        rows++;
    }
 
    if (rows * rows != count)
    {
        return;
    }
 
    Vector<bool> on_path(count);
    for (size_t i = 0; i < count; i++)
    {
        on_path[i] = false;
    }
    for (size_t i = 0; i < path.size(); i++)
    {
        on_path[path[i]] = true;
    }
 
    size_t width = 1;
    for (size_t i = 0; i < count; i++)
    {
        width = std::max(width, std::to_string(graph.get_name_vertex(i)).size());
    }
 
    for (size_t row = 0; row < rows; row++)
    {
        std::cout << std::string((rows - 1 - row) * (width + 3), ' ');
 
        for (size_t index = row * row; index < (row + 1) * (row + 1); index++)
        {
            std::cout << (on_path[index] ? "[" : " ") << std::setw(width) << graph.get_name_vertex(index) << (on_path[index] ? "] " : "  ");
        }
        std::cout << "\n";
    }
}

static void print_steps(const Directed_Graph<int, int> &graph, const Vector<size_t> &path, long long total_cost)
{
    std::cout << "\nROUTE\n";
    for (size_t i = 0; i < path.size(); i++)
    {
        std::cout << (i > 0 ? " -> " : "") << path[i];
    }
    std::cout << "\n";
 
    if (path.size() > 1)
    {
        std::cout << "\nStep  Move        Cost  Total\n";
 
        long long sum = 0;
        for (size_t i = 0; i + 1 < path.size(); i++)
        {
            int weight = graph.get_edge(path[i], path[i + 1]);
            sum += weight;
 
            std::cout << std::left << std::setw(6) << i + 1
                      << std::setw(12) << std::to_string(path[i]) + " -> " + std::to_string(path[i + 1])
                      << std::setw(12) << weight << sum << "\n";
        }
    }
 
    std::cout << "\nCOST: " << total_cost << "   MOVES: " << path.size() - 1 << "\n";
}

static void position_cell(size_t index_vertex, size_t &row, size_t &col)
{
    row = static_cast<size_t>(std::sqrt(static_cast<double>(index_vertex)));
    while (row * row > index_vertex)
    {
        row--;
    }
    while ((row + 1) * (row + 1) <= index_vertex)
    {
        row++;
    }
    col = index_vertex - row * row;
}

static long long Heuristic(size_t first_vertex, size_t second_vertex)
{
    size_t row_first;
    size_t col_first;
    size_t row_second;
    size_t col_second;

    position_cell(first_vertex, row_first, col_first);
    position_cell(second_vertex, row_second, col_second);

    long long delta_r = std::llabs(static_cast<long long>(row_first) - static_cast<long long>(row_second));
    long long delta_x = std::llabs((static_cast<long long>(col_first) - static_cast<long long>(row_first)) - (static_cast<long long>(col_second) - static_cast<long long>(row_second)));

    return delta_r + delta_x;
}

bool AStar(const Directed_Graph<int, int> &graph, size_t start, size_t end, Vector<size_t> &path, long long &total_cost)
{
    const size_t graph_size = graph.size_graph();
    
    const long long max_longlong = std::numeric_limits<long long>::max() / 4;

    Vector<long long> vec_cost(graph_size);
    Vector<size_t> parent_vertex(graph_size);
    Vector<bool> open_vertex(graph_size);
    Vector<bool> closed_vertex(graph_size);
    Vector<size_t> coming_vertex;

    long long weight_min = -1;

    for (size_t i = 0; i < graph_size; i++)
    {
        vec_cost[i] = max_longlong;
        parent_vertex[i] = i;
        open_vertex[i] = false;
        closed_vertex[i] = false;
    }

    if (start >= graph_size || end >= graph_size)
    {
        throw std::out_of_range("vertex out of range");
    }

    for (size_t start_vertex = 0; start_vertex < graph_size; start_vertex++)
    {
        for (auto iterator = graph.begin(start_vertex); iterator != graph.end(start_vertex); iterator++)
        {

            long long current_weight = iterator.weight();

            if (current_weight < 0)
            {
                throw std::invalid_argument("negative edge weight");
            }

            if (weight_min < 0 || current_weight < weight_min)
            {
                weight_min = current_weight;
            }
        }
    }

    if (weight_min < 0)
    {
        weight_min = 0;
    }

    vec_cost[start] = 0;
    coming_vertex.push(start);
    open_vertex[start] = true;

    while (coming_vertex.size() > 0)
    {
        size_t index_best_cost = 0;

        long long best_cost = vec_cost[coming_vertex[0]] + weight_min * Heuristic(coming_vertex[0], end);

        for (size_t i = 1; i < coming_vertex.size(); i++)
        {
            long long current_cost = vec_cost[coming_vertex[i]] + weight_min * Heuristic(coming_vertex[i], end);

            if (current_cost < best_cost)
            {
                best_cost = current_cost;
                index_best_cost = i;
            }
        }

        size_t start_vertex = coming_vertex[index_best_cost];

        coming_vertex.remove(index_best_cost);

        open_vertex[start_vertex] = false;

        if (start_vertex == end)
        {
            total_cost = vec_cost[start_vertex];

            path.clear();

            for (size_t end_vertex = end;; end_vertex = parent_vertex[end_vertex])
            {
                path.insert(end_vertex);
                if (end_vertex == start)
                {
                    break;
                }
            }
            return true;
        }

        closed_vertex[start_vertex] = true;

        for (auto iterator = graph.begin(start_vertex); iterator != graph.end(start_vertex); iterator++)
        {
            size_t end_vertex = *iterator;

            if (closed_vertex[end_vertex])
            {
                continue;
            }

            long long best_cost_vertex = vec_cost[start_vertex] + iterator.weight();

            if (best_cost_vertex < vec_cost[end_vertex])
            {
                vec_cost[end_vertex] = best_cost_vertex;
                parent_vertex[end_vertex] = start_vertex;

                if (!open_vertex[end_vertex])
                {
                    coming_vertex.push(end_vertex);
                    open_vertex[end_vertex] = true;
                }
            }
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    size_t start = 0;
    size_t end = 0;

    Directed_Graph<int, int> graph;

    Vector<size_t> path;

    long long total_cost = 0;

    std::ifstream input_file(argv[1]);

    if (input_file.is_open())
    {
        try
        {
            if (!(input_file >> start >> end))
            {
                throw std::invalid_argument("bad start or end");
            }

            if (!(input_file >> graph))
            {
                throw std::invalid_argument("bad graph input");
            }

            if (start >= graph.size_graph() || end >= graph.size_graph())
            {
                throw std::out_of_range("start or end out of range");
            }

            for (size_t start_vertex = 0; start_vertex < graph.size_graph(); start_vertex++)
            {
                for (auto iterator = graph.begin(start_vertex); iterator != graph.end(start_vertex); iterator++)
                {
                    size_t end_vertex = *iterator;

                    graph.set_edge_weight(start_vertex, end_vertex, graph.get_name_vertex(end_vertex));
                }
            }

            if (!AStar(graph, start, end, path, total_cost))
            {
                std::cout << "no path";
                return 0;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what();
            return 1;
        }
    }
    else
    {
        return 1;
    }

    print_field(graph, path);
    print_steps(graph, path, total_cost);
    
    input_file.close();

    return 0;
}