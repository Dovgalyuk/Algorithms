#include <iostream>
#include <stdexcept>
#include <cassert>
#include "../LibraryCPPTemplate/Vertex.h"
#include "../LibraryCPPTemplate/vector.h"
#include "../LibraryCPPTemplate/graph.h"

void print_matrix(const Vector<Vector<int>>& matrix) {
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    setlocale(0, "");
    Graph<std::string> graph;

    // Тест 1: Добавление вершин
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");

    // Проверка меток вершин
    Vector<std::string> marks = graph.get_marks();
    assert(marks.size() == 3);
    assert(marks[0] == "A");
    assert(marks[1] == "B");
    assert(marks[2] == "C");
    std::cout << "Тест 1 пройден: Добавление вершин." << std::endl;

    // Тест 2: Добавление рёбер
    graph.add_edge("A", "B", 1);
    graph.add_edge("A", "C", 2);
    graph.add_edge("B", "C", 3);

    // Проверка матрицы рёбер
    Vector<Vector<int>> edges = graph.get_edges();
    assert(edges.size() == 3);
    assert(edges[0][0] == 1); // A-B
    assert(edges[0][1] == 2); // A-C
    assert(edges[1][2] == 3); // B-C
    std::cout << "Тест 2 пройден: Добавление рёбер." << std::endl;

    // Тест 3: Проверка связности
    assert(graph.is_bounded("A", "B") == true);
    assert(graph.is_bounded("B", "C") == true);
    assert(graph.is_bounded("A", "C") == true);
    std::cout << "Тест 3 пройден: Проверка связности." << std::endl;

    // Тест 4: Удаление рёбер
    graph.delete_edge("A", "B");
    edges = graph.get_edges();
    assert(edges[0][1] == 0); // A-B должно быть удалено
    std::cout << "Тест 4 пройден: Удаление рёбер." << std::endl;

    // Тест 5: Удаление вершин
    graph.delete_vertex("B");
    marks = graph.get_marks();
    assert(marks.size() == 2);
    assert(marks[0] == "A");
    assert(marks[1] == "C");
    std::cout << "Тест 5 пройден: Удаление вершины B." << std::endl;

    graph.delete_vertex("A");
    graph.delete_vertex("C");
    marks = graph.get_marks();
    assert(marks.size() == 0);
    std::cout << "Тест 6 пройден: Удаление оставшихся вершин." << std::endl;

    std::cout << "Все тесты пройдены успешно!" << std::endl;
    return 0;
}
