#include <iostream>
#include <fstream>

#include "queue.h"
using namespace std;

void lab_3(int a, int b, int *arr){
    Queue * queue1 = queue_create();
    Queue * queue2 = queue_create();
    Queue * queue3 = queue_create();
    for (int i = 0; i < 9; i++){
        if (arr[i] < a){
            queue_insert(queue1, arr[i]);
        }
        else if(arr[i] <= b){
            queue_insert(queue2, arr[i]);
        }
        else{
            queue_insert(queue3, arr[i]);
        }
    }
    int k = 0;
    while (!queue_empty(queue1)){
        arr[k] = queue_get(queue1);
        k++;
        queue_remove(queue1);
    }
    while (!queue_empty(queue2)){
        arr[k] = queue_get(queue2);
        k++;
        queue_remove(queue2);
    }
    while (!queue_empty(queue3)){
        arr[k] = queue_get(queue3);
        k++;
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
    int arr[9];
    if (!(file >> a >> b)) {
        std::cout << "Error reading from file\n";
        file.close();
        return 1;
    }
    for(int i = 0; i < 9; i++){
        if (!(file >> arr[i])) {
            std::cout << "Error reading from file\n";
            file.close();
            return 1;
        }
    }
    int ans_arr[9];
    for(int i = 0; i < 9; i++){
        if (!(file >> ans_arr[i])) {
            std::cout << "Error reading from file\n";
            file.close();
            return 1;
        }
    }
    file.close();
    lab_3(a, b, arr);
    bool is_solve = true;
    for(int i = 0; i < 9; i++){
        if (arr[i] != ans_arr[i]) {
            is_solve = false;
            break;
        }
    }
    if (!is_solve)
    {
        std::cout << "Invalid lab_2 test1 execution\n";
        return 1;
    }
    return 0;
}
