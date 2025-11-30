#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <stack>
#include "queue.h"

using namespace std;

bool parseRoad(const string& last, string& start_name, string& end_name) {
    size_t pos = last.find(' ');
    if (pos == string::npos) {
        return false;
    }
    start_name = last.substr(0, pos);
    end_name = last.substr(pos + 1);
    return true;
}

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
    if (!parseRoad(last, start_name, end_name)) {
        return 1;
    }

    map<string, int> city_to_id;
    vector<string> id_to_city;

    auto get_id = [&](const string& name) -> int {
        if (!city_to_id.contains(name)) {
            city_to_id[name] = id_to_city.size();
            id_to_city.push_back(name);
        }
        return city_to_id[name];
    };

    int start_id = get_id(start_name);
    int end_id = get_id(end_name);

    for (const auto& ln : lines) {
        string a, b;
        if (!parseRoad(ln, a, b)) continue;
        get_id(a);
        get_id(b);
    }


    int n = id_to_city.size();
    vector<vector<int>> graph(n);

    for (const auto& ln : lines) {
        string a, b;
        if (!parseRoad(ln, a, b)) continue;
        int u = city_to_id[a];
        int v = city_to_id[b];
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> parent(n, -1);
    Queue* q = queue_create();
    queue_insert(q, start_id);
    parent[start_id] = -2;

    while (!queue_empty(q)) {
        int current = queue_get(q);
        queue_remove(q);
        if (current == end_id) break;
        for (int neighbor : graph[current]) {
            if (parent[neighbor] == -1) {
                parent[neighbor] = current;
                queue_insert(q, neighbor);
            }
        }
    }

    queue_delete(q);

    if (parent[end_id] == -1) {
        return 1;
    }

    stack<string> path;
    int cur = end_id;
    while (cur != -2) {
        path.push(id_to_city[cur]);
        cur = parent[cur];
    }

    cout << path.top();
    path.pop();
    while (!path.empty()) {
        cout << " " << path.top();
        path.pop();
    }
    cout << endl;
}