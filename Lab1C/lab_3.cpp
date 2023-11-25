#include <iostream>
#include <string>

#include "queue.h"

using namespace std;

int main()
{
    Queue* tmp_var = queue_create();
    Queue* result = queue_create();

    string input_temp;

    while (cin >> input_temp)
    {
        if (queue_empty(tmp_var))
            queue_insert(tmp_var, input_temp[0]);
        else if (queue_get(tmp_var) == input_temp[0])
        {
            queue_remove(tmp_var);

            queue_insert(tmp_var, input_temp[input_temp.size() - 1]);

            queue_insert(result, input_temp[input_temp.size() - 1]);
        }
    }

    while (!queue_empty(result))
    {
        cout << (char)queue_get(result) << endl;
        queue_remove(result);
    }
}