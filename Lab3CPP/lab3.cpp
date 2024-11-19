#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "queue.h"
#include "vector.h"

using namespace std;

struct Graph {
    Vector* adjList[100];
    int numCities;

    Graph() {
        for (int i = 0; i < 100; ++i) {
            adjList[i] = vector_create();
        }
        numCities = 0;
    }

    ~Graph() {
        for (int i = 0; i < numCities; ++i) {
            vector_delete(adjList[i]);
        }
    }

    int getCityIndex(const string& city, string* cityNames, int& cityCount) {
        for (int i = 0; i < cityCount; ++i) {
            if (cityNames[i] == city) {
                return i;
            }
        }
        if (cityCount < 100) {
            cityNames[cityCount] = city;
            return cityCount++;
        }
        throw runtime_error("Превышено максимальное количество городов");
    }

    void addEdge(const string& city1, const string& city2, string* cityNames, int& cityCount) {
        int index1 = getCityIndex(city1, cityNames, cityCount);
        int index2 = getCityIndex(city2, cityNames, cityCount);
        vector_set(adjList[index1], vector_size(adjList[index1]), index2);
        vector_set(adjList[index2], vector_size(adjList[index2]), index1);
    }
};

void bfs(Graph& graph, const string& start, const string& end, string* cityNames, int cityCount) {
    int startIdx = graph.getCityIndex(start, cityNames, cityCount);
    int endIdx = graph.getCityIndex(end, cityNames, cityCount);

    Vector* prev = vector_create();
    Vector* visited = vector_create();
    Queue* queue = queue_create();

    if (!prev || !visited || !queue) {
        cerr << "Ошибка при создании структуры данных." << endl;
        vector_delete(prev);
        vector_delete(visited);
        queue_delete(queue);
        return;
    }

    for (int i = 0; i < cityCount; ++i) {
        vector_set(prev, i, -1);
        vector_set(visited, i, 0);
    }

    vector_set(visited, startIdx, 1);
    queue_insert(queue, startIdx);

    bool pathFound = false;

    while (!queue_empty(queue)) {
        int currentIdx = static_cast<int>(queue_get(queue));
        queue_remove(queue);

        if (currentIdx == endIdx) {
            pathFound = true;
            break;
        }

        for (size_t i = 0; i < vector_size(graph.adjList[currentIdx]); ++i) {
            int neighborIdx = vector_get(graph.adjList[currentIdx], i);
            if (vector_get(visited, neighborIdx) == 0) {
                vector_set(visited, neighborIdx, 1);
                vector_set(prev, neighborIdx, currentIdx);
                queue_insert(queue, neighborIdx);
            }
        }
    }

    if (pathFound) {
        Vector* path = vector_create();
        int city = endIdx;
        while (city != -1) {
            vector_set(path, vector_size(path), city);
            city = vector_get(prev, city);
        }

        for (int i = static_cast<int>(vector_size(path)) - 1; i >= 0; --i) {
            cout << cityNames[vector_get(path, i)] << " ";
        }
        cout << endl;

        vector_delete(path);
    } else {
        cout << "Нет пути от " << start << " до " << end << endl;
    }

    vector_delete(prev);
    vector_delete(visited);
    queue_delete(queue);
}


void printGraph(const Graph& graph, string* cityNames, int cityCount) {
    cout << "Граф:" << endl;
    for (int i = 0; i < cityCount; ++i) {
        cout << cityNames[i] << ": ";
        for (size_t j = 0; j < vector_size(graph.adjList[i]); ++j) {
            int neighborIdx = vector_get(graph.adjList[i], j);
            cout << cityNames[neighborIdx] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input) {
        cerr << "Ошибка открытия файла" << endl;
        return 1;
    }

    Graph graph;

    string cityNames[100];
    int cityCount = 0;

    string city1, city2;

    while (input >> city1 >> city2) {
        if (input.eof()) break;
        graph.addEdge(city1, city2, cityNames, cityCount);
    }

    if (cityCount >= 2) {
        bfs(graph, city1, city2, cityNames, cityCount);
    } else {
        cerr << "Недостаточно данных для определения начального и конечного городов." << endl;
    }

    return 0;
}
