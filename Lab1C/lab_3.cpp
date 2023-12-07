#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "queue.h"

using namespace std;

int main() {
    unordered_map<std::string, std::unordered_set<std::string>> reactions;
    string start, reaction;

    cin >> start;
    while (cin >> reaction)
    {
        string substance1 = reaction.substr(0, reaction.find("->"));
        string substance2 = reaction.substr(reaction.find("->") + 2);
        reactions[substance1].insert(substance2);
    }

    Queue* queue = queue_create();
    unordered_set<std::string> visited;

    queue_insert(queue, start);
    visited.insert(start);

    while (!queue_empty(queue))
    {
        string current = queue_get(queue);
        queue_remove(queue);

        if (reactions.count(current) > 0) 
        {
            for (auto next : reactions[current]) 
            {
                if (visited.count(next) == 0) 
                {
                    queue_insert(queue, next);
                    visited.insert(next);
                }
            }
        }
    }

    for (auto substance : visited) 
    {
        if (substance != start)
            cout << substance << " ";
    }

    queue_delete(queue);

    return 0;
}
