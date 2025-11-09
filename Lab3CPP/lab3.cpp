#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include "queue.h"

using namespace std;

typedef map<string, size_t> City_Id;
typedef map<size_t, string> Id_City;
typedef map<size_t, vector<size_t>> Graph;

City_Id city_id;
Id_City id_city;
size_t next_id = 0;

size_t Id_get_city(const string& name) {

    if (city_id.count(name) == 0) {

        city_id[name] = next_id;
        id_city[next_id] = name;
        next_id++;
    }
    return city_id[name];
}

vector<size_t> search_puti(Graph& graph, size_t start, size_t end) {

    bool had_directly = false;

    auto search_end_start = find(graph[start].begin(), graph[start].end(), end);
    auto search_start_end = find(graph[end].begin(), graph[end].end(), start);

    if (search_end_start != graph[start].end()) {

        graph[start].erase(search_end_start);
        graph[end].erase(search_start_end);
        had_directly = true;
    }

    vector<int> visited(next_id, 0);
    vector<size_t> parent(next_id, next_id);

    Queue* queue = queue_create();
    queue_insert(queue, start);
    visited[start] = 1;

    while (!queue_empty(queue)) {

        size_t vershin = queue_get(queue);
        queue_remove(queue);

        if (vershin == end)
            break;

        for (size_t sosedi : graph[vershin]) {

            if (!visited[sosedi]) {

                visited[sosedi] = 1;
                parent[sosedi] = vershin;
                queue_insert(queue, sosedi);
            }
        }
    }

    queue_delete(queue);

    if (!visited[end]) {
        if (had_directly) 
            return { start, end };
        return {};
    }

    vector<size_t> path;
    for (size_t i = end; i != next_id; i = parent[i]) {
        path.push_back(i);

        if (i == start)
            break;
    }
    reverse(path.begin(), path.end());

    return path;
}

int main(int argc, char** argv) {
	(void)argc;

    ifstream file1(argv[1]);
    if (!file1.is_open()){
        return 1;
    }

    Graph graph;
    string a, b;

    while (file1 >> a >> b) {

        size_t id_a = Id_get_city(a);
        size_t id_b = Id_get_city(b);

        graph[id_a].push_back(id_b);
        graph[id_b].push_back(id_a);
    }


    size_t start = Id_get_city("Start");
    size_t end = Id_get_city("End");
    vector<size_t> path = search_puti(graph, start, end);

    if (path.empty()) {
        cout << "No path";
    }
    else {
        for (size_t i = 0; i < path.size(); i++) {

            cout << id_city[path[i]];
            if (i + 1 < path.size())
                cout << " ";
        }
    }

    file1.close();
    return 0;
}
