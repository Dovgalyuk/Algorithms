#include <cassert>
#include <iostream>
#include <string>
#include "graph.h"
#include "vector.h"

int main() {
    setlocale(0, "");
    Graph<std::string, std::string> graph;

    // ���� 1: ���������� ������
    graph.add_vertex("a");
    graph.add_vertex("b");
    graph.add_vertex("c");

    // �������� ����� ������
    Vector<std::string> marks = graph.get_vertices_marks();
    assert(marks.size() == 3);
    assert(marks[0] == "a");
    assert(marks[1] == "b");
    assert(marks[2] == "c");
    marks.clear();
    std::cout << "���� 1 �������: ���������� ������." << std::endl;

    // ���� 2: ���������� ����
    graph.add_edge(1, 2, "m");
    graph.add_edge(0, 2, "a");
    graph.add_edge(2, 0, "am");
    graph.add_edge(2, 2, "ii");

    Vector<Vector<Edge<std::string>*>> edges = graph.get_matrix();

    assert(edges.size() == 3);
    assert(edges[0][1] == nullptr);
    assert(edges[1][2] != nullptr);
    assert(edges[2][2] != nullptr);
    std::cout << "���� 2 �������: ���������� ����." << std::endl;

    // ���� 3: �������� ���������
    assert(graph.is_bounded(1, 2) == true);
    assert(graph.is_bounded(2, 2) == true);
    assert(graph.is_bounded(2, 1) == false);
    std::cout << "���� 3 �������: �������� ���������." << std::endl;

    // ���� 4: �������� ������ ���������
    Vector<Vertex<std::string>> vertices = graph.get_vertices();
    Vector<Vertex<std::string>> test;
    for (auto it = graph.begin(2); it != graph.end(2); ++it) {
        test.push(vertices[it.get_neib_index()]);
    }
    assert(test[0].mark == "a");
    assert(test[1].mark == "c");
    std::cout << "���� 4 �������: �������� ������ ���������." << std::endl;

    // ���� 5: �������� ����
    graph.delete_edge(0, 2);
    assert(graph.is_bounded(0, 2) == false); // a-b ������ ���� �������
    std::cout << "���� 5 �������: �������� ����." << std::endl;

    // ���� 6: �������� �������
    graph.delete_vertex(1);
    marks = graph.get_vertices_marks();
    assert(marks.size() == 2);
    assert(marks[0] == "a");
    assert(marks[1] == "c");
    marks.clear();
    std::cout << "���� 6 �������: �������� ������� b." << std::endl;

    // ���� 7: �������� ���������� ������
    graph.delete_vertex(0);
    graph.delete_vertex(0);
    //graph.delete_vertex(0);
    marks = graph.get_vertices_marks();
    assert(marks.size() == 0);
    marks.clear();
    std::cout << "���� 7 �������: �������� ���������� ������." << std::endl;

    std::cout << "��� ����� �������� �������!" << std::endl;
    return 0;
}