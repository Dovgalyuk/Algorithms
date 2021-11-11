#include <iostream>
#include <fstream>
#include <queue.h>

using namespace std;

int main()
{   auto* queue = new Queue<string>;
    char sim;
    ifstream myfile("file.txt");
    if (!myfile.is_open())
    {
        while (myfile.get(sim))
        {
            queue->insert(sim);
        }
        myfile.close();
    }
    else cout << "Unable to open file";
    
    return 0;
}
