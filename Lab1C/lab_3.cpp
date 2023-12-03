#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "queue.h"

using namespace std;

int main()
{
    Queue* tmp_var = queue_create();
    Queue* result = queue_create();

    vector <string> input_data;
    string input_temp;

    while (cin >> input_temp)
        input_data.push_back(input_temp);

    sort(input_data.begin(), input_data.end());

    for (auto element : input_data)
    {
        if (queue_empty(tmp_var))
            queue_insert(tmp_var, element[0]);
        else if (queue_get(tmp_var) == element[0])
        {
            queue_remove(tmp_var);

            queue_insert(tmp_var, element[element.size() - 1]);

            queue_insert(result, element[element.size() - 1]);
        }
    }

    while (!queue_empty(result))
    {
        cout << (char)queue_get(result) << endl;
        queue_remove(result);
    }
}