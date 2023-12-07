#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "queue.h"

using namespace std;

int main() {
    std::unordered_map<std::string, std::unordered_set<std::string>> reactions;
    std::string start, reaction;

    std::cin >> start;
    while (std::cin >> reaction)
    {
        std::string substance1 = reaction.substr(0, reaction.find("->"));
        std::string substance2 = reaction.substr(reaction.find("->") + 2);
        reactions[substance1].insert(substance2);
    }

    Queue* queue = queue_create();
    std::unordered_set<std::string> visited;

    queue_insert(queue, start);
    visited.insert(start);

    while (!queue_empty(queue))
    {
        std::string current = queue_get(queue);
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
            std::cout << substance << " ";
    }

    queue_delete(queue);

    return 0;
}
