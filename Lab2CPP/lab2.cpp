#include <iostream>
#include "stack.h"

using namespace std;

struct Particle {
    int position;
    char charge;
};

struct ParticleResult {
    int first;
    int second;
};

template <typename Data>
void task1(Stack<Data>& particleStack);

int main() {
    Stack<Particle> stack;
    task1(stack);
    return 0;
}

template <typename Data>
void task1(Stack<Data>& particleStack) {
    int N;
    cin >> N;

    Stack<ParticleResult> resultStack;
    Particle particle;
    ParticleResult result;

    for (int i = 0; i < N; i++) {
        cin >> particle.position >> particle.charge;
        particleStack.push(particle);
    }

    Stack<Particle> tempStack;

    while (!particleStack.empty()) {
        particle = particleStack.pop();

        if (!tempStack.empty() && (particle.charge == '+' && tempStack.get().charge == '-')) {
            result.first = particle.position;
            result.second = tempStack.get().position;
            resultStack.push(result);
            tempStack.pop();
        } else {
            tempStack.push(particle);
        }
    }

    while (!resultStack.empty()) {
        result = resultStack.pop();
        cout << result.first << " " << result.second << endl;
    }
}