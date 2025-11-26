#include <iostream>
#include <string>
#include "graph.h"

typedef Graph<std::string, int> MyGraph;

int main()
{
    MyGraph graph;

    // 1. Тест добавления вершин
    for (int i = 0; i < 5; ++i)
    {
        std::string label = std::string(1, (char)('A' + i)); 
        size_t idx = graph.add_vertex(label);
        if (idx != (size_t)i)
        {
            std::cout << "Invalid vertex index returned: " << idx << ", expected: " << i << "\n";
            return 1;
        }
    }

    if (graph.vertex_count() != 5)
    {
        std::cout << "Invalid vertex count: " << graph.vertex_count() << "\n";
        return 1;
    }

    // Проверка меток вершин
    for (int i = 0; i < 5; ++i)
    {
        std::string expected = std::string(1, (char)('A' + i));
        if (graph.get_vertex_label(i) != expected)
        {
            std::cout << "Invalid vertex label at " << i << "\n";
            return 1;
        }
    }

    // 2. Тест добавления ребер
    graph.add_edge(0, 1, 10);
    graph.add_edge(0, 2, 20);
    graph.add_edge(1, 3, 30);

    if (!graph.has_edge(0, 1) || !graph.has_edge(0, 2) || !graph.has_edge(1, 3))
    {
        std::cout << "Edges not found\n";
        return 1;
    }

    if (graph.get_edge_label(0, 1) != 10 || graph.get_edge_label(0, 2) != 20)
    {
        std::cout << "Invalid edge labels\n";
        return 1;
    }

    // 3. Тест итератора
    {
        auto it = graph.get_neighbor_iterator(0);
        int count = 0;
        bool found_1 = false;
        bool found_2 = false;

        while (it.has_next())
        {
            size_t neighbor_idx = it.next();
            count++;

            if (neighbor_idx == 1) found_1 = true;
            else if (neighbor_idx == 2) found_2 = true;
            else 
            {
                std::cout << "Unexpected neighbor for A: " << neighbor_idx << "\n";
                return 1;
            }
        }

        if (count != 2 || !found_1 || !found_2)
        {
            std::cout << "Iterator failed to find all neighbors for A\n";
            return 1;
        }
    }

    // 4. Тест удаления ребра
    graph.remove_edge(0, 2);
    if (graph.has_edge(0, 2))
    {
        std::cout << "Edge A->C should be removed\n";
        return 1;
    }

    // 5. Тест удаления вершины
    graph.remove_vertex(1); 

    if (graph.vertex_count() != 4)
    {
        std::cout << "Invalid vertex count after removal\n";
        return 1;
    }

    if (graph.get_vertex_label(1) != "C" || graph.get_vertex_label(2) != "D")
    {
        std::cout << "Vertex labels shift failed\n";
        return 1;
    }

    if (graph.has_edge(0, 1)) 
    {
        std::cout << "Edge 0->1 shouldn't exist\n";
        return 1;
    }

    std::cout << "All tests passed!\n";
    return 0;
}
