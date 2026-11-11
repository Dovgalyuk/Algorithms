#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool test_task(const std::string& program_path) {
    int passed = 0, failed = 0;

    std::string command1 = program_path + " < input.txt";
    int code1 = std::system(command1.c_str());

    if (code1 != 0) {
        std::cout << "Test 1 failed to run" << '\n';
        failed++;
    } else {
        std::vector<std::string> expected1 = {
            "PUSH 1", "PUSH 2", "PUSH 3",
            "POP A", "POP B", "MUL A, B", "PUSH A",
            "POP A", "POP B", "ADD A, B", "PUSH A"
        };

        std::ifstream output("output.txt");
        std::string line;
        size_t i = 0;
        bool is_ok = true;

        while (std::getline(output, line)) {
            if (i >= expected1.size() || line != expected1[i]) {
                is_ok = false;
                break;
            }
            i++;
        }

        if (is_ok && i == expected1.size()) {
            std::cout << "Test 1 passed" << '\n';
            passed++;
        } else {
            std::cout << "Test 1 failed" << '\n';
            failed++;
        }
    }

    std::string command2 = program_path + " < input2.txt";
    int code2 = std::system(command2.c_str());

    if (code2 != 0) {
        std::cout << "Test 2 failed to run" << '\n';
        failed++;
    } else {
        std::vector<std::string> expected2 = {
            "PUSH 4", "PUSH 3",
            "POP A", "POP B", "ADD A, B", "PUSH A",
            "PUSH 2",
            "POP A", "POP B", "MUL A, B", "PUSH A"
        };

        std::ifstream output2("output.txt");
        std::string line;
        size_t i = 0;
        bool is_ok = true;

        while (std::getline(output2, line)) {
            if (i >= expected2.size() || line != expected2[i]) {
                is_ok = false;
                break;
            }
            i++;
        }

        if (is_ok && i == expected2.size()) {
            std::cout << "Test 2 passed" << '\n';
            passed++;
        } else {
            std::cout << "Test 2 failed" << '\n';
            failed++;
        }
    }

    std::string command3 = program_path + " < input3.txt";
    int code3 = std::system(command3.c_str());

    if (code3 != 0) {
        std::cout << "Test 3 failed to run" << '\n';
        failed++;
    } else {
        std::vector<std::string> expected3 = {
            "PUSH 3", "PUSH 2",
            "POP A", "POP B", "MUL A, B", "PUSH A",
            "PUSH 1",
            "POP A", "POP B", "SUB B, A", "PUSH B"
        };

        std::ifstream output3("output.txt");
        std::string line;
        size_t i = 0;
        bool is_ok = true;

        while (std::getline(output3, line)) {
            if (i >= expected3.size() || line != expected3[i]) {
                is_ok = false;
                break;
            }
            i++;
        }

        if (is_ok && i == expected3.size()) {
            std::cout << "Test 3 passed" << '\n';
            passed++;
        } else {
            std::cout << "Test 3 failed" << '\n';
            failed++;
        }
    }


    std::cout << "Test passed: " << passed << '\n';
    std::cout << "Test failed: " << failed << '\n';

    return failed == 0;
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Missing required arguments" << '\n';
    }

    bool task_ok = test_task(argv[1]);

    if (task_ok) {
        return 0;
    }

    return 1;
}