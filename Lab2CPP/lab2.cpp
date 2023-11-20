#include <iostream>
#include <string>
#include <cstdlib>
//#include <stack>
#include "stack.h"

using namespace std;

template <typename T>
void task1(Stack<T> *particleStack);

struct Particle {
    int position;
    char charge;
};

struct ParticleResult {
    int first;
    int second;
};

int main()
{
    Stack<Particle> *stack = NULL;
    /* Create array here */
    task1(stack);
    if (stack != NULL) {
        stack_delete(stack);
    }
}

template <typename T>
void task1(Stack<T> *particleStack)  
{
    int N;
    cin >> N;

    particleStack = stack_create<Particle>();
    Stack<ParticleResult> *resultStack = stack_create<ParticleResult>();
    Particle particle;
    ParticleResult result;
    

    for (int i = 0; i < N; i++) {
        
        cin >> particle.position >> particle.charge;
        stack_push(particleStack, particle);
    }
    for (int i = 0; i < N; i++) {
        particle = stack_get(particleStack);
        stack_pop(particleStack);
        if (!stack_empty(particleStack) && particle.charge == '-' && stack_get(particleStack).charge == '+') {
            result.first = stack_get(particleStack).position; 
            result.second = particle.position;
            stack_push(resultStack, result);
        }
    }
    while(!stack_empty(resultStack)) {
        result = stack_get(resultStack);
        cout << result.first << " " << result.second << endl;
        stack_pop(resultStack);
    }
}