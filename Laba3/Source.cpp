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
   Queue* queue = queue_create();
   vector<int>b(n, 1e6);
   s--;
   f--;
   queue_insert(queue, s);
   b[s] = 0;
   while (!queue_empty(queue))
   {
       int v = queue_get(queue);
       queue_remove(queue);
       for (int i = 0; i < a[v].size(); i++)
       {
           int next = a[v][i];
           if (b[next] > b[v] + 1)
           {
               b[next] = b[v] + 1;
               queue_insert(queue, next);
           }
       }
   }
   if (b[f] < 1000000) cout << b[f];
   else cout << "IMPOISBLE";
   queue_delete(queue);
   return 0;
}
