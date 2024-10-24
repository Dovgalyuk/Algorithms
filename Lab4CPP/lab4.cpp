// Основной файл проекта, здесь main()

#include <iostream>
#include <queue>

typedef unsigned int uint;

#include "../LibraryCPPTemplate/vector.h"
#include "../LibraryCPPTemplate/graph.h"

int main() {
    setlocale(0, "");
    Graph<Vertex> graph;
    Vector<Vertex> vertex(3, {0, 0});
    for (size_t i = 0; i < vertex.size(); i++) {
        vertex[i] = { (int)i, 0 };
    }

    graph.add_vertex(vertex[0]);
    graph.add_vertex(vertex[1]);
    graph.add_vertex(vertex[2]);

    std::cout << "Граф из 3 вершин" << std::endl << std::endl;
    graph.print_matrix();
    std::cout << std::endl;

    std::cout << "Соединим 1 и 2, 2 и 3, 3 и 1" << std::endl << std::endl;
    graph.add_edge(vertex[0], vertex[1]);
    graph.add_edge(vertex[1], vertex[2]);
    graph.add_edge(vertex[2], vertex[0]);

    std::cout << "Граф из 3 соединенных вершин" << std::endl << std::endl;
    graph.print_matrix();
    std::cout << std::endl;

    std::cout << "Вершины 1 и 2 связаны: " << graph.is_bounded(vertex[0], vertex[1]) << std::endl;
    std::cout << "Вершины 1 и 3 связаны: " << graph.is_bounded(vertex[1], vertex[2]) << std::endl;
    std::cout << "Вершины 2 и 1 связаны: " << graph.is_bounded(vertex[1], vertex[0]) << std::endl << std::endl;
    
    std::cout << "Добавим в граф еще одну вершину" << std::endl << std::endl;
    vertex.push({3, 0});
    graph.add_vertex(vertex[3]);
    graph.print_matrix();
	return 0;
}