#include <iostream>
#include <vector>
#include "queue.h"


using namespace std;

int main()
{

    const int COUNT = 1000000;
    int n, s, f,t;
    cin >> n >> s >> f; 
    vector<vector<int>>a(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> t;
            if (t == 1) 
                a[i].push_back(j);
        }
    Queue* q = queue_create();
    vector<int>b(n, 1e6);
    s--;
    f--;
    queue_insert(q, s);
    b[s] = 0;
    while (!queue_empty(q))
    {
        int v = queue_get(q);
        queue_remove(q);
        for (int i = 0; i < a[v].size(); i++)
        {
            int next = a[v][i];
            if (b[next] > b[v] + 1)
            {
                b[next] = b[v] + 1;
                queue_insert(q, next);
            }
        }
    }
    if (b[f] < COUNT) cout << b[f];
    else cout <<"IMPOSSIBLE";
    queue_delete(q);
    return 0;
}
