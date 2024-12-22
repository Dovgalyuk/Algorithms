#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"
#include "vector.h"

using namespace std;

// Реализация алгоритма BFS
void bfs(int** graph, int num_vertices, int start, const string& filename) {
    // Создаем вектор для хранения расстояний
    Vector* distances = vector_create();
    vector_resize(distances, num_vertices);

    // Инициализируем все расстояния значением -1
    for (int i = 0; i < num_vertices; i++) {
        vector_set(distances, i, -1);
    }
    vector_set(distances, start, 0); // Расстояние до стартовой вершины равно 0

    // Создаем очередь и добавляем стартовую вершину
    Queue* queue = queue_create();
    queue_insert(queue, start);

    // Пока очередь не пуста, выполняем обход
    while (!queue_empty(queue)) {
        int current = queue_get(queue); // Получаем текущую вершину
        queue_remove(queue);            // Удаляем её из очереди

        // Перебираем всех соседей текущей вершины
        for (int i = 0; i < num_vertices; i++) {
            if (graph[current][i] == 1 && vector_get(distances, i) == -1) {
                vector_set(distances, i, vector_get(distances, current) + 1); // Обновляем расстояние
                queue_insert(queue, i); // Добавляем соседнюю вершину в очередь
            }
        }
    }

    // Записываем результаты в файл
    ofstream output(filename);
    if (!output.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << " для записи." << endl;
    } else {
        for (int i = 0; i < num_vertices; i++) {
            output << vector_get(distances, i) << endl; // Записываем расстояния до каждой вершины
        }
        output.close();
    }

    // Удаляем вектор и очередь
    vector_delete(distances);
    queue_delete(queue);
}

int main(int argc, char* argv[]) {
    // Проверяем количество аргументов
    if (argc != 3) {
        cerr << "usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    // Открываем файл для чтения
    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << argv[1] << " для чтения." << endl;
        return 1;
    }

    // Считываем количество вершин
    int num_vertices;
    input >> num_vertices;

    // Создаем и заполняем граф
    int** graph = new int*[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        graph[i] = new int[num_vertices];
        for (int j = 0; j < num_vertices; j++) {
            input >> graph[i][j];
        }
    }
    input.close();

    // Запускаем BFS
    bfs(graph, num_vertices, 0, argv[2]);

    // Удаляем граф
    for (int i = 0; i < num_vertices; i++) {
        delete[] graph[i];
    }
    delete[] graph;

    return 0;
}
