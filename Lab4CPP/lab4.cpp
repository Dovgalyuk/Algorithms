// Основной файл проекта, здесь main()

#include <iostream>
#include <queue>
#include <string>

#include "../LibraryCPPTemplate/Vertex.h"
#include "../LibraryCPPTemplate/vector.h"
#include "../LibraryCPPTemplate/graph.h"

void output_vertices(Graph<std::string> graph) {
    Vector<Vector<bool>> rel = graph.get_matrix();
    for (size_t i = 0; i < rel.size(); i++) {
        for (size_t j = 0; j < rel.size(); j++) {
            std::cout << rel[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void output_marks(Graph<std::string> graph) {
    Vector<std::string> marks = graph.get_marks();
    for (size_t i = 0; i < marks.size(); i++) {
        std::cout << marks[i] << " ";
    }
}

void output_edges(Graph<std::string> graph) {
    Vector<Vector<int>> edges = graph.get_edges();
    for (size_t i = 0; i < edges.size(); i++) {
        for (size_t j = 0; j < edges[i].size(); j++) {
            std::cout << edges[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    setlocale(0, "");
    Graph<std::string> graph;
    graph.add_vertex("a");
    graph.add_vertex("b");
    graph.add_edge("a", "b", 5);
    graph.add_vertex("c");
    output_vertices(graph);
    std::cout << std::endl;
    output_edges(graph);
    std::cout << std::endl;
    output_marks(graph);
    return 0;
}

//// Основной файл проекта, здесь main()
//
//#include <iostream>
//#include <queue>
//
//#include "../LibraryCPPTemplate/Vertex.h"
//#include "../LibraryCPPTemplate/vector.h"
//#include "../LibraryCPPTemplate/graph.h"
//
//int main() {
//    setlocale(0, "");
//    Graph<int> graph;
//    Vector<Vertex<int>> vertex;
//    for (size_t i = 0; i < vertex.size(); i++) {
//        vertex[i] = { (uint)i, 0 };
//    }
//
//    graph.add_vertex(vertex[0]);
//    graph.add_vertex(vertex[1]);
//    graph.add_vertex(vertex[2]);
//
//    std::cout << "Граф из 3 вершин" << std::endl << std::endl;
//    graph.print_matrix();
//    std::cout << std::endl;
//
//    std::cout << "Соединим 1 и 2, 2 и 3, 3 и 1" << std::endl << std::endl;
//    graph.add_edge(vertex[0], vertex[1]);
//    graph.add_edge(vertex[1], vertex[2]);
//    graph.add_edge(vertex[2], vertex[0]);
//
//    std::cout << "Граф из 3 соединенных вершин" << std::endl << std::endl;
//    graph.print_matrix();
//    std::cout << std::endl;
//
//    std::cout << "Вершины 1 и 2 связаны: " << graph.is_bounded(vertex[0], vertex[1]) << std::endl;
//    std::cout << "Вершины 1 и 3 связаны: " << graph.is_bounded(vertex[1], vertex[2]) << std::endl;
//    std::cout << "Вершины 2 и 1 связаны: " << graph.is_bounded(vertex[1], vertex[0]) << std::endl << std::endl;
//    
//    std::cout << "Добавим в граф еще одну вершину" << std::endl << std::endl;
//    vertex.push({3, 0});
//    graph.add_vertex(vertex[3]);
//    graph.print_matrix();
//    std::cout << std::endl;
//
//    std::cout << "Удалим из графа вершину 1" << std::endl << std::endl;
//    graph.delete_vertex(vertex[0]);
//    graph.print_matrix();
//    std::cout << std::endl;
//
//    std::cout << "Вершины 1 и 2 связаны: " << graph.is_bounded(vertex[0], vertex[1]) << std::endl;
//    std::cout << "Вершины 1 и 3 связаны: " << graph.is_bounded(vertex[1], vertex[2]) << std::endl;
//    std::cout << "Вершины 2 и 1 связаны: " << graph.is_bounded(vertex[1], vertex[0]) << std::endl << std::endl;
//
//	return 0;
//}