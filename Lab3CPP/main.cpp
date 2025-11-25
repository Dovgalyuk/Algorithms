#include <iostream>
#include <vector>
#include "queue.h"
using namespace std;

const int BITS = 2;
const int BASE = 1 << BITS;

int main()
{
    vector<int> a;
    int x;

    while (cin >> x)
    {
        if (x > 0)
            a.push_back(x);
    }

    if (a.empty())
        return 0;

    int maxValue = a[0];
    for (size_t i = 1; i < a.size(); i++)
        if (a[i] > maxValue)
            maxValue = a[i];

    int passes = 0;
    int tmp = maxValue;
    while (tmp > 0)
    {
        passes++;
        tmp >>= BITS;
    }

    Queue* buckets[BASE];
    for (int i = 0; i < BASE; i++)
        buckets[i] = queue_create();

    for (int pass = 0; pass < passes; pass++)
    {
        int shift = pass * BITS;

        for (size_t i = 0; i < a.size(); i++)
        {
            int key = (a[i] >> shift) & (BASE - 1);
            queue_insert(buckets[key], a[i]);
        }

        size_t idx = 0;
        for (int b = 0; b < BASE; b++)
        {
            while (!queue_empty(buckets[b]))
            {
                a[idx++] = queue_get(buckets[b]);
                queue_remove(buckets[b]);
            }
        }
    }

    for (int i = 0; i < BASE; i++)
        queue_delete(buckets[i]);

    for (size_t i = 0; i < a.size(); i++)
    {
        if (i != 0)
            cout << ' ';
        cout << a[i];
    }
    cout << '\n';
}
