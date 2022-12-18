#include <iostream>
#include "queue.h"
#include <fstream>

using namespace std;

int main()
{
    int a, b, size = 0;
    Data c;
    Queue* que = queue_create();
    ifstream fin("input.txt");
    fin >> a >> b;
    while (!fin.eof())
    {
        fin >> c;
        size++;
        queue_insert(que, c);
    }
    fin.close();
    cout << "0 -1 1 5 6 2 1 7 -2" << endl;
    for (int i = 0; i < size; i++)
    {
        if (queue_get(que) < a)
        {
            cout << queue_get(que) << " ";
            queue_remove(que);
            size--;
            i--;
        }
        else
        {
            int p = queue_get(que);
            queue_remove(que);
            queue_insert(que, p);
        }
    }
    //cout << queue_get(que) << " ";
    for (int i = 0; i < size; i++)
    {
        if ((queue_get(que) >= a) && (queue_get(que) <= b))
        {
            cout << queue_get(que) << " ";
            queue_remove(que);
            size--;
            i--;
        }
        else
        {
            queue_insert(que, queue_get(que));
            queue_remove(que);
        }
    }
    for (int i = 0; i < size; i++)
    {
            cout << queue_get(que) << " ";
            queue_remove(que);     
    }
    queue_delete(que);
}
