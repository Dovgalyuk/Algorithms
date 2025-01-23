#include <iostream>
#include <fstream>
#include <vector>
#include "queue.h"
using namespace std;

void lab_3(int a, int b, vector<int>& arr, ifstream& file){
    Queue * queue1 = queue_create();
    Queue * queue2 = queue_create();
    Queue * queue3 = queue_create();
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
        arr.push_back(queue_get(queue1));
        queue_remove(queue1);
    }
    while (!queue_empty(queue2)) {
        arr.push_back(queue_get(queue2));
        queue_remove(queue2);
    }
    while (!queue_empty(queue3)) {
        arr.push_back(queue_get(queue3));
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

    int a,b;
    if (!(file >> a >> b)) {
        std::cout << "Error reading from file\n";
        file.close();
        return 1;
    }
    vector<int> arr;
    int temp;
    
    lab_3(a, b, arr, file);
    
    bool is_solve = true;
    size_t i = 0;
    while (file >> temp){
        if (i >= arr.size())
            {
                is_solve = false;
                break;
            }
        if(arr[i] != temp)
            {
                is_solve = false;
                break;
            }
            i++;
    }
    if (i != arr.size() && is_solve)
    {
        is_solve = false;
    }
    file.close();
    if (!is_solve)
    {
        std::cout << "Invalid lab_3 test1 execution\n";
        return 1;
    }
    return 0;
}
