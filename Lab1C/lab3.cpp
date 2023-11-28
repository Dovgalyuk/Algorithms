#include <iostream>
#include <queue>
#include "queue.h"

using namespace std;

const int MAX_VERTICES = 100;

// ������� ��� ����������� ����� ����������� ���� �� ����� ������� � ������ � ��������������� �����
int shortestP(int adjMatrix[MAX_VERTICES][MAX_VERTICES], int numVertices, int start, int end) {
    // ������ ��� ������������ ���������� ������
    bool v[MAX_VERTICES] = { false };
    // �������� ������� ��� ������ � ������
    Queue* queue = queue_create();
    // ������ ��� �������� ���� ����� �� ��������� �������
    int distances[MAX_VERTICES] = { 0 };

    // ��������� ������� ����������� � ������� � ���������� ��� ����������
    queue_insert(queue, start);
    v[start - 1] = true;

    // ����� � ������
    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove(queue);

        // ���� ���������� �������� �������, ������������ ����� ����
        if (current == end) {
            queue_delete(queue);
            return distances[current - 1];
        }

        // ������� ���� ������� ������ ������� �������
        for (int i = 0; i < numVertices; i++) {
            if (adjMatrix[current - 1][i] && !v[i]) {
                // ���� ������� ������� �� ��������, ��� ����������� � �������
                queue_insert(queue, i + 1);
                v[i] = true;
                // ����� ���� �� ������� ������� ������������� �� 1
                distances[i] = distances[current - 1] + 1;
            }
        }
    }

    // ���� ���� �����������, � �������� ������� �� ����������, ������������ -1, ��� ��������, ��� ���������� ���� �� ����������
    queue_delete(queue);
    return -1; // IMPOSSIBLE
}

int main() {
    int numVertices, start, end;
    // ���� ���������� ������, ��������� � �������� ������
    cin >> numVertices >> start >> end;

    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    // ���� ������� ���������
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            cin >> adjMatrix[i][j];
        }
    }

    // ����� ������� ��� ����������� ����� ����������� ����
    int result = shortestP(adjMatrix, numVertices, start, end);
    // ����� ����������
    if (result == -1) {
        cout << "IMPOSSIBLE" << endl;
    }
    else {
        cout << result << endl;
    }

    return 0;
}
