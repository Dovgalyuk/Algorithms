#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <limits>
#include "queue.h"
#include "vector.h"

using namespace std;

struct Graph {
    Vector* cities;
    Vector** adjList;
    size_t numCities;

    Graph(size_t maxCities) {
        cities = vector_create();
        adjList = new Vector*[maxCities];
        for (size_t i = 0; i < maxCities; ++i) {
            adjList[i] = vector_create();
        }
        numCities = 0;
    }

    ~Graph() {
        for (size_t i = 0; i < numCities; ++i) {
            vector_delete(adjList[i]);
        }
        delete[] adjList;
        vector_delete(cities);
    }

    size_t getCityIndex(const string& city, string* cityNames, size_t& cityCount) {
        for (size_t i = 0; i < cityCount; ++i) {
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

    void addEdge(const string& city1, const string& city2, string* cityNames, size_t& cityCount) {
        size_t index1 = getCityIndex(city1, cityNames, cityCount);
        size_t index2 = getCityIndex(city2, cityNames, cityCount);
        vector_set(adjList[index1], vector_size(adjList[index1]), index2);
        vector_set(adjList[index2], vector_size(adjList[index2]), index1);
    }
};

void bfs(Graph& graph, const string& start, const string& end, string* cityNames, size_t cityCount) {
    size_t startIdx = graph.getCityIndex(start, cityNames, cityCount);
    size_t endIdx = graph.getCityIndex(end, cityNames, cityCount);

    Vector* prev = vector_create();
    Vector* visited = vector_create();
    Queue* queue = queue_create();

    const size_t NO_PREVIOUS = std::numeric_limits<size_t>::max();

    for (size_t i = 0; i < cityCount; ++i) {
        vector_set(prev, i, NO_PREVIOUS);
        vector_set(visited, i, 0);
    }

    vector_set(prev, startIdx, NO_PREVIOUS);
    vector_set(visited, startIdx, 1);
    queue_insert(queue, startIdx);

    while (!queue_empty(queue)) {
        size_t currentIdx = queue_get(queue);
        queue_remove(queue);

        if (currentIdx == endIdx) {
            Vector* path = vector_create();
            size_t city = endIdx;
            while (city != NO_PREVIOUS) {
                vector_set(path, vector_size(path), city);
                city = vector_get(prev, city);
            }

            for (size_t i = vector_size(path); i > 0; --i) {
                cout << cityNames[vector_get(path, i - 1)] << " ";
            }
            cout << endl;

            vector_delete(path);
            break;
        }

        for (size_t i = 0; i < vector_size(graph.adjList[currentIdx]); ++i) {
            size_t neighborIdx = vector_get(graph.adjList[currentIdx], i);
            if (vector_get(visited, neighborIdx) == 0) {
                vector_set(visited, neighborIdx, 1);
                vector_set(prev, neighborIdx, currentIdx);
                queue_insert(queue, neighborIdx);
            }
        }
    }

    if (vector_get(prev, endIdx) == NO_PREVIOUS) {
        cout << "Нет пути от " << start << " до " << end << endl;
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

    size_t maxCities = 100;
    Graph graph(maxCities);
    string cityNames[100];
    size_t cityCount = 0;

    string city1, city2;
    string cities[100];
    size_t citiesCount = 0;

    while (input >> city1 >> city2) {
        if (!input.eof()) {
            graph.addEdge(city1, city2, cityNames, cityCount);
        }
        if (citiesCount < 100) {
            bool foundCity1 = false;
            bool foundCity2 = false;

            for (size_t i = 0; i < citiesCount; ++i) {
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
