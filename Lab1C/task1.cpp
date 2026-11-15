#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "queue.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "ERROR\n";
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cout << "ERROR\n";
        return 1;
    }

    vector<pair<string, string>> all_lines;
    string u, v;

    while (input >> u >> v) {
        all_lines.push_back({u, v});
    }

    if (all_lines.empty()) {
        cout << "ERROR\n";
        return 1;
    }

    string start_city = all_lines.back().first;
    string end_city = all_lines.back().second;

    vector<pair<string, string>> edges;
    for (size_t i = 0; i < all_lines.size() - 1; ++i) {
        edges.push_back(all_lines[i]);
    }

    map<string, int> city_to_id;
    vector<string> id_to_city;

    auto get_id = [&](const string& name) {
        if (city_to_id.find(name) == city_to_id.end()) {
            city_to_id[name] = id_to_city.size();
            id_to_city.push_back(name);
        }
        return city_to_id[name];
    };

    get_id(start_city);
    get_id(end_city);

    for (const auto& edge : edges) {
        get_id(edge.first);
        get_id(edge.second);
    }

    vector<vector<int>> adj(id_to_city.size());
    for (const auto& edge : edges) {
        int u_id = city_to_id[edge.first];
        int v_id = city_to_id[edge.second];
        adj[u_id].push_back(v_id);
        adj[v_id].push_back(u_id);
    }

    int start_id = city_to_id[start_city];
    int end_id = city_to_id[end_city];

    vector<int> parent(id_to_city.size(), -1);
    vector<bool> visited(id_to_city.size(), false);

    Queue* q = queue_create();
    queue_insert(q, start_id);
    visited[start_id] = true;

    while (!queue_empty(q)) {
        int curr = queue_get(q);
        queue_remove(q);

        if (curr == end_id) break;

        for (int neighbor : adj[curr]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = curr;
                queue_insert(q, neighbor);
            }
        }
    }
    queue_delete(q);

    if (!visited[end_id]) {
        cout << "No path\n";
        return 0;
    }

    vector<string> path;
    for (int curr = end_id; curr != -1; curr = parent[curr]) {
        path.push_back(id_to_city[curr]);
    }
    reverse(path.begin(), path.end());

    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << (i + 1 < path.size() ? " " : "\n");
    }

    return 0;
}