#include <iostream>
#include "graph.h"

int main() {

    Graph<std::string, int> graph(5);

    //Adding vertex marks
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");
    graph.add_vertex("D");
    graph.add_vertex("E");

    if (graph.get_vertex_count() != 5) {
        std::cout << "Invalid vertex amount\n" << std::endl;
        return 1;
    }
    else {
        std::cout << "Correct number of vertices\n" << std::endl;
    }

    //Setting marks for vertices
    graph.set_vertex_mark(0, "A");
    graph.set_vertex_mark(1, "B");
    graph.set_vertex_mark(2, "C");
    graph.set_vertex_mark(3, "D");
    graph.set_vertex_mark(4, "E");

    //Vertex marking check
    for (size_t i = 0; i < graph.get_vertex_count(); ++i) {
        std::cout << "Vertex " << i << " mark" << ": " << graph.get_vertex_mark(i) << std::endl;
    }
    std::cout << "\n";

    //Testing edges addition
    graph.add_edge(0, 1, 4);
    graph.add_edge(0, 2, 1);
    graph.add_edge(1, 2, 2);
    graph.add_edge(1, 3, 5);
    graph.add_edge(2, 3, 3);
    graph.add_edge(3, 4, 1);

    //Edge check
    std::cout << "Has edge A -> B: " << (graph.has_edge(0, 1) ? "Yes" : "No") << std::endl;//yes
    std::cout << "Has edge B -> C: " << (graph.has_edge(1, 2) ? "Yes" : "No") << std::endl;//yes
    std::cout << "Has edge E -> A: " << (graph.has_edge(4, 0) ? "Yes" : "No") << std::endl;//no
    std::cout << "\n";

    // Получение и проверка пометок рёбер

    std::cout << "Edge weight from A to B: " << graph.get_edge_mark(0) << std::endl;
    std::cout << "Edge weight from B to C: " << graph.get_edge_mark(2) << std::endl;
    std::cout << "\n";

    //Edge remove
    graph.remove_edge(graph.get_vertex(0), graph.get_vertex(1));
    std::cout << "Edge A -> B exists after deletion: " << (graph.has_edge(0, 1) ? "Yes\n" : "No\n") << std::endl;

    //Get and print all vertex marks
    std::vector<std::string> all_marks = graph.get_all_vertex_marks();
    std::cout << "All vertex marks: ";
    for (const auto& mark : all_marks) {
        std::cout << mark << " ";
    }
    std::cout << std::endl;
    std::cout << "\n";

    //Vertex remove
    graph.remove_vertex(2);
    std::cout << "Vertex count after deletion: " << graph.get_vertex_count() << std::endl;
    std::cout << "\n";

    //Checking the remaining vertex marks
    for (size_t i = 0; i < graph.get_vertex_count(); ++i) {
        std::cout << "Vertex " << i << ": " << graph.get_vertex_mark(i) << std::endl;
    }

    return 0;
}