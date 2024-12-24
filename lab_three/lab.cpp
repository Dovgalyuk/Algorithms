#include <iostream>
#include <fstream>
#include "queue.h"

using namespace std;

void search(int** graph, int num_tops, const string &filename, int &start, int &end);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <file_path>" << endl;
        return 1;
    }
    ifstream input(argv[1]);

    if (!input) {
        cout << "Opening error" <<  endl;
        return 1;
    }

    int num_tops, start, end;
    input >> num_tops >> start >> end;

    int** graph = new int*[num_tops];

    for (int i = 0; i < num_tops; i++) {
        graph[i] = new int[num_tops];
        for (int j = 0; j < num_tops; j++) input >> graph[i][j];
    }

    search(graph, num_tops, argv[2], start, end);

    for (int i = 0; i < num_tops; i++) delete[] graph[i];
    delete[] graph;

    input.close();
    
    return 0;
}

void search(int** graph, int num_tops, const string &filename, int &start, int &end) {

    int* distances = new int[num_tops];
    for (int i = 0; i < num_tops; i++) distances[i] = -1; //0 -1 -1 -1
    distances[start-1] = 0;

    Queue* queue = queue_create();
    queue_insert(queue, start-1);

    while (!queue_empty(queue)) {
        int now = static_cast<int>(queue_get(queue));
        queue_remove(queue);

        if (now == (end - 1)) break;

        for (int i = 0; i < num_tops; i++) {
            if (graph[now][i] == 1 && distances[i] == -1) {
                distances[i] = distances[now] + 1;
                queue_insert(queue, i);
            }
            else queue_insert(queue, i);
        }
    }

    ofstream output(filename);
    if (distances[end-1] != -1) output << distances[end-1];
    else output << "IMPOSSIBLE";
    output.close();

    delete[] distances;
    queue_delete(queue);
}