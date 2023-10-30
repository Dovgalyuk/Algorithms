#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include "queue.h"
#include <algorithm>

using namespace std;
typedef map<string, vector<string>> Graph;
typedef map<string, Data> StringToDataMap;
typedef map<Data, string> DataToStringMap;

Data stringToData(const string& str, StringToDataMap& strToDataMap, DataToStringMap& dataToStrMap) {
    static Data nextData = 0;
    auto it = strToDataMap.find(str);
    if (it == strToDataMap.end()) {
        strToDataMap[str] = nextData;
        dataToStrMap[nextData] = str;
        return nextData++;
    }
    return it->second;
}

string dataToString(Data data, DataToStringMap& dataToStrMap) {
    return dataToStrMap[data];
}


vector<Data> bfsShortestPath(const Graph& graph, Data start, Data end, StringToDataMap& strToDataMap, DataToStringMap& dataToStrMap) {
    map<Data, Data> predecessors;
    map<Data, bool> visited;
    Queue* queue = queue_create();

    visited[start] = true;
    queue_insert(queue, start);

    while (!queue_empty(queue)) {
        Data current = queue_get(queue);
        queue_remove(queue);

        if (current == end) {
            break;
        }

        string currentCity = dataToString(current, dataToStrMap);
        for (const auto& neighborName : graph.at(currentCity)) {
            Data neighbor = stringToData(neighborName, strToDataMap, dataToStrMap);
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                predecessors[neighbor] = current;
                queue_insert(queue, neighbor);
            }
        }
    }

    queue_delete(queue);

    vector<Data> path;
    if (predecessors.find(end) == predecessors.end()) {
        return path; // No path found
    }

    for (Data at = end; at != start; at = predecessors[at]) {
        path.push_back(at);
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

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
            graph[city1].push_back(city2);
            graph[city2].push_back(city1);
        }
    }

    vector<Data> path = bfsShortestPath(graph, startData, endData, strToDataMap, dataToStrMap);

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

    return 0;
}