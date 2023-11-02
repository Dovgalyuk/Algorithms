#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "queue.h"
#include <algorithm>

using namespace std;
typedef vector<vector<Data>> Graph;
typedef map<string, Data> StringToDataMap;
typedef vector<string> DataToStringMap;

Data stringToData(const string& str, StringToDataMap& strToDataMap, DataToStringMap& dataToStrMap) {
    static Data nextData = 0;
    auto it = strToDataMap.find(str);
    if (it == strToDataMap.end()) {
        strToDataMap[str] = nextData;
        dataToStrMap.push_back(str);
        return nextData++;
    }
    return it->second;
}

string dataToString(Data data, DataToStringMap& dataToStrMap) {
    return dataToStrMap[data];
}


vector<Data> bfsShortestPath(const Graph& graph, Data start, Data end) {
    size_t max_index = graph.size() - 1;
    Data* predecessors = new Data[max_index + 1];
    fill_n(predecessors, max_index + 1, 0);
    bool* visited = new bool[max_index + 1];
    fill_n(visited, max_index + 1, false);

    Queue* queue = queue_create();

    visited[start] = true;
    queue_insert(queue, start);

    while (!queue_empty(queue)) {
        Data current = queue_get(queue);
        queue_remove(queue);

        if (current == end) {
            break;
        }

        for (const auto& neighbor : graph.at(current)) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                predecessors[neighbor] = current;
                queue_insert(queue, neighbor);
            }
        }
    }

    queue_delete(queue);

    vector<Data> path;
    if (!visited[end]) {
        delete[] predecessors;
        delete[] visited;
        return path;
    }

    for (Data at = end; at != start; at = predecessors[at]) {
        path.push_back(at);
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

    delete[] predecessors;
    delete[] visited;

    return path;
}

int main() {
    ifstream input("input.txt");
    vector<string> lines;
    string line;
    while (getline(input, line)) {
        lines.push_back(line);
    }
    input.close();
    if (!lines.empty()) {
        istringstream last_line_stream(lines.back());
        string startCity, endCity;
        last_line_stream >> startCity >> endCity;
        lines.pop_back();
        StringToDataMap strToDataMap;
        DataToStringMap dataToStrMap;

        Data startData = stringToData(startCity, strToDataMap, dataToStrMap);
        Data endData = stringToData(endCity, strToDataMap, dataToStrMap);
        Graph graph;
        for (const auto& l : lines) {
            istringstream iss(l);
            string city1, city2;
            while (iss >> city1 >> city2) {
                Data city1Data = stringToData(city1, strToDataMap, dataToStrMap);
                Data city2Data = stringToData(city2, strToDataMap, dataToStrMap);
                Data maxCityData = max(city1Data, city2Data);
                if ((Data)graph.size() <= maxCityData) {
                    graph.resize(maxCityData + 1);
                }
                graph[city1Data].push_back(city2Data);
                graph[city2Data].push_back(city1Data);
            }
        }


        vector<Data> path = bfsShortestPath(graph, startData, endData);

        ofstream output("output.txt");
        if (!path.empty()) {
            for (Data data : path) {
                output << dataToString(data, dataToStrMap) << " ";
            }
        }
        else {
            output << "No path found.";
        }
        output.close();
    }
    else
    {
        cerr << "Input file is empty or does not contain any lines." << endl;
        return 1;
    }
    return 0;
}