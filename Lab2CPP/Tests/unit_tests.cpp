#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "task.h"
#include "stack.h"

int main() {
    int passed = 0, failed = 0;
    Stack *stackRes1 = stack_create();
    std::string expr = "1 - 3 - 4";
    stack_push(stackRes1, MINUS);
    stack_push(stackRes1, 4);
    stack_push(stackRes1, MINUS);
    stack_push(stackRes1, 3);
    stack_push(stackRes1, 1);

    Stack *stack1 = stack_create();
    convertToRPN(expr, stack1);

    bool is_ok = true;
    while (!stack_empty(stack1) && !stack_empty(stackRes1)) {
        if (stack_get(stack1) != stack_get(stackRes1)) {
            is_ok = false;
            break;
        }
        stack_pop(stack1);
        stack_pop(stackRes1);
    }

    if (!stack_empty(stack1) || !stack_empty(stackRes1)) {
        is_ok = false;
    }

    stack_delete(stackRes1);
    stack_delete(stack1);

    if (is_ok) {
        std::cout << "Test 1 convertToRPN passed" << '\n';
        passed++;
    } else {
        std::cout << "Test 1 convertToRPN failed" << '\n';
        failed++;
    }

    Stack *stackRes2 = stack_create();
    std::string expr2 = "(2 + 5) * 4";
    stack_push(stackRes2, MUL);
    stack_push(stackRes2, 4);
    stack_push(stackRes2, PLUS);
    stack_push(stackRes2, 5);
    stack_push(stackRes2, 2);

    Stack *stack2 = stack_create();
    convertToRPN(expr2, stack2);

    bool is_ok2 = true;
    while (!stack_empty(stack2) && !stack_empty(stackRes2)) {
        if (stack_get(stack2) != stack_get(stackRes2)) {
            is_ok2 = false;
            break;
        }
        stack_pop(stack2);
        stack_pop(stackRes2);
    }

    if (!stack_empty(stack2) || !stack_empty(stackRes2)) {
        is_ok2 = false;
    }

    stack_delete(stackRes2);
    stack_delete(stack2);

    if (is_ok2) {
        std::cout << "Test 2 convertToRPN passed" << '\n';
        passed++;
    } else {
        std::cout << "Test 2 convertToRPN failed" << '\n';
        failed++;
    }

    std::ofstream output1("output1.txt");
    Stack *stack3 = stack_create();
    stack_push(stack3, MINUS);
    stack_push(stack3, 4);
    stack_push(stack3, MINUS);
    stack_push(stack3, 3);
    stack_push(stack3, 1);

    std::vector<std::string> result1 = {
        "PUSH 1",
        "PUSH 3",
        "POP A",
        "POP B",
        "SUB B, A",
        "PUSH B",
        "PUSH 4",
        "POP A",
        "POP B",
        "SUB B, A",
        "PUSH B"
    };

    if (output1.is_open()) {
        generateAssembler(stack3, output1);
        output1.close();
    }

    std::ifstream output_read1("output1.txt");

    bool is_ok3 = true;
    size_t i = 0;
    std::string line;
    while (std::getline(output_read1, line)){
        if (i >= result1.size() || line != result1[i]) {
            is_ok3 = false;
            break;
        }
        i++;
    }
    if (i != result1.size()) {
        is_ok3 = false;
    }

    output_read1.close();
    stack_delete(stack3);

    if (is_ok3) {
        std::cout << "Test 1 generateAssembler passed" << '\n';
        passed++;
    } else {
        std::cout << "Test 1 generateAssembler failed" << '\n';
        failed++;
    }

    std::ofstream output2("output2.txt");
    Stack *stack4 = stack_create();
    stack_push(stack4, MUL);
    stack_push(stack4, 4);
    stack_push(stack4, PLUS);
    stack_push(stack4, 5);
    stack_push(stack4, 2);

    std::vector<std::string> result2 = {
        "PUSH 2",
        "PUSH 5",
        "POP A",
        "POP B",
        "ADD A, B",
        "PUSH A",
        "PUSH 4",
        "POP A",
        "POP B",
        "MUL A, B",
        "PUSH A"
    };

    if (output2.is_open()) {
        generateAssembler(stack4, output2);
        output2.close();
    }

    std::ifstream output_read2("output2.txt");

    bool is_ok4 = true;
    i = 0;
    line = "";
    while (std::getline(output_read2, line)){
        if (i >= result2.size() || line != result2[i]) {
            is_ok4 = false;
            break;
        }
        i++;
    }
    if (i != result2.size()) {
        is_ok4 = false;
    }

    output_read2.close();
    stack_delete(stack4);

    if (is_ok4) {
        std::cout << "Test 2 generateAssembler passed" << '\n';
        passed++;
    } else {
        std::cout << "Test 2 generateAssembler failed" << '\n';
        failed++;
    }

    std::cout << "Тестов пройдено: " << passed << "\n";
    std::cout << "Тестов не пройдено: " << failed << "\n";

    return failed != 0;
}