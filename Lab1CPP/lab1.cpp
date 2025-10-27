#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits>

void findFastestCars(std::istream& in) {
    int n;
    in >> n;

    if (n <= 0) {
        std::cout << "Task4: no data" << std::endl;
        return;
    }

    std::vector<int> speeds(n);
    int maxSpeed = std::numeric_limits<int>::min();

    for (int i = 0; i < n; ++i) {
        in >> speeds[i];
        if (speeds[i] > maxSpeed) {
            maxSpeed = speeds[i];
        }
    }

    int firstIndex = -1;
    int lastIndex = -1;

    for (int i = 0; i < n; ++i) {
        if (speeds[i] == maxSpeed) {
            if (firstIndex == -1) { 
                firstIndex = i;
            }
            lastIndex = i; 
        }
    }

    if (firstIndex == lastIndex) {
        std::cout << "Task4: " << firstIndex + 1 << std::endl;
    } else {
        std::cout << "Task4: " << firstIndex + 1 << " " << lastIndex + 1 << std::endl;
    }
}

void findNonDivisibleElements(std::istream& in) {
    int m;
    in >> m;

    if (m <= 0) {
        std::cout << "Task5: no data" << std::endl;
        return;
    }

    std::vector<int> arr(m);
    for (int i = 0; i < m; ++i) {
        in >> arr[i];
    }

    std::cout << "Task5:";
    
    for (int i = 0; i < m; ++i) {
        bool isDivisible = false;
        
        for (int j = 0; j < m; ++j) {
            if (i == j) {
                continue;
            }
            
            if (arr[j] != 0 && arr[i] % arr[j] == 0) {
                isDivisible = true;
                break;
            }
        }

        if (!isDivisible) {
            std::cout << " " << arr[i];
        }
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    std::ifstream infile(argv[1]);
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    findFastestCars(infile);
    findNonDivisibleElements(infile);

    infile.close();
    return 0;
}