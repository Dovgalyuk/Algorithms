#include <iostream>
#include <vector>
#include "queue.h"
#include <string>

using namespace std;

const int MAXN = 100;

vector<int> graph[MAXN];

void buildGraph(vector<string> &reactions)
{
    for (const auto &reaction : reactions)
    {
        size_t arrowPos = reaction.find("->");
        int src = reaction[0] - 'A';
        int dest = reaction[arrowPos + 2] - 'A';
        graph[src].push_back(dest);
    }
}

void bfs(int start)
{
    Queue *q = queue_create();
    vector<bool> visited(MAXN, false);
    queue_insert(q, start);
    visited[start] = true;

    while (!queue_empty(q))
    {
        int node = queue_get(q);
        queue_remove(q);
        if (start != node)
        {
            cout << static_cast<char>(node + 'A') << endl;
        }
        for (const auto &neighbor : graph[node])
        {
            if (!visited[neighbor])
            {
                queue_insert(q, neighbor);
                visited[neighbor] = true;
            }
        }
    }
    queue_delete(q);
}

int main()
{
    string Sub;
    cin >> Sub;
    cin.ignore();

    vector<string> reactions;
    string reaction;
    while (getline(cin, reaction) && !reaction.empty())
    {
        reactions.push_back(reaction);
    }

    buildGraph(reactions);

    int startNode = Sub[0] - 'A';
    bfs(startNode);

    return 0;
}