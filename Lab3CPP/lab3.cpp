#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "queue.h"
#include "vector.h"

using namespace std;

struct Graph {
    Vector* cities;
    Vector** adjList;
    int numCities;

    Graph(int maxCities) {
        cities = vector_create();
        adjList = new Vector*[maxCities];
        for (int i = 0; i < maxCities; ++i) {
            adjList[i] = vector_create();
        }
        numCities = 0;
    }

    ~Graph() {
    for (int i = 0; i < 100; ++i) {
        if (adjList[i]) {
            vector_delete(adjList[i]);
        }
    }
    delete[] adjList;
    vector_delete(cities);
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
        vector_set(adjList[index1], vector_size(adjList[index1]), static_cast<int>(index2));
        vector_set(adjList[index2], vector_size(adjList[index2]), static_cast<int>(index1));
    }
};

void bfs(Graph& graph, const string& start, const string& end, string* cityNames, int cityCount) {
    int startIdx = graph.getCityIndex(start, cityNames, cityCount);
    int endIdx = graph.getCityIndex(end, cityNames, cityCount);

    Vector* prev = vector_create();
    Vector* visited = vector_create();
    Queue* queue = queue_create();

    for (int i = 0; i < cityCount; ++i) {
        vector_set(prev, i, -1);
        vector_set(visited, i, 0);
    }

    vector_set(visited, startIdx, 1);
    queue_insert(queue, startIdx);

    while (!queue_empty(queue)) {
        int currentIdx = static_cast<int>(queue_get(queue));
        queue_remove(queue);

        if (currentIdx == endIdx) {
            Vector* path = vector_create();
            int city = endIdx;
            while (city != -1) {
                vector_set(path, vector_size(path), city);
                city = vector_get(prev, city);
            }

            for (int i = 0; i < vector_size(path); i++) {
                cout << cityNames[vector_get(path, i)] << " ";
            }
            cout << endl;

            vector_delete(path);
            break;
        }

        for (int i = 0; i < vector_size(graph.adjList[currentIdx]); ++i) {
            int neighborIdx = vector_get(graph.adjList[currentIdx], i);
            if (vector_get(visited, neighborIdx) == 0) {
                vector_set(visited, neighborIdx, 1);
                vector_set(prev, neighborIdx, currentIdx);
                queue_insert(queue, neighborIdx);
            }
        }
    }

    queue_delete(queue);
    vector_delete(prev);
    vector_delete(visited);
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

    int maxCities = 100;
    Graph graph(maxCities);
    string cityNames[100];
    int cityCount = 0;

    string city1, city2;
    string cities[100];
    int citiesCount = 0;

    while (input >> city1 >> city2) {
        if (!input.eof()) {
            graph.addEdge(city1, city2, cityNames, cityCount);
        }
        if (citiesCount < 100) {
            bool foundCity1 = false;
            bool foundCity2 = false;

            for (int i = 0; i < citiesCount; ++i) {
                if (cities[i] == city1) {
                    foundCity1 = true;
                }
                if (cities[i] == city2) {
                    foundCity2 = true;
                }
            }

            if (!foundCity1) {
                cities[citiesCount++] = city1;
            }
            if (!foundCity2) {
                cities[citiesCount++] = city2;
            }
        }
    }

    if (citiesCount >= 2) {
        string start = cities[citiesCount - 2];
        string end = cities[citiesCount - 1];
        bfs(graph, start, end, cityNames, cityCount);
    } else {
        cerr << "Недостаточно данных для определения начального и конечного городов." << endl;
    }

    return 0;
}
