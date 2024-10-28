// Основной файл проекта, здесь main()

#include <iostream>
#include <queue>
#include <string>

#include "../LibraryCPPTemplate/Vertex.h"
#include "../LibraryCPPTemplate/vector.h"
#include "../LibraryCPPTemplate/graph.h"

void output_matrix(Graph<std::string> graph);
void output_marks(Graph<std::string> graph);

int main() {
    setlocale(0, "");
    Graph<std::string> graph(5);
    output_matrix(graph);
    std::cout << std::endl;
    for (int i = 0; i < 5; i++) {
        graph.add_edge(i, i);
    }
    output_matrix(graph);
    std::cout << std::endl;
    for (int i = 0; i < 5; i++) {
        graph.add_edge(i, (size_t)4 - i);
    }
    output_matrix(graph);
    std::cout << std::endl;
    for (int i = 0; i < 5; i++) {
        std::string str(1, 'a' + i);
        graph.add_mark(i, str);
    }
    output_marks(graph);
    return 0;
}

void output_matrix(Graph<std::string> graph) {
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