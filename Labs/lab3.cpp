#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"
#include <vector>


using namespace std;

const char ASCII = '0';

int main() {
    setlocale(LC_ALL, "rus");

    string input_path = "input";
    string output_path = "output";

    fstream input(input_path + ".txt", fstream::app | fstream::in);
    fstream output(output_path + ".txt", fstream::out);
    string text;

    char symbol;
    input >> symbol;
    int count_vertexes = symbol - ASCII; //Количество вершин

    int** matrix = new int* [count_vertexes];
    for (size_t i = 0; i < count_vertexes; i++) matrix[i] = new int[count_vertexes] {0};

    input >> symbol;
    int path_out = symbol - ASCII; //Вершина откуда

    input >> symbol;
    int path_in = symbol - ASCII; //Вершина куда

    if (path_in > count_vertexes) {
        cout << "Error\n";
        return 0;
    }

    vector<vector<int>> paths(count_vertexes);

    //reading the file
    if (input.is_open()) {
        int iterator = count_vertexes;
        while (!input.eof()) {
            int index_out, index_in;

            input >> symbol;
            if (symbol != '\n') index_out = symbol - ASCII;

            input >> symbol;
            if (symbol != '\n') index_in = symbol - ASCII;

            matrix[index_out - 1][index_in - 1] = 1;
            matrix[index_in - 1][index_out - 1] = 1;
            paths[index_out - 1].push_back(index_in - 1);

            iterator--;
            if (!iterator) break;
        }
    }
    else {
        cout << "Error opening the file\n";
    }

    vector<int> b(count_vertexes, 1e6);
    b[path_out - 1] = 0;

    Queue* queue = queue_create();
    queue_insert(queue, path_out - 1);

    bool check = false;
    for (size_t i = 0; i < count_vertexes; i++) { if (matrix[i][path_in - 1]) check = true; }

    if (!check) cout << "IMPOSSIBLE\n";
    else {
        //show the matrix
        for (size_t i = 0; i < count_vertexes; i++) {
            for (size_t j = 0; j < count_vertexes; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << "\n";
        }
        //поиск в ширину
        while (!queue_empty(queue))
        {
            int v = queue_get(queue);
            queue_remove(queue);
            for (int i = 0; i < paths[v].size(); i++) {
                int next = paths[v][i];
                if (b[next] > b[v] + 1) {
                    b[next] = b[v] + 1;
                    queue_insert(queue, next);
                }
            }
        }
        cout << "\nСамый короткий путь: " << b[path_in - 1] << "\n";
    }
    queue_delete (queue);
    input.close();

    return 0;
}
