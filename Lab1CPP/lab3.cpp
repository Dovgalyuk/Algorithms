/*

4 1 2
1 3
1 4
3 2
4 3

5 1 3
1 4
5 2
4 3
3 2

*/

#include "queue.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool find_in_vector(std::vector<int> vector, int value)
{
    for (size_t i = 0; i < vector.size(); i++)
    {
        if (vector[i] == value)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    size_t count_nodes, start_nodes, finish_nodes, start_edge, finish_edge;
    cin >> count_nodes >> start_nodes >> finish_nodes;

    int route_lenght = 0; // Длина маршрута

    std::vector<int> visited_nodes; // Посещенные вершины

    Queue* nodes_for_visit = queue_create(); // Очередь для хранения вершин для посещения
    queue_insert(nodes_for_visit, start_nodes);

    cout << "count_nodes: " << count_nodes << " start_nodes: " << start_nodes << " finish_nodes: " << finish_nodes << endl;

    /* Вектор для хранения матрицы смежности */

    std::vector<std::vector<int>> correspondence_matrix;

    for (size_t i = 0; i < count_nodes; i++)
    {     
        std::vector<int> correspondence_node;

        for (size_t j = 0; j < count_nodes; j++)
        {
            correspondence_node.push_back(0);
        }

        correspondence_matrix.push_back(correspondence_node);
    }

    /* Ввод описания ребер графа */

    int count_edge = 0;

    cout << "Enter number of edges" << endl;

    cin >> count_edge;

    cout << "Enter a description of the edges" << endl;
        
    for (size_t i = 0; i < count_edge; i++)
    {
        cin >> start_edge >> finish_edge;

        correspondence_matrix[start_edge - 1][finish_edge - 1] = 1;
        correspondence_matrix[finish_edge - 1][start_edge - 1] = 1;
    }

    /* Вывод матрицы смежности */

    for (size_t i = 0; i < count_nodes; i++)
    {
        for (size_t j = 0; j < count_nodes; j++)
        {
            cout << correspondence_matrix[i][j] << ", ";
        }

        cout << endl;
    }

    while (!queue_empty(nodes_for_visit))
    {
        int current_node = queue_get(nodes_for_visit);        
        visited_nodes.push_back(current_node);
        queue_remove(nodes_for_visit);
        for (size_t i = 0; i < correspondence_matrix[current_node - 1].size(); i++)
        {
            if (correspondence_matrix[current_node - 1][i] == 1)
            {
                if (i + 1 == finish_nodes)
                {
                    route_lenght = 1;
                    
                    break;
                }

                if (find_in_vector(visited_nodes, i + 1))
                {
                    continue;
                }
                else
                {
                    queue_insert(nodes_for_visit, i + 1);
                }
            }
        }
        if (route_lenght)
        {
            break;
        }
    }
    
    queue_delete(nodes_for_visit);

    if (route_lenght)
    {
        route_lenght = visited_nodes.size();
        cout << route_lenght << endl;
    }
    else
    {
        cout << "IMPOSSIBLE" << endl;
    }

}