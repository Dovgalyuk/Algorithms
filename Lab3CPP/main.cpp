#include "queue.h"
#include <fstream>
#include <iostream>
#include <cstring>

const int MAX_NAME  = 64;
const int MAX_VERTS = 1024;

static char names[MAX_VERTS][MAX_NAME];
static int  name_count = 0;
static int  adj[MAX_VERTS][MAX_VERTS] = {};

static int name_get_or_add(const char *s)
{
    for (int i = 0; i < name_count; ++i)
        if (std::strcmp(names[i], s) == 0) return i;

    int id = name_count++;
    std::strcpy(names[id], s);
    return id;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    std::ifstream file{argv[1]};
    if (!file)
    {
        std::cerr << "Cannot open file: " << argv[1] << '\n';
        return 1;
    }

    char line[256];
    char start[MAX_NAME];

    if (!file.getline(line, sizeof(line))) return 0;
    std::strcpy(start, line);
    int start_id = name_get_or_add(start);

    while (file.getline(line, sizeof(line)))
    {
        if (line[0] == '\0') continue;

        char *arrow = std::strstr(line, "->");
        if (!arrow) continue;

        *arrow = '\0';
        int f = name_get_or_add(line);
        int t = name_get_or_add(arrow + 2);
        adj[f][t] = 1;
    }

    int *visited = new int[name_count]();
    Queue *q = queue_create();

    visited[start_id] = 1;
    queue_insert(q, start_id);

    while (!queue_empty(q))
    {
        int cur = queue_get(q);
        queue_remove(q);

        for (int nx = 0; nx < name_count; ++nx)
        {
            if (adj[cur][nx] && !visited[nx])
            {
                visited[nx] = 1;
                queue_insert(q, nx);
                std::cout << names[nx] << '\n';
            }
        }
    }

    queue_delete(q);
    delete[] visited;
    return 0;
}