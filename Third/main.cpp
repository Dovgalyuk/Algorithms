#include <iostream>
#include <fstream>
#include "queue.h"
using namespace std;

int main()
{   auto* queue = new Queue<char>;
    char sim;
    bool contains = false;
    ifstream myfile("V:/COD/VS/Algorithms/Third/file.txt");
    if (myfile.is_open())
    {
        while (myfile.get(sim))
        {
            if (sim == '\n'){
                break;
            }
            queue->insert(sim); 
        }
        while (myfile.get(sim)) {
            if (queue->empty()) {
                contains = false;
            }
            while (!queue->empty()) {
                if (queue->get() == sim) {
                    contains = true;
                    queue->remove();
                    break;
                }
                else {
                    contains = false;
                    queue->remove();
                    }
            }
        }
        myfile.close();
        if (contains) {
            cout << "\nYES" << endl;
        }
        else {
            cout << "\nNO" << endl;
        }            
    }
    else {
        cout << "Unable to open file";
    }
    
    return 0;
}
