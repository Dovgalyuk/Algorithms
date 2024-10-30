#include <array.h>
#include <iostream>

Data task_1(Array*& array, std::ifstream& input) {

    Data result = 0;

    array = fill_array(input);

    Data min = array_get(array, 0);
    Data max = array_get(array, 0);
    
    for (size_t i = 1; i < array_size(array); i++) {
        Data value = array_get(array, i);
        if (value < min) {
            min = value;
        }
        if (value > max) {
            max = value;
        }
    }

    double avg = (min + max) / 2.0;

    for (size_t i = 0; i < array_size(array); i++) {
        if (array_get(array, i) < avg) {
            result +=1;
        }
    }
    std::cout << result << std::endl;

    return result;
}

void task_2(Array*& array) {

    Data max_sum = 0;
    size_t start_index = 0;

    for (size_t i = 0; i < 5; i++) {
        max_sum += array_get(array, i);
    }

    Data current_sum = max_sum;
    for (size_t i = 5; i < array_size(array); i++) {
        current_sum = current_sum - array_get(array, i - 5) + array_get(array, i);
        if (current_sum > max_sum) {
            max_sum = current_sum;
            start_index = i - 4;
        }
    }

    for (size_t i = start_index; i < start_index + 5; i++) {
        std::cout << "Index: " << i << ", Value: " << array_get(array, i) << std::endl;
    }
}
int main(){

    std::ifstream input("input.txt");
    
	if (input.is_open()) {
		Array* array = NULL;

		if (task_1(array, input) != 30) {
			std::cout << "task_1 error result!" << std::endl;
        }
		array_delete(array);

		task_2(array);
		array_delete(array);
	}

	input.close();

	return 0;
}