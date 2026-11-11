#include <fstream>
#include <limits>
#include <vector>

#include "queue.h"

typedef std::vector<std::vector<int>> Graph;
typedef std::vector<int> Distances;
typedef std::vector<int> Parents;
typedef std::vector<int> Path;

bool expand_layer(
    Queue *queue,
    const Graph& graph,
    Distances& distance_current,
    const Distances& distance_other,
    Parents& parent_current,
    int& meeting_vertex)
{
    if (queue_empty(queue))
    {
        return false;
    }

    const int layer_distance =
        distance_current[queue_get(queue)];

    int best_distance = std::numeric_limits<int>::max();
    int best_vertex = -1;

    while (!queue_empty(queue)
        && distance_current[queue_get(queue)] == layer_distance)
    {
        int vertex = queue_get(queue);
        queue_remove(queue);

        for (int neighbor : graph[vertex])
        {
            if (distance_current[neighbor] == -1)
            {
                distance_current[neighbor] =
                    distance_current[vertex] + 1;

                parent_current[neighbor] = vertex;

                if (distance_other[neighbor] != -1)
                {
                    int total_distance =
                        distance_current[neighbor]
                        + distance_other[neighbor];

                    if (total_distance < best_distance)
                    {
                        best_distance = total_distance;
                        best_vertex = neighbor;
                    }
                }

                queue_insert(queue, neighbor);
            }
        }
    }

    if (best_vertex != -1)
    {
        meeting_vertex = best_vertex;
        return true;
    }

    return false;
}

Path find_shortest_path(
    const Graph& graph,
    int start,
    int finish)
{
    int vertex_count = static_cast<int>(graph.size());

    Distances distance_start(vertex_count, -1);
    Distances distance_finish(vertex_count, -1);

    Parents parent_start(vertex_count, -1);
    Parents parent_finish(vertex_count, -1);

    Queue *queue_start = queue_create();
    Queue *queue_finish = queue_create();

    distance_start[start] = 0;
    distance_finish[finish] = 0;

    queue_insert(queue_start, start);
    queue_insert(queue_finish, finish);

    int meeting_vertex = -1;

    while (!queue_empty(queue_start) && !queue_empty(queue_finish))
    {
        if (expand_layer(
                queue_start,
                graph,
                distance_start,
                distance_finish,
                parent_start,
                meeting_vertex))
        {
            break;
        }

        if (expand_layer(
                queue_finish,
                graph,
                distance_finish,
                distance_start,
                parent_finish,
                meeting_vertex))
        {
            break;
        }
    }

    Path path;

    if (meeting_vertex != -1)
    {
        int vertex = meeting_vertex;

        while (vertex != -1)
        {
            path.push_back(vertex);
            vertex = parent_start[vertex];
        }

        for (size_t i = 0; i < path.size() / 2; ++i)
        {
            int temp = path[i];
            path[i] = path[path.size() - 1 - i];
            path[path.size() - 1 - i] = temp;
        }

        vertex = parent_finish[meeting_vertex];

        while (vertex != -1)
        {
            path.push_back(vertex);
            vertex = parent_finish[vertex];
        }
    }

    queue_delete(queue_start);
    queue_delete(queue_finish);

    return path;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        return 1;
    }

    std::ifstream input(argv[1]);

    if (!input)
    {
        return 1;
    }

    std::ofstream output(argv[2]);

    if (!output)
    {
        return 1;
    }

    int vertex_count;
    int start;
    int finish;

    if (!(input >> vertex_count >> start >> finish))
    {
        return 1;
    }

    if (vertex_count <= 0
        || start < 1 || start > vertex_count
        || finish < 1 || finish > vertex_count)
    {
        output << "IMPOSSIBLE\n";
        return 0;
    }

    Graph graph(vertex_count);

    int u;
    int v;

    while (input >> u >> v)
    {
        if (u < 1 || u > vertex_count
            || v < 1 || v > vertex_count)
        {
            output << "IMPOSSIBLE\n";
            return 0;
        }

        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }

    if (start == finish)
    {
        output << start << '\n';
        return 0;
    }

    Path path = find_shortest_path(graph, start - 1, finish - 1);

    if (path.empty())
    {
        output << "IMPOSSIBLE\n";
        return 0;
    }

    for (size_t i = 0; i < path.size(); ++i)
    {
        if (i > 0)
        {
            output << ' ';
        }

        output << path[i] + 1;
    }

    output << '\n';

    return 0;
}