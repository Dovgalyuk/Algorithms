#include <iostream> 
#include <fstream>  
#include "array.h" 
using namespace std; 


void fill_array_from_file(Array* arr, const string& filename) {
    ifstream file(filename); 
    if (!file.is_open()) {
        throw runtime_error("Unable to open file: " + filename); 
    }
    for (size_t i = 0; i < array_size(arr); ++i) { 
        int value; 
        file >> value; 
        array_set(arr, i, value); 
    }
    file.close(); 


void process_array_sum_and_product(const Array* arr) {
    Data sum = 0;     
    Data product = 1; 
    for (size_t i = 0; i < array_size(arr); ++i) { 
        Data value = array_get(arr, i); 
        sum += value;      
        product *= value; 
    }
    cout << "Sum: " << sum << "\n";         
    cout << "Product: " << product << "\n"; 
}


void process_array_min_max_sum(const Array* arr) {
    if (array_size(arr) < 2) { 
        cout << "Array too small.\n"; 
        return;
    }

    size_t minIndex = 0, maxIndex = 0; 
    for (size_t i = 1; i < array_size(arr); ++i) { 
        if (array_get(arr, i) < array_get(arr, minIndex)) { 
            minIndex = i; 
        }
        if (array_get(arr, i) > array_get(arr, maxIndex)) { 
            maxIndex = i; 
        }
    }

    if (minIndex > maxIndex) { 
        swap(minIndex, maxIndex); 
    }

    Data sum = 0; 
    for (size_t i = minIndex + 1; i < maxIndex; ++i) { 
        sum += array_get(arr, i); 
    }

    cout << "Sum between min and max: " << sum << "\n"; 
}


int main() {
    try { 
        int size; 
        string filename1 = "input1.txt"; 
        string filename2 = "input2.txt"; 

        
        cout << "Enter size of array for first task: ";
        cin >> size;

        Array* arr1 = array_create(size); 
        fill_array_from_file(arr1, filename1);
        cout << "First task:\n"; 
        process_array_sum_and_product(arr1); 
        array_delete(arr1); 

        // Вторая задача
        cout << "\nEnter size of array for second task: "; 
        cin >> size; 

        Array* arr2 = array_create(size); 
        fill_array_from_file(arr2, filename2);
        cout << "Second task:\n"; 
        process_array_min_max_sum(arr2); 
        array_delete(arr2); 

    }
    catch (const exception& e) { 
        cerr << "Error: " << e.what() << "\n"; 
    }

    return 0; 
}
