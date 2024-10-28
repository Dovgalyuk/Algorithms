// �������� ���� �������, ����� main()

#include <iostream>
#include <queue>
#include <string>

#include "../LibraryCPPTemplate/Vertex.h"
#include "../LibraryCPPTemplate/vector.h"
#include "../LibraryCPPTemplate/graph.h"

int main() {
    setlocale(0, "");
    Graph<int> graph;
    graph.add_vertex();

    return 0;
}

//// �������� ���� �������, ����� main()
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
//    std::cout << "���� �� 3 ������" << std::endl << std::endl;
//    graph.print_matrix();
//    std::cout << std::endl;
//
//    std::cout << "�������� 1 � 2, 2 � 3, 3 � 1" << std::endl << std::endl;
//    graph.add_edge(vertex[0], vertex[1]);
//    graph.add_edge(vertex[1], vertex[2]);
//    graph.add_edge(vertex[2], vertex[0]);
//
//    std::cout << "���� �� 3 ����������� ������" << std::endl << std::endl;
//    graph.print_matrix();
//    std::cout << std::endl;
//
//    std::cout << "������� 1 � 2 �������: " << graph.is_bounded(vertex[0], vertex[1]) << std::endl;
//    std::cout << "������� 1 � 3 �������: " << graph.is_bounded(vertex[1], vertex[2]) << std::endl;
//    std::cout << "������� 2 � 1 �������: " << graph.is_bounded(vertex[1], vertex[0]) << std::endl << std::endl;
//    
//    std::cout << "������� � ���� ��� ���� �������" << std::endl << std::endl;
//    vertex.push({3, 0});
//    graph.add_vertex(vertex[3]);
//    graph.print_matrix();
//    std::cout << std::endl;
//
//    std::cout << "������ �� ����� ������� 1" << std::endl << std::endl;
//    graph.delete_vertex(vertex[0]);
//    graph.print_matrix();
//    std::cout << std::endl;
//
//    std::cout << "������� 1 � 2 �������: " << graph.is_bounded(vertex[0], vertex[1]) << std::endl;
//    std::cout << "������� 1 � 3 �������: " << graph.is_bounded(vertex[1], vertex[2]) << std::endl;
//    std::cout << "������� 2 � 1 �������: " << graph.is_bounded(vertex[1], vertex[0]) << std::endl << std::endl;
//
//	return 0;
//}