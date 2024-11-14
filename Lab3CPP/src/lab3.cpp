#include "queue.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

int main() {
    ifstream input(INPUT_FILE);
    ofstream output(OUTPUT_FILE);
    
    if (!input.is_open()) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }
    if (!output.is_open()) {
        cerr << "Error opening output file!" << endl;
        return 1;
    }

    // Считываем количество вершин, начальную и конечную вершины
    int vertices, start, finish;
    input >> vertices >> start >> finish;
    start--; finish--; // Преобразуем в 0-based индекс для удобства

    // Создаем граф в виде списка смежности
    vector<vector<int>> graph(vertices);
    int u, v;
    while (input >> u >> v) {
        u--; v--; // Преобразуем в 0-based
        graph[u].push_back(v);
        graph[v].push_back(u); // Так как граф неориентированный
    }

    // Инициализируем очередь и вектор расстояний
    Queue queue;
    vector<int> distance(vertices, numeric_limits<int>::max());
    distance[start] = 0;
    queue.insert(start);

    // Поиск в ширину
    while (!queue.empty()) {
        int current = queue.get();
        queue.remove();

        for (int neighbor : graph[current]) {
            if (distance[neighbor] == numeric_limits<int>::max()) {
                distance[neighbor] = distance[current] + 1;
                queue.insert(neighbor);
            }
        }
    }

    // Выводим результат
    if (distance[finish] == numeric_limits<int>::max()) {
        output << "IMPOSSIBLE" << endl;
    } else {
        output << distance[finish] << endl;
    }

    input.close();
    output.close();
    return 0;
}
