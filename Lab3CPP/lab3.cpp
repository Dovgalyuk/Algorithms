#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "queue.h"
using namespace std;

void lab_3(const string& file_path, int a, int b) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Error opening file: " << file_path << endl;
        return; 
    }

    vector<int> arr;
    int num;
    while (file >> num) {
        arr.push_back(num);
    }
    file.close();
    Queue * queue1 = queue_create();
    Queue * queue2 = queue_create();
    Queue * queue3 = queue_create();
    for (int i = 0; i < arr.size(); i++){
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

    int a, b;
    if (!(file >> a >> b)) {
        std::cout << "Error reading a and b from file\n";
        file.close();
        return 1;
    }
    std::vector<int> arr(9);
    for(int i = 0; i < 9; i++){
        if (!(file >> arr[i])) {
            std::cout << "Error reading from file\n";
            file.close();
            return 1;
        }
    }
    std::vector<int> ans_arr(9);
    for(int i = 0; i < 9; i++){
        if (!(file >> ans_arr[i])) {
            std::cout << "Error reading answer array from file\n";
            file.close();
            return 1;
        }
    }

    string filePath = argv[1];
    lab_3(filePath, a, b);
    
    file.seekg(0);

    if (!(file >> a >> b)) {
        std::cout << "Error reading from file\n";
        file.close();
        return 1;
    }
    std::vector<int> arr_check(9);
    for(int i = 0; i < 9; i++){
        if (!(file >> arr_check[i])) {
            std::cout << "Error reading numbers from file\n";
            file.close();
            return 1;
        }
    }
    file.close();

    bool is_solve = true;
    for(int i = 0; i < 9; i++){
        if (arr_check[i] != ans_arr[i]) {
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
