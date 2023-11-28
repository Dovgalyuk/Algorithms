#include <iostream>
#include <queue>
#include "queue.h"

using namespace std;

const int MAX_VERTICES = 100;

// Функция для определения длины кратчайшего пути от одной вершины к другой в ориентированном графе
int shortestP(int adjMatrix[MAX_VERTICES][MAX_VERTICES], int numVertices, int start, int end) {
    // Массив для отслеживания посещенных вершин
    bool v[MAX_VERTICES] = { false };
    // Создание очереди для поиска в ширину
    Queue* queue = queue_create();
    // Массив для хранения длин путей от начальной вершины
    int distances[MAX_VERTICES] = { 0 };

    // Начальная вершина добавляется в очередь и помечается как посещенная
    queue_insert(queue, start);
    v[start - 1] = true;

    // Поиск в ширину
    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove(queue);

        // Если достигнута конечная вершина, возвращается длина пути
        if (current == end) {
            queue_delete(queue);
            return distances[current - 1];
        }

        // Перебор всех смежных вершин текущей вершины
        for (int i = 0; i < numVertices; i++) {
            if (adjMatrix[current - 1][i] && !v[i]) {
                // Если смежная вершина не посещена, она добавляется в очередь
                queue_insert(queue, i + 1);
                v[i] = true;
                // Длина пути до смежной вершины увеличивается на 1
                distances[i] = distances[current - 1] + 1;
            }
        }
    }

    // Если цикл завершается, и конечная вершина не достигнута, возвращается -1, что означает, что кратчайший путь не существует
    queue_delete(queue);
    return -1; // IMPOSSIBLE
}

int main() {
    int numVertices, start, end;
    // Ввод количества вершин, начальной и конечной вершин
    cin >> numVertices >> start >> end;

    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    // Ввод матрицы смежности
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            cin >> adjMatrix[i][j];
        }
    }

    // Вызов функции для определения длины кратчайшего пути
    int result = shortestP(adjMatrix, numVertices, start, end);
    // Вывод результата
    if (result == -1) {
        cout << "IMPOSSIBLE" << endl;
    }
    else {
        cout << result << endl;
    }

    return 0;
}
