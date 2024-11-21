#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include "queue.h"
#include <stdexcept>

using namespace std;

struct Graph {
    vector<vector<int>> adjList;
    int numCities;

    Graph() : numCities(0) {
        adjList.resize(100);
    }

    int getCityIndex(const string& city, vector<string>& cityNames) {
        for (size_t i = 0; i < cityNames.size(); ++i) {
            if (cityNames[i] == city) {
                return static_cast<int>(i);
            }
        }
        if (cityNames.size() < 100) {
            cityNames.push_back(city);
            return static_cast<int>(cityNames.size() - 1);
        }
        throw runtime_error("Превышено максимальное количество городов");
    }

    void addEdge(const string& city1, const string& city2, vector<string>& cityNames) {
        int index1 = getCityIndex(city1, cityNames);
        int index2 = getCityIndex(city2, cityNames);
        adjList[index1].push_back(index2);
        adjList[index2].push_back(index1);
    }
};

void bfs(Graph& graph, const string& start, const string& end, vector<string>& cityNames) {
    int cityCount = static_cast<int>(cityNames.size());
    vector<int> prev(cityCount, -1);
    vector<bool> visited(cityCount, false);
    queue<int> q;

    int startIdx = graph.getCityIndex(start, cityNames);
    int endIdx = graph.getCityIndex(end, cityNames);

    visited[startIdx] = true;
    q.push(startIdx);

    bool pathFound = false;

    while (!q.empty()) {
        int currentIdx = q.front();
        q.pop();

        if (currentIdx == endIdx) {
            pathFound = true;
            break;
        }

        for (int neighborIdx : graph.adjList[currentIdx]) {
            if (!visited[neighborIdx]) {
                visited[neighborIdx] = true;
                prev[neighborIdx] = currentIdx;
                q.push(neighborIdx);
            }
        }
    }

    if (pathFound) {
        vector<int> path;
        for (int city = endIdx; city != -1; city = prev[city]) {
            path.push_back(city);
        }
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            cout << cityNames[*it] << " ";
        }
        cout << endl;
    } else {
        cout << "Нет пути от " << start << " до " << end << endl;
    }
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
    vector<string> cityNames;

    string city1, city2;

    while (input >> city1 >> city2) {
        if (input.eof()) break;
        graph.addEdge(city1, city2, cityNames);
    }

    if (cityNames.size() >= 2) {
        bfs(graph, city1, city2, cityNames);
    } else {
        cerr << "Недостаточно данных для определения начального и конечного городов." << endl;
    }

    return 0;
}
