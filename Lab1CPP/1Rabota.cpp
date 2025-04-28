#include <fstream>
#include <iostream>
#include <vector>  
#include <locale>
#include <exception>
#include "queue.h"
#include "vector.h"

using namespace std;


vector<Vector*> component_storage;

void bfs(const Vector* adjacency_matrix, size_t vertex_count, 
         size_t start_vertex, Vector* component, Vector* visited) {
    Queue* queue = queue_create();
    
    queue_insert(queue, (Data)start_vertex);
    vector_set(visited, start_vertex, 1);

    while (!queue_empty(queue)) {
        size_t current = (size_t)queue_get(queue);
        queue_remove(queue);
        
        vector_resize(component, vector_size(component) + 1);
        vector_set(component, vector_size(component) - 1, (Data)(current + 1));

        for (size_t neighbor = 0; neighbor < vertex_count; ++neighbor) {
            if (vector_get(adjacency_matrix, current * vertex_count + neighbor)) {
                if (!vector_get(visited, neighbor)) {
                    vector_set(visited, neighbor, 1);
                    queue_insert(queue, (Data)neighbor);
                }
            }
        }
    }
    queue_delete(queue);
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc < 3) {
        cerr << "Ошибка: укажите путь к входному и выходному файлам." << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Ошибка: не удалось открыть входной файл " << argv[1] << endl;
        return 1;
    }

    ofstream outputFile(argv[2]);
    if (!outputFile) {
        cerr << "Ошибка: не удалось открыть выходной файл " << argv[2] << endl;
        inputFile.close();
        return 1;
    }

    try {
        size_t vertex_count;
        inputFile >> vertex_count;
        if (vertex_count == 0) {
            outputFile << 0 << endl;
            inputFile.close();
            outputFile.close();
            return 0;
        }

        Vector* adjacency_matrix = vector_create();
        vector_resize(adjacency_matrix, vertex_count * vertex_count);
        for (size_t i = 0; i < vertex_count; ++i) {
            for (size_t j = 0; j < vertex_count; ++j) {
                int value;
                inputFile >> value;
                vector_set(adjacency_matrix, i * vertex_count + j, value);
            }
        }

        Vector* visited = vector_create();
        vector_resize(visited, vertex_count);
        for (size_t i = 0; i < vertex_count; ++i) {
            vector_set(visited, i, 0);
        }

        Vector* components = vector_create();
        vector_resize(components, 0);
        size_t component_count = 0;
        component_storage.clear();

        for (size_t i = 0; i < vertex_count; ++i) {
            if (!vector_get(visited, i)) {
                Vector* component = vector_create();
                vector_resize(component, 0);
                bfs(adjacency_matrix, vertex_count, i, component, visited);
                
                component_storage.push_back(component);
                vector_resize(components, vector_size(components) + 1);
                vector_set(components, component_count, (Data)(component_storage.size() - 1));
                component_count++;
            }
        }

        outputFile << component_count << "\n";
        for (size_t i = 0; i < component_count; ++i) {
            Vector* component = component_storage[(size_t)vector_get(components, i)];
            for (size_t j = 0; j < vector_size(component); ++j) {
                outputFile << vector_get(component, j);
                if (j != vector_size(component) - 1)
                    outputFile << " ";
            }
            outputFile << "\n";
        }

        
        for (auto component : component_storage) {
            vector_delete(component);
        }
        vector_delete(adjacency_matrix);
        vector_delete(visited);
        vector_delete(components);

    } catch (const exception& e) {
        cerr << "Произошла ошибка: " << e.what() << endl;
        inputFile.close();
        outputFile.close();
        return 1;
    }

    inputFile.close();
    outputFile.close();
    return 0;
}