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
    if(marks.size() != 3) return 1;
    if(marks[0] != "a") return 2;
    if(marks[1] != "b") return 3;
    if(marks[2] != "c") return 4;
    marks.clear();
    std::cout << "test 1 vertecies adding: success" << std::endl;

    // ���� 2: ���������� ����
    graph.add_edge(1, 2, "m");
    graph.add_edge(0, 2, "a");
    graph.add_edge(2, 0, "am");
    graph.add_edge(2, 2, "ii");

    Vector<Vector<Edge<std::string>*>> edges = graph.get_matrix();

    if(edges.size() != 3) return 5;
    if(edges[0][1] != nullptr) return 6;
    if(edges[1][2] == nullptr) return 7;
    if(edges[2][2] == nullptr) return 8;
    std::cout << "test 2 edges adding: success" << std::endl;

    // ���� 3: �������� ���������
    if(graph.is_bounded(1, 2) != true) return 9;
    if(graph.is_bounded(2, 2) != true) return 10;
    if(graph.is_bounded(2, 1) != false) return 11;
    std::cout << "test 3 is_bounded: success" << std::endl;

    // ���� 4: �������� ������ ���������
    Vector<Vertex<std::string>> vertices = graph.get_vertices();
    Vector<Vertex<std::string>> test;
    for (auto it = graph.begin(2); it != graph.end(2); ++it) {
        test.push(vertices[it.get_neib_index()]);
    }
    if(test[0].mark != "a") return 12;
    if(test[1].mark != "c") return 13;
    std::cout << "test 4 iterator: success" << std::endl;

    // ���� 5: �������� ����
    graph.delete_edge(0, 2);
    if(graph.is_bounded(0, 2) != false) return 14; // a-b ������ ���� �������
    std::cout << "test 5 edges deleting: success" << std::endl;

    // ���� 6: �������� �������
    graph.delete_vertex(1);
    marks = graph.get_vertices_marks();
    if(marks.size() != 2) return 15;
    if(marks[0] != "a") return 16;
    if(marks[1] != "c") return 17;
    marks.clear();
    std::cout << "test 6 vertex b deleting: success" << std::endl;

    // ���� 7: �������� ���������� ������
    graph.delete_vertex(0);
    graph.delete_vertex(0);
    marks = graph.get_vertices_marks();
    if(marks.size() != 0) return 18;
    marks.clear();
    std::cout << "test 7 deleting the remaining: success" << std::endl;

    std::cout << "all tests was passed successfully" << std::endl;
    return 0;
}