#include <iostream>
#include <fstream>
#include <vector>
#include "queue.h"
using namespace std;

void lab_3(int a, int b, ifstream& file, Queue* result_queue) {
    Queue* queue1 = queue_create();
    Queue* queue2 = queue_create();
    Queue* queue3 = queue_create();
    int temp;
    while (file >> temp) {
        if (temp < a) {
            queue_insert(queue1, temp);
        } else if (temp <= b) {
            queue_insert(queue2, temp);
        } else {
            queue_insert(queue3, temp);
        }
    }
    while (!queue_empty(queue1)) {
        queue_insert(result_queue, queue_get(queue1));
        queue_remove(queue1);
    }
    while (!queue_empty(queue2)) {
        queue_insert(result_queue, queue_get(queue2));
        queue_remove(queue2);
    }
    while (!queue_empty(queue3)) {
        queue_insert(result_queue, queue_get(queue3));
        queue_remove(queue3);
    }
    queue_delete(queue1);
    queue_delete(queue2);
    queue_delete(queue3);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    int a, b;
    if (!(file >> a >> b)) {
        std::cout << "Error reading from file\n";
        file.close();
        return 1;
    }

    vector<int> file_data;
    int temp;
    while(file >> temp){
        file_data.push_back(temp);
    }
    file.clear();  // Clear flags
    file.seekg(0, ios::beg);
    if (!(file >> a >> b)) {
        std::cout << "Error reading from file\n";
        file.close();
        return 1;
    }
    Queue * result_queue = queue_create();
    lab_3(a, b, file, result_queue);

    bool is_solve = true;
    for(int temp_file : file_data){
        if (queue_empty(result_queue))
        {
            is_solve = false;
            break;
        }
        int temp_queue = queue_get(result_queue);
        queue_remove(result_queue);
        if (temp_file != temp_queue)
        {
            is_solve = false;
            break;
        }
    }

    if (!queue_empty(result_queue))
    {
        is_solve = false;
    }
    file.close();
    queue_delete(result_queue);
    if (!is_solve) {
        std::cout << "Invalid lab_3 test1 execution\n";
        return 1;
    }
    return 0;
}
