#include <iostream>
#include <queue>

using namespace std;

struct MyQueueNode {
    int vertex;
    int distance;
};

int shortestPath(int** graph, int vertices, int start, int finish) {
    int* visited = new int[vertices](); //Массив для отслеживания посещенных вершин
    queue<MyQueueNode> q;
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
    return -1; //Если путь не найден
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