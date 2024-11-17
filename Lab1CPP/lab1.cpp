#include "array.h"
#include <fstream>
#include <iostream>
#include <vector>


std::vector<int> readFile(const std::string& filename) {
    std::ifstream input(filename);
    std::vector<int> arr;
    int size;

    if (input >> size) {
        arr.resize(size);
        for (int i = 0; i < size; ++i) {
            input >> arr[i];
        }
    }
    return arr;
}

void task1(const std::string& input)
{
	std::vector<int> heights = readFile(input);
    if (heights.empty()) {
        std::cout << "array empty." << std::endl;
        return;
    }

    double sum = 0;
    for (int heigh : heights) {
        sum += heigh;
    }
    double avg = sum / heights.size();

    int count = 0;
    for (int heigh : heights) {
        if (heigh > avg) {
            count++;
        }
    }

    std::cout << "numb of highest then avg: " << count << std::endl;

}


void task2(const std::string& input) {

	std::vector<int> arr = readFile(input);
    if (arr.empty()) {
        std::cout << "array is empty" << std::endl;
        return;
    }

    std::vector<int> notDivide;

    for (size_t i = 0; i < arr.size(); ++i) {
        bool isDivide = false;
        for (size_t j = 0; j < arr.size(); ++j) {
            if (i != j && arr[i] % arr[j] == 0) {
                isDivide = true;
                break;
            }
        }
        if (!isDivide) {
            notDivide.push_back(arr[i]);
        }
    }

    std::cout << "not devide by others: ";
    for (int elem : notDivide) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

}

int main() {
    const std::string file = "input.txt";

	task1(file);
	task2(file);


	return 0;
}
