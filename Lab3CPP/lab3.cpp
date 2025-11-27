#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "queue.h"

using namespace std;

int main(int argc, char **argv) {
    ifstream input(argv[1]);

    vector<string> lines;
    string line;

    while (getline(input, line)) {
        if (line.empty()) continue;
        lines.push_back(line);
    }
    input.close();

    if (lines.empty()) {
        return 1;
    }

    string last = lines.back();
    lines.pop_back();

    string start_name, end_name;
    size_t pos = last.find(' ');
    if (pos == string::npos) return 1;
    start_name = last.substr(0, pos);
    end_name = last.substr(pos + 1);

    map<string, int> city_to_id;
    vector<string> id_to_city;

    auto get_id = [&](const string& name) -> int {
        if (city_to_id.count(name) == 0) {
            city_to_id[name] = id_to_city.size();
            id_to_city.push_back(name);
        }
        return city_to_id[name];
    };

    get_id(start_name);
    get_id(end_name);

    vector<pair<string, string>> roads;

    for (const auto& ln : lines) {
        pos = ln.find(' ');
        if (pos == string::npos) continue;
        string a = ln.substr(0, pos);
        string b = ln.substr(pos + 1);
        roads.emplace_back(a, b);
        get_id(a);
        get_id(b);
    }

    int n = id_to_city.size();
    vector<vector<int>> graph(n);

    for (const auto& road : roads) {
        int u = city_to_id[road.first];
        int v = city_to_id[road.second];
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int start_id = city_to_id[start_name];
    int end_id = city_to_id[end_name];

    vector<int> parent(n, -1);
    vector<bool> visited(n, false);
    Queue* q = queue_create();

    queue_insert(q, start_id);
    visited[start_id] = true;
    parent[start_id] = -1;

    while (!queue_empty(q)) {
        int current = queue_get(q);
        queue_remove(q);
        if (current == end_id) break;
        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                queue_insert(q, neighbor);
            }
        }
    }

    queue_delete(q);

    if (!visited[end_id]) {
        return 1;
    }

    vector<int> path;
    int cur = end_id;
    while (cur != -1) {
        path.push_back(cur);
        cur = parent[cur];
    }

    reverse(path.begin(), path.end());

    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) cout << " ";
        cout << id_to_city[path[i]];
    }
    cout << endl;
}