#include <iostream>
#include <fstream>
#include <string>

bool test_task1(const std::string& program_path) {
    int passed = 0, failed = 0;

    {
        std::ofstream input("input.txt");
        input << "5" << '\n';
        input << "10 10 10 10 10" << '\n';
    }

    int code = std::system(program_path.c_str());

    if (code != 0) {
        std::cout << "Test 1 task1 failed to run" << '\n';
        failed++;
    } else {
        std::ifstream output("output.txt");

        std::string result;
        std::getline(output, result);

        if (result == "2") {
            std::cout << "Test 1 task1 passed" << '\n';
            passed++;
        } else {
            std::cout << "Test 1 task1 failed" << '\n';
            failed++;
        }
    }

    {
        std::ofstream input("input.txt");
        input << "2" << '\n';
        input << "6 6" << '\n';
    }

    code = std::system(program_path.c_str());

    if (code != 0) {
        std::cout << "Test 2 task1 failed to run" << '\n';
        failed++;
    } else {
        std::ifstream output("output.txt");

        std::string result;
        std::getline(output, result);

        if (result == "3") {
            std::cout << "Test 2 task1 passed" << '\n';
            passed++;
        } else {
            std::cout << "Test 2 task1 failed" << '\n';
            failed++;
        }
    }

    std::cout << "Test passed: " << passed << '\n';
    std::cout << "Test failed: " << failed << '\n';

    return failed == 0;
}

bool test_task2(const std::string& program_path) {
    int passed = 0, failed = 0;

    {
        std::ofstream input("input.txt");
        input << "7" << '\n';
        input << "1 2 3 4 5 6 7" << '\n';
    }

    int code = std::system(program_path.c_str());

    if (code != 0) {
        std::cout << "Test 1 task2 failed to run" << '\n';
        failed++;
    } else {
        std::ifstream output("output.txt");

        std::string result;
        std::getline(output, result);

        if (result == "3 4 5 6 7") {
            std::cout << "Test 1 task2 passed" << '\n';
            passed++;
        } else {
            std::cout << "Test 1 task2 failed" << '\n';
            failed++;
        }
    }

    {
        std::ofstream input("input.txt");
        input << "7" << '\n';
        input << "7 6 5 4 3 2 1" << '\n';
    }

    code = std::system(program_path.c_str());

    if (code != 0) {
        std::cout << "Test 2 task2 failed to run" << '\n';
        failed++;
    } else {
        std::ifstream output("output.txt");

        std::string result;
        std::getline(output, result);

        if (result == "7 6 5 4 3") {
            std::cout << "Test 2 task2 passed" << '\n';
            passed++;
        } else {
            std::cout << "Test 2 task2 failed" << '\n';
            failed++;
        }
    }

    std::cout << "Test passed: " << passed << '\n';
    std::cout << "Test failed: " << failed << '\n';

    return failed == 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Missing required arguments" << '\n';
    }

    bool task1_ok = test_task1(argv[1]);
    bool task2_ok = test_task2(argv[2]);

    if (task1_ok && task2_ok) {
        return 0;
    }

    return 1;
}