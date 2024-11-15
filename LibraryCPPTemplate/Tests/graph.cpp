#include <cassert>
#include <iostream>
#include <string>
#include "graph.h"
#include "vector.h"

int main() {
    setlocale(0, "");
    Graph<std::string, std::string> graph;

    // тест 1: добавление вершин
    graph.add_vertex("a");
    graph.add_vertex("b");
    graph.add_vertex("c");

    // проверка меток вершин
    Vector<std::string> marks = graph.get_vertices_marks();
    assert(marks.size() == 3);
    assert(marks[0] == "a");
    assert(marks[1] == "b");
    assert(marks[2] == "c");
    marks.clear();
    std::cout << "тест 1 пройден: добавление вершин." << std::endl;

    // тест 2: добавление рёбер
    graph.add_edge(1, 2, "m");
    graph.add_edge(0, 2, "a");
    graph.add_edge(2, 0, "am");
    graph.add_edge(2, 2, "ii");

    Vector<Vector<Edge<std::string>*>> edges = graph.get_matrix();

    assert(edges.size() == 3);
    assert(edges[0][1] == nullptr);
    assert(edges[1][2] != nullptr);
    assert(edges[2][2] != nullptr);
    std::cout << "тест 2 пройден: добавление рёбер." << std::endl;

    // тест 3: проверка связности
    assert(graph.is_bounded(1, 2) == true);
    assert(graph.is_bounded(2, 2) == true);
    assert(graph.is_bounded(2, 1) == false);
    std::cout << "тест 3 пройден: проверка связности." << std::endl;

    // тест 4: проверка работы итератора
    Vector<Vertex<std::string>> vertices = graph.get_vertices();
    Vector<Vertex<std::string>> test;
    for (auto it = graph.begin(2); it != graph.end(2); ++it) {
        test.push(vertices[it.get_neib_index()]);
    }
    assert(test[0].mark == "a");
    assert(test[1].mark == "c");
    std::cout << "тест 4 пройден: проверка работы итератора." << std::endl;

    // тест 5: удаление рёбер
    graph.delete_edge(0, 2);
    assert(graph.is_bounded(0, 2) == false); // a-b должно быть удалено
    std::cout << "тест 5 пройден: удаление рёбер." << std::endl;

    // тест 6: удаление вершины
    graph.delete_vertex(1);
    marks = graph.get_vertices_marks();
    assert(marks.size() == 2);
    assert(marks[0] == "a");
    assert(marks[1] == "c");
    marks.clear();
    std::cout << "тест 6 пройден: удаление вершины b." << std::endl;

    // тест 7: удаление оставшихся вершин
    graph.delete_vertex(0);
    graph.delete_vertex(0);
    //graph.delete_vertex(0);
    marks = graph.get_vertices_marks();
    assert(marks.size() == 0);
    marks.clear();
    std::cout << "тест 7 пройден: удаление оставшихся вершин." << std::endl;

    std::cout << "все тесты пройдены успешно!" << std::endl;
    return 0;
}