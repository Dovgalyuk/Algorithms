#include <fstream>
#include <iostream>
#include <vector>

#include "queue.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    ifstream input(argv[1]);

    if (!input)
    {
        return 1;
    }

    int n;
    input >> n;

    vector<vector<int>> graph(n, vector<int>(n));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            input >> graph[i][j];
        }
    }

    vector<bool> visited(n, false);
    vector<vector<int>> components;

    Queue* queue = queue_create();

    for (int start = 0; start < n; ++start)
    {
        if (visited[start])
        {
            continue;
        }

        components.push_back(vector<int>());

        queue_insert(queue, start);
        visited[start] = true;

        while (!queue_empty(queue))
        {
            int vertex = queue_get(queue);
            queue_remove(queue);

            components.back().push_back(vertex + 1);

            for (int next = 0; next < n; ++next)
            {
                if (graph[vertex][next] == 1 && !visited[next])
                {
                    visited[next] = true;
                    queue_insert(queue, next);
                }
            }
        }
    }

    queue_delete(queue);

    cout << components.size() << '\n';

    for (size_t i = 0; i < components.size(); ++i)
    {
        for (size_t j = 0; j < components[i].size(); ++j)
        {
            if (j > 0)
            {
                cout << ' ';
            }

            cout << components[i][j];
        }

        cout << '\n';
    }

    return 0;
}