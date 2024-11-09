#include <cassert>
#include <iostream>
#include <stdexcept>
#include "../LibraryCPPTemplate/graph.h"
#include "../LibraryCPPTemplate/vector.h"

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

//Graph<char, std::string> graph(2);
//
//graph.add_edge(0, 1, "a");
//graph.add_edge(0, 1, "b");
//graph.add_vertex();
//graph.add_edge(0, 2, "b");
//
//output(graph);
//
//for (auto it = graph.begin(0); it != graph.end(0); ++it) {
//	std::cout << (*it).number << std::endl;
//}
//
//graph.delete_edge(0, 1);
//graph.delete_edge(0, 1);
//graph.delete_edge(0, 2);
//std::cout << std::endl;
//output(graph);

void output(Graph<char, std::string> graph) {
	Vector<Vector<unsigned int>> matrix = graph.get_matrix();
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++)
			std::cout << matrix[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
	Vector<Edge<std::string>> edges = graph.get_edges();
	for (int i = 0; i < edges.size(); i++) {
		std::cout << edges[i].mark << " ";
	}
	std::cout <<std::endl;
}

int main() {
	Graph<std::string, int> graph(5);
	std::cout << graph << std::endl;
}
