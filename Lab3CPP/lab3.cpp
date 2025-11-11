#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
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

    unordered_map<string, vector<string>> reactions;
    string line;
    while (getline(input, line)) {
        if (line.empty()) continue;
        pair<string, string> reaction_pair = parse_reaction(line);
        if (!reaction_pair.first.empty() && !reaction_pair.second.empty()) {
            reactions[reaction_pair.first].push_back(reaction_pair.second);
        }
    }

    Queue* queue = queue_create();
    unordered_set<string> visited;
    vector<string> result;

    visited.insert(start_substance);
    unordered_map<string, int> substance_map;
    unordered_map<int, string> reverse_map;
    int next_id = 0;

    auto get_id = [&](const string& substance) {
        if (substance_map.find(substance) == substance_map.end()) {
            substance_map[substance] = next_id;
            reverse_map[next_id] = substance;
            next_id++;
        }
        return substance_map[substance];
        };

    queue_insert(queue, get_id(start_substance));

    while (!queue_empty(queue)) {
        int current_id = queue_get(queue);
        queue_remove(queue);

        string current = reverse_map[current_id];

        if (reactions.find(current) != reactions.end()) {
            for (const string& next : reactions[current]) {
                if (visited.find(next) == visited.end()) {
                    visited.insert(next);
                    result.push_back(next);
                    queue_insert(queue, get_id(next));
                }
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