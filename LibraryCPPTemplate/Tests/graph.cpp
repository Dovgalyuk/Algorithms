//#include <cassert>
//#include <iostream>
//#include <stdexcept>
//#include "Vertex.h"
//#include "graph.h"
//#include "vector.h"
//
//int main() {
//    setlocale(0, "");
//    Graph<std::string> graph;
//
//    // ���� 1: ���������� ������
//    graph.add_vertex("A");
//    graph.add_vertex("B");
//    graph.add_vertex("C");
//
//    // �������� ����� ������
//    Vector<std::string> marks = graph.get_marks();
//    assert(marks.size() == 3);
//    assert(marks[0] == "A");
//    assert(marks[1] == "B");
//    assert(marks[2] == "C");
//    std::cout << "���� 1 �������: ���������� ������." << std::endl;
//
//    // ���� 2: ���������� ����
//    graph.add_edge("A", "B", 1);
//    graph.add_edge("A", "C", 2);
//    graph.add_edge("B", "C", 3);
//
//    // �������� ������� ����
//    Vector<Vector<int>> edges = graph.get_edges();
//    assert(edges.size() == 3);
//    assert(edges[0][0] == 1); // A-B
//    assert(edges[0][1] == 2); // A-C
//    assert(edges[1][2] == 3); // B-C
//    std::cout << "���� 2 �������: ���������� ����." << std::endl;
//
//    // ���� 3: �������� ���������
//    assert(graph.is_bounded("A", "B") == true);
//    assert(graph.is_bounded("B", "C") == true);
//    assert(graph.is_bounded("A", "C") == true);
//    std::cout << "���� 3 �������: �������� ���������." << std::endl;
//
//    // ���� 4: �������� ������ ���������
//    Vector<Vertex<std::string>> test;
//    for (auto it = graph.begin("A"); it != graph.end("A"); ++it) {
//        test.push(*it);
//    }
//    assert(test[0].mark == "B");
//    assert(test[1].mark == "C");
//    std::cout << "���� 4 �������: �������� ������ ���������." << std::endl;
//
//    // ���� 5: �������� ����
//    graph.delete_edge("A", "B");
//    edges = graph.get_edges();
//    assert(edges[0][1] == 0); // A-B ������ ���� �������
//    std::cout << "���� 5 �������: �������� ����." << std::endl;
//
//    // ���� 6: �������� �������
//    graph.delete_vertex("B");
//    marks = graph.get_marks();
//    assert(marks.size() == 2);
//    assert(marks[0] == "A");
//    assert(marks[1] == "C");
//    std::cout << "���� 6 �������: �������� ������� B." << std::endl;
//
//    // ���� 7: �������� ���������� ������
//    graph.delete_vertex("A");
//    graph.delete_vertex("C");
//    marks = graph.get_marks();
//    assert(marks.size() == 0);
//    std::cout << "���� 7 �������: �������� ���������� ������." << std::endl;
//
//    std::cout << "��� ����� �������� �������!" << std::endl;
//    return 0;
//}