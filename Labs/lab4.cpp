#include <iostream>
#include "graph.h"

using namespace std;

typedef Graph<int> MyGraph;

const int INF = 999999; // �������� "�������������" ��� ���������� ����� ����� ���������

void floydWarshall(MyGraph* graph) {
    size_t vertex_count = graph->getVertexAmount();

    // ������� ������� ��� �������� ���� ���������� �����
    int** dist = new int* [vertex_count];
    for (size_t i = 0; i < vertex_count; ++i) {
        dist[i] = new int[vertex_count];
        for (size_t j = 0; j < vertex_count; ++j) {
            if (i == j) {
                dist[i][j] = 0; // ���������� �� ������� �� ����� ���� ����� 0
            }
            else if (graph->isEdgeExist(i, j)) {
                dist[i][j] = graph->getEdge(i, j)->getEdgeData(); // ��������� ��������� ����������
            }
            else {
                dist[i][j] = INF; // �������������� ��������� ���������� ��� "�������������"
            }
        }
    }

    // �������� ������
    for (size_t k = 0; k < vertex_count; ++k) {
        for (size_t i = 0; i < vertex_count; ++i) {
            for (size_t j = 0; j < vertex_count; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // ����� �����������
    cout << "���������� ���� ����� ���������:\n";
    for (size_t i = 0; i < vertex_count; ++i) {
        for (size_t j = 0; j < vertex_count; ++j) {
            if (dist[i][j] == INF) {
                cout << "INF ";
            }
            else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }

    // ����������� ���������� ������ ��� �������
    for (size_t i = 0; i < vertex_count; ++i) {
        delete[] dist[i];
    }
    delete[] dist;
}

int main() {
    setlocale(LC_ALL, "ru");
    size_t vertex_count;
    cout << "������� ���������� ������ � �����: ";
    cin >> vertex_count;

    MyGraph* graph = new MyGraph(vertex_count, INF); // ������� ���� � �������� ������ ������ � ���������� "�������������"

    // ������ ���������� ����� (����)
    cout << "������� ������ � ����� ��� �������:\n";
    for (size_t i = 0; i < vertex_count; ++i) {
        for (size_t j = 0; j < vertex_count; ++j) {
            int edge_data;
            cin >> edge_data;
            if (edge_data != INF) {
                graph->addEdge(i, j, edge_data); // ���������� ���� � ����
            }
        }
    }

    // ����� ������� ��� ���������� ���������� �����
    floydWarshall(graph);

    delete graph; // ������������ ������, ���������� ��� �����
    return 0;
}