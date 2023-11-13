#include <iostream>
#include "queue.h"

using namespace std;

struct MyQueueNode {
    int vertex;
    int distance;
};

struct MyQueue {
    MyQueueNode* data;
    size_t size;
    size_t capacity;

    MyQueue() {
        size = 0;
        capacity = 1;
        data = new MyQueueNode[capacity];
    }


    void push(const MyQueueNode& value) { //Добавление элемента в конец очереди
        if (size == capacity) {
            size_t newCapacity = capacity * 2;
            MyQueueNode* newData = new MyQueueNode[newCapacity];
            for (size_t i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }

        data[size++] = value;
    }

    void pop() { //Удаление элемента из начала очереди
        if (size > 0) {
            for (size_t i = 1; i < size; ++i) {
                data[i - 1] = data[i];
            }
            --size;
        }
    }

    MyQueueNode front() const { // Возвращает первый элемент в очереди
        if (size > 0) {
            return data[0];
        }
        throw "Queue is empty";
    }

    bool empty() const { //Проверяет, является ли очередь пустой
        return size == 0;
    }
};

int shortestPath(int** graph, int vertices, int start, int finish) {
    int* visited = new int[vertices](); // Массив для отслеживания посещенных вершин

    MyQueue q;
    q.push({ start, 0 });
    visited[start] = 1;

    while (!q.empty()) {
        MyQueueNode current = q.front();
        q.pop();

        int currentVertex = current.vertex;
        int currentDistance = current.distance;

        if (currentVertex == finish) {
            delete[] visited;
            return currentDistance;
        }

        for (int i = 0; i < vertices; ++i) {
            if (graph[currentVertex][i] == 1 && visited[i] == 0) {
                q.push({ i, currentDistance + 1 });
                visited[i] = 1;
            }
        }
    }

    delete[] visited;
    return -1; // Если путь не найден
}

int main() {
    int vertices, start, finish;
    cin >> vertices >> start >> finish;

    //Чтение матрицы смежности
    int** graph = new int* [vertices];
    for (int i = 0; i < vertices; ++i) {
        graph[i] = new int[vertices];
        for (int j = 0; j < vertices; ++j) {
            cin >> graph[i][j];
        }
    }

    //Поиск кратчайшего пути
    int result = shortestPath(graph, vertices, start - 1, finish - 1);

    //Вывод результата
    if (result == -1) {
        cout << "IMPOSSIBLE" << endl;
    }
    else {
        cout << result << endl;
    }

    //Освобождение памяти
    for (int i = 0; i < vertices; ++i) {
        delete[] graph[i];
    }
    delete[] graph;

    return 0;
}