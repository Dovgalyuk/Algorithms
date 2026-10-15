#include <iostream>
#include <fstream>
#include <cstddef>

#include "list.h"
#include "queue.h"

using namespace std;

int* bidirectional_search(List** graph, int num_vertices, int start, int finish, int& path_length) {
    Queue* qForward = queue_create();
    Queue* qBackward = queue_create();

    int* parentForward = new int[num_vertices + 1];
    int* parentBackward = new int[num_vertices + 1];

    for (int i = 1; i <= num_vertices; i++) {
        parentForward[i] = 0;
        parentBackward[i] = 0;
    }

    queue_insert(qForward, start);
    parentForward[start] = start;

    queue_insert(qBackward, finish);
    parentBackward[finish] = finish;

    int meetFwd = 0;
    int meetBwd = 0;
    bool found = false;

    while (!queue_empty(qForward) && !queue_empty(qBackward) && !found) {
        int u = queue_get(qForward);
        queue_remove(qForward);

        ListItem* neighbour = list_first(graph[u]);
        while (neighbour != NULL && !found) {
            int v = list_item_data(neighbour);

            if (parentBackward[v] != 0) {
                meetFwd = u;
                meetBwd = v;
                found = true;
            } else if (parentForward[v] == 0) {
                parentForward[v] = u;
                queue_insert(qForward, v);
            }

            neighbour = list_item_next(neighbour);
        }
        if (found) break;

        u = queue_get(qBackward);
        queue_remove(qBackward);

        neighbour = list_first(graph[u]);
        while (neighbour != NULL && !found) {
            int v = list_item_data(neighbour);

            if (parentForward[v] != 0) {
                meetFwd = v;
                meetBwd = u;
                found = true;
            } else if (parentBackward[v] == 0) {
                parentBackward[v] = u;
                queue_insert(qBackward, v);
            }

            neighbour = list_item_next(neighbour);
        }
    }
    if (!found) {
        path_length = 0;

        queue_delete(qForward);
        queue_delete(qBackward);
        delete[] parentForward;
        delete[] parentBackward;

        return NULL;
    }

    int len1 = 0;
    int temp_node = meetFwd;
    while (true) {
        len1++;
        if (temp_node == start) break;
        temp_node = parentForward[temp_node];
    }

    int len2 = 0;
    temp_node = meetBwd;
    while (true) {
        len2++;
        if (temp_node == finish) break;
        temp_node = parentBackward[temp_node];
    }

    int totalLen = len1 + len2;
    path_length = totalLen;

    int* path = new int[totalLen];

    int idx = len1 - 1;
    int current = meetFwd;
    while (current != start) {
        path[idx] = current;
        idx--;
        current = parentForward[current];
    }
    path[idx] = start;

    idx = len1;
    current = meetBwd;
    while (current != finish) {
        path[idx] = current;
        idx++;
        current = parentBackward[current];
    }
    path[idx] = finish;

    queue_delete(qForward);
    queue_delete(qBackward);
    delete[] parentForward;
    delete[] parentBackward;

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