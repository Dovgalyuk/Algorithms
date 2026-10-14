#include <iostream>
#include <sstream>
#include "directed_graph.h"

typedef Directed_Graph<int, int> Graph;

int main()
{
    Graph graph(4);
    if (graph.size_graph() != 4 || graph.size_vec_vertex() != 4 || graph.empty_graph())
    {
        std::cout << "Invalid constructor";
        return 1;
    }

    for(size_t i=0; i<4;i++) graph.set_vertex_name(i, static_cast<int>(i + 1));

    for (size_t i = 0; i < graph.size_graph(); i++)
        if (graph.get_index_by_name(graph.get_name_vertex(i)) != i)
        {
            std::cout << "Invalid vertex name or index " << i;
            return 1;
        }

    graph.add_edge(0, 1, 10);
    graph.add_edge(0, 2, 20);
    graph.add_edge(1, 3, 30);
    graph.add_edge(2, 3, 40);

    if (!graph.edge(0, 1) || !graph.edge(0, 2) || !graph.edge(1, 3) || !graph.edge(2, 3))
    {
        std::cout << "Invalid edge creation";
        return 1;
    }
    if (graph(0, 1) != 10 || graph.get_edge(0, 2) != 20 || graph.get_edge(1, 3) != 30 || graph.get_edge(2, 3) != 40)
    {
        std::cout << "Invalid edge weight";
        return 1;
    }

    graph.set_edge_weight(0, 1, 100);

    if (graph(0, 1) != 100)
    {
        std::cout << "Invalid edge weight update";
        return 1;
    }

    graph.remove_edge(0, 2);
    if (graph.edge(0, 2))
    {
        std::cout << "Invalid edge removal";
        return 1;
    }

    graph = graph;

    if (graph.size_graph() != 4 || !graph.edge(0, 1) || graph(0, 1) != 100 || graph.edge(0, 2))
    {
        std::cout << "Invalid self-assignment";
        return 1;
    }

    Graph copy(graph);
    if (copy.size_graph() != graph.size_graph())
    {
        std::cout << "Invalid copy constructor";
        return 1;
    }
    for (size_t i = 0; i < graph.size_graph(); i++)
    {
        if (copy.get_name_vertex(i) != graph.get_name_vertex(i))
        {
            std::cout << "Invalid copy vertex " << i;
            return 1;
        }

        for (size_t j = 0; j < graph.size_graph(); j++)
        {
            if (copy.edge(i, j) != graph.edge(i, j))
            {
                std::cout << "Invalid copy edge " << i << j;
                return 1;
            }
            if (graph.edge(i, j) && copy.get_edge(i, j) != graph.get_edge(i, j))
            {
                std::cout << "Invalid copy edge weight";
                return 1;
            }
        }
    }

    copy.set_edge_weight(0, 1, 999);
    if (graph.get_edge(0, 1) != 100)
    {
        std::cout << "Invalid copy";
        return 1;
    }

    graph.push_vertex(5);
    if (graph.size_graph() != 5 || graph.get_name_vertex(4) != 5)
    {
        std::cout << "Invalid push_vertex";
        return 1;
    }

    graph.add_edge(4, 0, 50);
    if (!graph.edge(4, 0) || graph.get_edge(4, 0) != 50)
    {
        std::cout << "Invalid add_edge";
        return 1;
    }

    graph.insert_vertex(-1);
    if (graph.size_graph() != 6 || graph.get_name_vertex(0) != -1 || graph.get_name_vertex(2) != 2)
    {
        std::cout << "Invalid insert_vertex";
        return 1;
    }

    graph.remove_vertex_by_name(5);
    if (graph.size_graph() != 5)
    {
        std::cout << "Invalid reomve_vertex_by_name";
        return 1;
    }

    graph.pop_vertex();
    if (graph.size_graph() != 4)
    {
        std::cout << "Invalid pop_vertex";
        return 1;
    }

    graph.removeFirst_vertex();
    if (graph.size_graph() != 3 || graph.get_name_vertex(0) != 1)
    {
        std::cout << "Invalid removeFirst_vertex";
        return 1;
    }

    Graph neighbors_graph(4);

    neighbors_graph.add_edge(0, 1, 10);
    neighbors_graph.add_edge(0, 3, 30);
    neighbors_graph.add_edge(1, 2, 20);

    size_t expected_neighbors[] = {1, 3};
    size_t count = 0;
    for (auto iterator = neighbors_graph.begin(0); iterator != neighbors_graph.end(0); iterator++)
    {
        size_t vertex = *iterator;

        if (count >= 2 || vertex != expected_neighbors[count++])
        {
            std::cout << "Invalid iteration";
            return 1;
        }
    }
    if (count != 2)
    {
        std::cout << "Invalid number of neighbors";
        return 1;
    }

    Graph rectangle = Graph(2, 3, 1);
    if (rectangle.size_graph() != 6 || !rectangle.edge(0, 1) || !rectangle.edge(1, 0) || !rectangle.edge(0, 3) || !rectangle.edge(3, 0) || rectangle.edge(0, 2))
    {
        std::cout << "Invalid rectangle graph";
        return 1;
    }

    Graph triangle = Graph::make_triangle_by_rows(3, 5);
    if (triangle.size_graph() != 9 || !triangle.edge(0, 2) || !triangle.edge(1, 2) || !triangle.edge(2, 0) || !triangle.edge(2, 3) || triangle.edge(2, 4))
    {
        std::cout << "Invalid triangle graph";
        return 1;
    }

    try
    {
        Graph invalid = Graph::make_triangle_by_vertices(8);
        std::cout << "Invalid triangle size";
        return 1;
    }
    catch (const std::invalid_argument &){}

    try
    {
        graph.get_name_vertex(100);
        std::cout << "Invalid vertex index";
        return 1;
    }
    catch (const std::out_of_range &){}

    std::istringstream input("3 1 2 3 2 0 1 10 1 2 20");
    Graph input_graph;
    input >> input_graph;
    if (input.fail() || input_graph.size_graph() != 3 || input_graph.get_name_vertex(0) != 1 || input_graph.get_name_vertex(1) != 2 || input_graph.get_name_vertex(2) != 3   || !input_graph.edge(0, 1) || !input_graph.edge(1, 2) || input_graph.get_edge(0, 1) != 10 || input_graph.get_edge(1, 2) != 20)
    {
        std::cout << "Invalid graph input";
        return 1;
    }

    std::istringstream triangle_input("4 10 20 30 40");
    Graph triangle_input_graph;
    triangle_input >> triangle_input_graph;
    if (triangle_input.fail() || triangle_input_graph.size_graph() != 4 || triangle_input_graph.get_name_vertex(0) != 10 || triangle_input_graph.get_name_vertex(1) != 20 || triangle_input_graph.get_name_vertex(2) != 30 || triangle_input_graph.get_name_vertex(3) != 40 || !triangle_input_graph.edge(0, 2) || !triangle_input_graph.edge(1, 2) || !triangle_input_graph.edge(2, 1) || !triangle_input_graph.edge(2, 3) || !triangle_input_graph.edge(2, 0))
    {
        std::cout << "Invalid triangle graph input";
        return 1;
    }

    std::istringstream bad_triangle_input("8 1 2 3 4 5 6 7 8");
    Graph bad_triangle_graph;
    bad_triangle_input >> bad_triangle_graph;
    if (!bad_triangle_input.fail())
    {
        std::cout << "Non-square triangle input";
        return 1;
    }

    std::cout << "Graph: ";
    for (size_t i = 0; i < input_graph.size_graph(); ++i) std::cout << input_graph.get_name_vertex(i) << " ";

    const size_t n = 1000;
    Graph performance_graph(n);

    for (size_t i = 0; i + 1 < n; i++) performance_graph.add_edge(i, i + 1, static_cast<int>(i + 1));

    Graph performance_copy = performance_graph;

    for (size_t i = 0; i + 1 < n; i++)
        if (performance_copy.get_edge(i, i + 1) != static_cast<int>(i + 1))
        {
            std::cout << "Invalid performance copy" << i;
            return 1;
        }

    long long sum = 0;

    for (size_t i = 0; i + 1 < n; i++) sum += performance_graph.get_edge(i, i + 1);
    std::cout << sum;;
}