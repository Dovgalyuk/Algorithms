#include <iostream>
#include <fstream>
#include "queue.h"

using namespace std;

int main()
{
    Queue *queue = queue_create();
    
    string cmd;
    int value = 0, size = 0, maxim = 0;
    ifstream input;
    
    input.open("input.txt", ios::in);

    //inserting commands
    do{
        input >> cmd;
        if (input.eof()) break;
    
        if(cmd == "add"){
            input >> value;
            queue_insert(queue, value);
            size++;
            
            if (size > maxim)
                maxim = size;
            
        }else
            if (cmd == "get") {
                if (!queue_empty(queue)) //checks for emptiness
                {
                    cout << "Value: " << queue_get(queue) << endl;
                    queue_remove(queue);
                    size--;
                }
            }
    }while(!input.eof());

    cout << "Size: " << maxim << endl;
    input.close();
    queue_delete(queue);
    return 0;
}
