#include <iostream>
#include <string>
#include <cstdlib>
//#include <stack>
#include "stack.h"

using namespace std;

template <typename Data>
void task1(Stack<Data> particleStack);

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
void task1(Stack<Data> particleStack)  
{
    int N;
    cin >> N;

    MyStackResult resultStack;
    Particle particle;
    ParticleResult result;
    

    for (int i = 0; i < N; i++) {
        
        cin >> particle.position >> particle.charge;
        particleStack.push(particle);
    }
    for (int i = 0; i < N; i++) {
        particle = particleStack.get();
        particleStack.pop();
        if (!particleStack.empty() && particle.charge == '-' && particleStack.get().charge == '+') {
            result.first = particleStack.get().position; 
            result.second = particle.position;
            resultStack.push(result);
        }
    }
    while(!resultStack.empty()) {
        result = resultStack.get();
        cout << result.first << " " << result.second << endl;
        resultStack.pop();
    }
}