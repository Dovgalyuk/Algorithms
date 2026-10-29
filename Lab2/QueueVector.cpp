#include <iostream>
#include <fstream>
#include <vector>
#include "vector.h"
#include "stack.h"

struct Particle {
    int position;
    char charge;
};

int main(int argc, char* argv[]){
    std::ifstream input(argv[1]);

    if (!input){
       return 1;
    }
 

    size_t n;
    input >> n;

    if (n < 2){
        return 1;
    }
    
    std::vector<Particle> particles;
    particles.reserve(n);

    for(size_t i = 0; i < n; i++){
        Particle particle;

        input >> particle.position >> particle.charge;
        

        particles.push_back(particle);

    }

    Stack* stack = stack_create();

    try {
        for (const Particle& particle : particles) {
            if (particle.charge == '+') {
                stack_push(stack, particle.position);
            } else if (!stack_empty(stack)) {
                long long positive_position = stack_get(stack);
                stack_pop(stack);

                std::cout << positive_position << ' '
                          << particle.position << '\n';
            }
        }
    } catch (...) {
        stack_delete(stack);
        throw;
    }


    stack_delete(stack);

    return 0;
}
