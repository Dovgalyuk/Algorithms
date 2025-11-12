#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "queue.h"

using namespace std;

pair<string, string> parse_reaction(const string& reaction) {
    size_t pos = reaction.find("->");
    if (pos == string::npos) {
        return make_pair("", "");
    }
    string from = reaction.substr(0, pos);
    string to = reaction.substr(pos + 2);
    return make_pair(from, to);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Error: Cannot open input file " << argv[1] << endl;
        return 1;
    }

    string start_substance;
    getline(input, start_substance);

    unordered_map<string, int> substance_to_id;
    vector<string> id_to_substance;
    vector<vector<int>> reactions_graph;

    auto get_id = [&](const string& substance) -> int {
        auto it = substance_to_id.find(substance);
        if (it != substance_to_id.end()) {
            return it->second;
        }
        int new_id = static_cast<int>(id_to_substance.size());
        substance_to_id[substance] = new_id;
        id_to_substance.push_back(substance);
        reactions_graph.push_back(vector<int>());
        return new_id;
        };

    int start_id = get_id(start_substance);
    string line;
    while (getline(input, line)) {
        if (line.empty()) continue;
        pair<string, string> reaction_pair = parse_reaction(line);
        if (!reaction_pair.first.empty() && !reaction_pair.second.empty()) {
            int from_id = get_id(reaction_pair.first);
            int to_id = get_id(reaction_pair.second);
            reactions_graph[from_id].push_back(to_id);
        }
    }
    Queue* queue = queue_create();
    vector<bool> visited(id_to_substance.size(), false);
    vector<string> result;

    queue_insert(queue, start_id);
    visited[start_id] = true;

    while (!queue_empty(queue)) {
        int current_id = queue_get(queue);
        queue_remove(queue);
        for (size_t i = 0; i < reactions_graph[current_id].size(); i++) {
            int next_id = reactions_graph[current_id][i];
            if (!visited[next_id]) {
                visited[next_id] = true;
                result.push_back(id_to_substance[next_id]);
                queue_insert(queue, next_id);
            }
        }
    }
    queue_delete(queue);

    sort(result.begin(), result.end());
    for (const string& substance : result) {
        cout << substance << endl;
    }
    return 0;
}