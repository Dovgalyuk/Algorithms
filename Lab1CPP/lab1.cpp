#include <iostream>
#include "array.h"

using namespace std;

Data z1(Array*& array, std::ifstream &vh) {
	
	Data res = 0.0;

	array = array_rand(vh);
	Data obschsoprot = 0.0;
	for (size_t i = 0; i < array_size(array); i++) {
		obschsoprot += 1.0 / array_get(array, i);
	}
	res = 1.0 / obschsoprot;
	return res;
}

void sdvig(Array*& arr, std::ifstream& vh) {
    arr = array_rand(vh);

    bool dir;
    size_t colsh;
    vh >> dir >> colsh;
    if (dir) {
        for (size_t i = 0; i < colsh; i++) {
            for (size_t j = array_size(arr)-1; j > 0; j--) {
                array_set(arr, j, array_get(arr,j-1));
            }
            array_set(arr, i, 0);
            for(size_t f = 0;f<array_size(arr);f++){
                cout << array_get(arr,f)  <<  " ";
            }
            cout << endl;
        }
    }
    else {
        for (size_t i = 0; i < colsh; i++) {
            for (size_t j = 0; j < array_size(arr) - 1; j++) {
                array_set(arr, j, array_get(arr, j + 1));
            }
            array_set(arr, array_size(arr) - 1, 0);
            for(size_t f = 0;f<array_size(arr);f++){
                cout << array_get(arr,f)  << " ";
            }
            cout << endl;
        }
    }
}


int main() {

	ifstream v("input.txt");
    Array* arr = NULL;
    Array* arr1 = NULL;
    if (v.is_open()) {
        z1(arr, v);
        array_delete(arr);
        sdvig(arr1, v);
        array_delete(arr1);
        cin.get();
        v.close();
    }
}