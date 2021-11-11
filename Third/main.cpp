#include <iostream>
#include <fstream>
#include "queue.h"
using namespace std;

bool contains(Queue<char> *queue, string secondStr) {
    int i = 0;
    while (!queue->empty()){
        if (queue->get() == secondStr[i])
            {
                queue->remove();
                
                if (i == secondStr.length() -1) {
                    return true;
                }
                i++;
            }
            else {
                queue->remove();
                i = 0;
            }
    }
    return false;
}

int main()
{   auto* queue = new Queue<char>;
    char sim;
    string secondStr;
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
            secondStr += sim;
        }
        myfile.close();
        cout << secondStr + "\n";
        if (contains(queue, secondStr)) {
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
