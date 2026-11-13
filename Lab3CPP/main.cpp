#include <iostream>
#include <fstream>
#include "queue.h"

using namespace std;

void task(ifstream &fin, ofstream &fout)
{
    int n;
    fin >> n;

    int *matrix = new int[n * n];
    for (int i = 0; i < n * n; ++i)
    {
        fin >> matrix[i];
    }

    int *component = new int[n];
    for (int i = 0; i < n; ++i)
    {
        component[i] = 0;
    }

    int count = 0;
    Queue *queue = queue_create();
    for (int i = 0; i < n; ++i)
    {
        if (component[i] != 0)
        {
            continue;
        }

        ++count;
        component[i] = count;
        queue_insert(queue, i);
        while (!queue_empty(queue))
        {
            int v = queue_get(queue);
            queue_remove(queue);
            for (int j = 0; j < n; ++j)
            {
                if (matrix[v * n + j] == 1 && component[j] == 0)
                {
                    component[j] = count;
                    queue_insert(queue, j);
                }
            }
        }
    }

    fout << count << endl;
    for (int i = 1; i <= count; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (component[j] == i)
            {
                fout << j + 1 << " ";
            }
        }
        fout << endl;
    }

    queue_delete(queue);
    delete[] component;
    delete[] matrix;
}

int main(int argc, char **argv)
{
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    task(fin, fout);

    return 0;
}
