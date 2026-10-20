#include <iostream>
#include <fstream>
#include <cstddef>

#include "list.h"
#include "queue.h"

using namespace std;

void initialize_array(int* arr, int size) {
    for (int i = 1; i <= size; i++) {
        arr[i] = 0;
    }
}

void cleanup_resources(
    Queue* qForward,
    Queue* qBackward,
    int* parentForward,
    int* parentBackward
) {
    queue_delete(qForward);
    queue_delete(qBackward);
    delete[] parentForward;
    delete[] parentBackward;
}

bool expand_level(Queue* q, List** graph, int* parentSelf, int* parentOther,
                  int& meetSelf, int& meetOther, int num_vertices) {
    int levelSize = queue_size(q);
    for (int i = 0; i < levelSize; i++) {
        int u = queue_get(q);
        queue_remove(q);

        ListItem* end = list_end(graph[u]);
        ListItem* neighbour = list_first(graph[u]);

        while (neighbour != NULL && neighbour != end) {
            int v = list_item_data(neighbour);

            if (v <= 0 || v > num_vertices) {
                neighbour = list_item_next(neighbour);
                continue;
            }

            if (parentOther[v] != 0) {
                meetSelf = u;
                meetOther = v;
                return true;
            } else if (parentSelf[v] == 0) {
                parentSelf[v] = u;
                queue_insert(q, v);
            }

            neighbour = list_item_next(neighbour);
        }
    }
    return false;
}

int count_segment_length(int node, int root, int* parent) {
    int length = 0;
    int temp = node;
    while (true) {
        length++;
        if (temp == root) break;
        temp = parent[temp];
    }
    return length;
}

void write_segment(int* path, int startIdx, int node, int root, int* parent, int direction) {
    int idx = startIdx;
    int current = node;
    while (current != root) {
        path[idx] = current;
        idx += direction;
        current = parent[current];
    }
    path[idx] = root;
}

int* bidirectional_search(List** graph, int num_vertices, int start, int finish, int& path_length) {
    Queue* qForward = queue_create();
    Queue* qBackward = queue_create();

    int* parentForward = new int[num_vertices + 1];
    int* parentBackward = new int[num_vertices + 1];

    initialize_array(parentForward, num_vertices);
    initialize_array(parentBackward, num_vertices);

    queue_insert(qForward, start);
    parentForward[start] = start;

    queue_insert(qBackward, finish);
    parentBackward[finish] = finish;

    int meetFwd = 0;
    int meetBwd = 0;
    bool found = false;

    while (!queue_empty(qForward) && !queue_empty(qBackward) && !found) {
        if (expand_level(qForward, graph, parentForward, parentBackward, meetFwd, meetBwd, num_vertices)) {
            found = true;
            break;
        }
        if (expand_level(qBackward, graph, parentBackward, parentForward, meetBwd, meetFwd, num_vertices)) {
            found = true;
            break;
        }
    }

    if (!found) {
        cleanup_resources(qForward, qBackward, parentForward, parentBackward);
        return NULL;
    }

    int len1 = count_segment_length(meetFwd, start, parentForward);
    int len2 = count_segment_length(meetBwd, finish, parentBackward);
    int totalLen = len1 + len2;
    path_length = totalLen;

    int* path = new int[totalLen];

    write_segment(path, len1 - 1, meetFwd, start, parentForward, -1);

    write_segment(path, len1, meetBwd, finish, parentBackward, +1);

    cleanup_resources(qForward, qBackward, parentForward, parentBackward);

    return path;
}


int main(int argc,char* argv[]) {
    if (argc < 2) {
        cout << "Входной файл не найден!!" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) {
        cerr << "Ошибка чтения входного файла!" << endl;
        return 1;
    }

    int num_vertices, start, finish;
    inputFile >> num_vertices >> start >> finish;

    if (start == finish) {
        cout << start << endl;
        inputFile.close();
        return 0;
    }

    List** graph = new List*[num_vertices + 1];
    for (int i = 1; i <= num_vertices; i++) {
        graph[i] = list_create();
    }

    int u, v;
    while (inputFile >> u >> v) {
        list_insert(graph[u], v);
        list_insert(graph[v], u);
    }

    inputFile.close();

    int pathLength = 0;
    int *path = bidirectional_search(graph, num_vertices, start, finish, pathLength);

    if (path == NULL || pathLength == 0) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        for (int i = 0; i < pathLength; i++) {
            if (i > 0) {
                cout << " ";
            }
            cout << path[i];
        }
        cout << endl;

        delete[] path;
    }

    for (int i = 1; i <= num_vertices; i++) {
        list_delete(graph[i]);
    }
    delete[] graph;
}