#include <iostream>
#include <string>
#include <cstdlib>
//#include <stack>
#include "stack.h"

using namespace std;

template <typename Data>
void task1(Stack<Data>& particleStack);

struct Particle {
    int position;
    char charge;
};

struct ParticleResult {
    int first;
    int second;
};

typedef Stack<ParticleResult> MyStackResult;

int main()
{
    Stack<Particle> stack;
    /* Create array here */
    task1(stack);
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
        particle = particleStack.get();
        particleStack.pop();

        if (!tempStack.empty() && particle.charge != tempStack.get().charge) {
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