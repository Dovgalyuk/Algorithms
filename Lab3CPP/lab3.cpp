#include <iostream>
#include <fstream>
#include "queue.h"

using namespace std;

int main(__attribute__((unused)) int argc, char** argv){
    //initializng x and y queue
    Queue *queue_x = queue_create();
    Queue *queue_y = queue_create();

    //open file
    ifstream input(argv[1]);
    int x_matrix, y_matrix;

    //input size of matrix
    input >> x_matrix >> y_matrix;

    //initializing zero-matrix
    int** arr = new int*[y_matrix];
    for (int i = 0; i < y_matrix; ++i) {
        arr[i] = new int[x_matrix];
    }
    for(int y = 0; y < y_matrix; y++){
        for(int x = 0; x < x_matrix; x++){
            arr[y][x] = 0;
        }
    }

    //input coords of 1-colors and add to queue
    int x1, y1;
    while(!input.eof()){
        input >> x1 >> y1;
        x1--;
        y1--;
        arr[y1][x1] = 1;
        queue_insert(queue_x, x1);
        queue_insert(queue_y, y1);
    }

    //main loop
    while(!queue_empty(queue_x)){
        x1 = queue_get(queue_x);
        queue_remove(queue_x);
        y1 = queue_get(queue_y);
        queue_remove(queue_y);
        for(int y = y1-1; y <= y1+1; y++){
            for(int x = x1-1; x <= x1+1; x++){
                if(x1 == x && y1 == y){
                    continue;
                } else if((x1 + y1) % 2 == (x + y) % 2){
                    continue;       
                } else if(y >= 0 && y < y_matrix && x >= 0 && x < x_matrix && arr[y][x] == 0){
                    arr[y][x] = arr[y1][x1] + 1;
                    queue_insert(queue_x, x);
                    queue_insert(queue_y, y);

                }
            }
        }
    }
    //finding max
    int max = 0;
    for(int y = 0; y < y_matrix; y++){
        for(int x = 0; x < x_matrix; x++){
            if(arr[y][x] > max){
                max = arr[y][x];
            } 
        }                    
    }
    for (int i = 0; i < y_matrix; ++i) {
        delete[] arr[i];
    }
    delete[] arr;

    cout << max;
    return 0;           
}
