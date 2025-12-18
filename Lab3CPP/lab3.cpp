#include <iostream>
#include <fstream>
#include "vector.h"
#include "queue.h"

using namespace std;

typedef Vector<int> Graph;
typedef Vector<int> Component;
typedef Vector<Component> ComponentsList;
typedef Vector<bool> Visited;

Component bfs(int start, size_t n, const Graph &matrix, Visited &visited) {
    Component component;

    Queue<int> q;
    q.insert(start);
    visited.set(start, true);
    component.push_back(start + 1);

    while (!q.empty()) {
        int current = q.get();
        q.remove();

        for (size_t i = 0; i < n; i++) {
            int edge = matrix.get(current * n + i);
            // current - в какую строку матрицы хотим попасть, i - сдвиг в этой строке
            
            if (edge == 1 && !visited.get(i)) {
                visited.set(i, true);
                q.insert(i);
                component.push_back(i + 1);
            }
        }
    }

    return component;
}

int main(int argc, char **argv) {

    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);

    size_t N;
    inputFile >> N;

    Graph matrix;
    matrix.resize(N * N);
    for (size_t i = 0; i < N * N; i++) {
        int value;
        inputFile >> value;
        matrix.set(i, value);
    }

    Visited visited;
    visited.resize(N);
    for (size_t i = 0; i < N; i++) visited.set(i, false);

    ComponentsList allComponents;
    for (size_t i = 0; i < N; i++) {
        if (!visited.get(i)) {
            Component component = bfs(i, N, matrix, visited);
            allComponents.push_back(component);
        }
    }

    outputFile << allComponents.size() << endl;
    cout << allComponents.size() << endl;

    for (size_t i = 0; i < allComponents.size(); i++) {
        Component comp = allComponents.get(i);
        
        for (size_t j = 0; j < comp.size(); j++) {
            outputFile << comp.get(j) << " ";
            cout << comp.get(j) << " ";
        }
        
        outputFile << endl;
        cout << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}