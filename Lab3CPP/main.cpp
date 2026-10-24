#include "queue.h"
#include <fstream>
#include <iostream>
#include <cstring>

const int MAX_NAME = 64;
const int MAX_VERTS = 1024;
const int MAX_EDGES = 4096;
const int BUCKETS = 1024;

static char names[MAX_VERTS][MAX_NAME];
static int  name_count = 0;

static int bucket_head[BUCKETS];
static int bucket_next[MAX_VERTS];

static unsigned hash_str(const char *s) 
{
    unsigned h = 5381;
    while (*s) h = h * 33u + static_cast<unsigned char>(*s++);
    return h % BUCKETS;
}

static int name_find(const char *s) 
{
    unsigned b = hash_str(s);
    for (int i = bucket_head[b]; i != -1; i = bucket_next[i])
        if (std::strcmp(names[i], s) == 0) return i;
    return -1;
}

static int name_get_or_add(const char *s) 
{
    int existing = name_find(s);
    if (existing >= 0) return existing;

    int id = name_count++;
    std::strncpy(names[id], s, MAX_NAME - 1);
    names[id][MAX_NAME - 1] = '\0';

    unsigned b = hash_str(s);
    bucket_next[id] = bucket_head[b];
    bucket_head[b]  = id;
    return id;
}

static const char *name_by_id(int id) 
{
    return names[id];
}

static int edge_from[MAX_EDGES];
static int edge_to[MAX_EDGES];
static int edge_count = 0;

static void add_edge(int from, int to) 
{
    if (edge_count >= MAX_EDGES) return;
    edge_from[edge_count] = from;
    edge_to[edge_count] = to;
    ++edge_count;
}

int main(int argc, char **argv) 
{
    if (argc < 2) 
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) 
    {
        std::cerr << "Cannot open file: " << argv[1] << '\n';
        return 1;
    }

    for (int i = 0; i < BUCKETS; ++i)   bucket_head[i] = -1;
    for (int i = 0; i < MAX_VERTS; ++i) bucket_next[i] = -1;

    char line[MAX_NAME * 4];
    char start[MAX_NAME];

    if (!file.getline(line, sizeof(line))) return 0;

    line[std::strcspn(line, "\r\n")] = '\0';
    std::strncpy(start, line, MAX_NAME - 1);
    start[MAX_NAME - 1] = '\0';

    int start_id = name_get_or_add(start);

    while (file.getline(line, sizeof(line))) 
    {
        line[std::strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0') continue;

        char *arrow = std::strstr(line, "->");
        if (!arrow) continue;

        *arrow = '\0';
        int f = name_get_or_add(line);
        int t = name_get_or_add(arrow + 2);
        add_edge(f, t);
    }

    bool *visited = new bool[name_count]();
    Queue *q = queue_create();

    visited[start_id] = true;
    queue_insert(q, start_id);

    while (!queue_empty(q)) 
    {
        int cur = queue_get(q);
        queue_remove(q);

        for (int i = 0; i < edge_count; ++i) 
        {
            if (edge_from[i] != cur) continue;
            int nx = edge_to[i];
            if (!visited[nx]) {
                visited[nx] = true;
                queue_insert(q, nx);
                std::cout << name_by_id(nx) << '\n';
            }
        }
    }

    queue_delete(q);
    delete[] visited;
    return 0;
}