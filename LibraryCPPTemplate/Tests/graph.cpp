#include <cassert>
#include <iostream>
#include <string>
#include "graph.h"
#include "vector.h"

int main() {
    setlocale(0, "");
    Graph<std::string, std::string> graph;

    // Тест 1: Добавление вершин
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");

    // Проверка меток вершин
    Vector<std::string> marks = graph.get_vertices_marks();
    assert(marks.size() == 3);
    assert(marks[0] == "A");
    assert(marks[1] == "B");
    assert(marks[2] == "C");
    marks.clear();
    std::cout << "Тест 1 пройден: Добавление вершин." << std::endl;

    // Тест 2: Добавление рёбер
    graph.add_edge(1, 2, "m");
    graph.add_edge(0, 2, "a");
    graph.add_edge(2, 0, "am");
    graph.add_edge(2, 2, "II");

    Vector<Edge<std::string, std::string>> edges = graph.get_edges();

    assert(edges.size() == 4);
    assert(edges[0].destination->number == 2 && edges[0].mark == "m");
    assert(edges[1].start->number == 0 && edges[1].destination->number == 2);
    assert(edges[2].start->number == 2 && edges[2].mark == "am");
    std::cout << "Тест 2 пройден: Добавление рёбер." << std::endl;

    // Тест 3: Проверка связности
    assert(graph.is_bounded(1, 2) == true);
    assert(graph.is_bounded(2, 2) == true);
    assert(graph.is_bounded(2, 1) == false);
    std::cout << "Тест 3 пройден: Проверка связности." << std::endl;

    // Тест 4: Проверка работы итератора
    Vector<Vertex<std::string>> test;
    for (auto it = graph.begin(2); it != graph.end(2); ++it) {
        test.push(*it);
    }
    assert(test[0].mark == "A");
    assert(test[1].mark == "C");
    std::cout << "Тест 4 пройден: Проверка работы итератора." << std::endl;

    // Тест 5: Удаление рёбер
    graph.delete_edge(0, 2);
    assert(graph.is_bounded(0, 2) == false); // A-B должно быть удалено
    std::cout << "Тест 5 пройден: Удаление рёбер." << std::endl;

    // Тест 6: Удаление вершины
    graph.delete_vertex(1);
    marks = graph.get_vertices_marks();
    assert(marks.size() == 2);
    assert(marks[0] == "A");
    assert(marks[1] == "C");
    marks.clear();
    std::cout << "Тест 6 пройден: Удаление вершины B." << std::endl;

    // Тест 7: Удаление оставшихся вершин
    graph.delete_vertex(0);
    graph.delete_vertex(0);
    //graph.delete_vertex(0);
    marks = graph.get_vertices_marks();
    assert(marks.size() == 0);
    marks.clear();
    std::cout << "Тест 7 пройден: Удаление оставшихся вершин." << std::endl;

    std::cout << "Все тесты пройдены успешно!" << std::endl;
    return 0;
}