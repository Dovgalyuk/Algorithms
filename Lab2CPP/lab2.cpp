#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

struct Particle {
    int coord;
    char charge;
};

void solve_particles(const std::string& filename) {
    Stack* plus_stack = stack_create();  // Только один стек для индексов
    std::ifstream infile(filename);

    int N;
    infile >> N;
    Particle* arr = new Particle[N];
    for (int i = 0; i < N; ++i) {
        infile >> arr[i].coord >> arr[i].charge;
    }

    for (int i = 0; i < N; ++i) {
        if (arr[i].charge == '+') {
            stack_push(plus_stack, i);  // Сохраняем только индекс
        }
        else if (arr[i].charge == '-') {
            if (!stack_empty(plus_stack)) {
                int plus_index = stack_get(plus_stack);
                stack_pop(plus_stack);
                std::cout << arr[plus_index].coord << " " << arr[i].coord << std::endl;
            }
        }
    }

    stack_delete(plus_stack);
    delete[] arr;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            solve_particles(argv[i]);
        }
    }
    else {
        std::string filenames[] = { "input.txt", "input2.txt", "input3.txt", "input4.txt", "input5.txt" };
        for (int i = 0; i < 5; i++) {
            solve_particles(filenames[i]);
        }
    }
    return 0;
}
