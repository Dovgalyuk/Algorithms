#include "queue.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    size_t count_nodes, start_nodes, finish_nodes, start_edge, finish_edge;
    std::cin >> count_nodes >> start_nodes >> finish_nodes;

    bool path_found = false;

    std::vector<std::vector<int>> path;
    path.resize(count_nodes);

    std::vector<bool> visited_nodes;
    visited_nodes.resize(count_nodes, false);
    visited_nodes[start_nodes - 1] = true;

    Queue* nodes_for_visit = queue_create();
    queue_insert(nodes_for_visit, start_nodes);

    std::cout << "count_nodes: " << count_nodes << " start_nodes: " << start_nodes << " finish_nodes: " << finish_nodes << endl;

    /* Вектор для хранения матрицы смежности */

    std::vector<std::vector<int>> correspondence_matrix;

    for (size_t i = 0; i < count_nodes; i++)
    {
        std::vector<int> correspondence_node;

        correspondence_node.resize(count_nodes, 0);

        correspondence_matrix.push_back(correspondence_node);
    }

    /* Ввод описания ребер графа */

    size_t count_edge = 0;

    std::cout << "Enter number of edges" << endl;

    std::cin >> count_edge;

    std::cout << "Enter a description of the edges" << endl;

    for (size_t i = 0; i < count_edge; i++)
    {
        std::cin >> start_edge >> finish_edge;

        correspondence_matrix[start_edge - 1][finish_edge - 1] = 1;
        correspondence_matrix[finish_edge - 1][start_edge - 1] = 1;
    }

    /* Вывод матрицы смежности */

    for (size_t i = 0; i < count_nodes; i++)
    {
        for (size_t j = 0; j < count_nodes; j++)
        {
            std::cout << correspondence_matrix[i][j] << ", ";
        }

        std::cout << endl;
    }

    while (!queue_empty(nodes_for_visit) && !path_found)
    {
        int current_node = queue_get(nodes_for_visit);
        queue_remove(nodes_for_visit);

        for (size_t i = 0; i < correspondence_matrix[current_node - 1].size(); i++)
        {
            if (correspondence_matrix[current_node - 1][i] == 1 && !visited_nodes[i])
            {
                visited_nodes[i] = true;
                path[i] = path[current_node - 1]; // Copy the path
                path[i].push_back(i + 1); // Add the current node to the path

                queue_insert(nodes_for_visit, i + 1);

                if (i + 1 == finish_nodes)
                {
                    path_found = true;
                    break;
                }
            }
        }
    }

    queue_delete(nodes_for_visit);

    if (path_found)
    {
        std::cout << "Path: " << start_nodes <<" -> ";
        for (size_t i = 0; i < path[finish_nodes - 1].size(); i++)
        {
            std::cout << path[finish_nodes - 1][i];
            if (i < path[finish_nodes - 1].size() - 1)
                std::cout << " -> ";
        }
        std::cout << endl;
    }
    else
    {
        std::cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}
