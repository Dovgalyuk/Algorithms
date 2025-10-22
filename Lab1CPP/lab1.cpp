#include <iostream>
#include <fstream>
#include <string>
#include "../LibraryCPP/array.h"

using namespace std;

Array *array_create_and_read(istream &input)
{
    int n;
    input >> n;
    /* Create array */
    Array *arr = array_create(n);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{
    if (arr == nullptr || array_size(arr) == 0) return;

    int count = 0;
    for (size_t i = 0; i < array_size(arr) - 1; i++){
        if(array_get(arr, i) * array_get(arr, i + 1) < 0){
            count++;
        }
    }
    cout << "change of sign: " << count << " ";
}

void task2(Array *arr)
{
    cout << "unique values: ";
    if (arr == nullptr || array_size(arr) == 0) return;
    
    for (size_t i = 0; i < array_size(arr); i++){
        int count = 0;
        for (size_t j = 0; j < array_size(arr); j++){
            if (array_get(arr, i) == array_get(arr, j)) {
                count++;
            }
        }  
        if (count == 1) {
            cout << array_get(arr, i) << " ";
        }
    }
    cout << endl;
}


int main(int argc, char **argv){
    if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <input_file>" << endl;
    return 1;
    }
    ifstream FILE(argv[1]);
    if (!FILE.is_open()){
        return -1;
    }
    Array *arr = array_create_and_read(FILE);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(FILE);
    task2(arr);
    array_delete(arr);


    FILE.close();
    cout << "\n";
}