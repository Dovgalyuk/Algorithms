#include "lab3.h"

int main(int argc, char **argv)
{
    if(argc < 2)
        return 1;

    ifstream input(argv[1]);

    vector<char> correct = {'B','C'};
    if(!(task(input, 3) == correct))
    {
        cout << "Wrong answer: Test 1";
        return 1;
    }

    correct = {'C', 'D', 'E', 'F', 'G'};
    if(!(task(input, 5) == correct))
    {
        cout << "Wrong answer: Test 2";
        return 1;
    }

    correct = {};
    if(!(task(input, 3) == correct))
    {
        cout << "Wrong answer: Test 3";
        return 1;
    }

    correct = {'E'};
    if(!(task(input, 2) == correct))
    {
        cout << "Wrong answer: Test 4";
        return 1;
    }

    correct = {'F', 'G', 'A', 'B'};
    if(!(task(input, 7) == correct))
    {
        cout << "Wrong answer: Test 5";
        return 1;
    }

    correct = {'A', 'D', 'B', 'C', 'E', 'G'};
    if(!(task(input, 7) == correct))
    {
        cout << "Wrong answer: Test 6";
        return 1;
    }

    input.close();
    
    return 0;
}
