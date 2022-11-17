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
   auto queue = new Queue<int>;
   vector<int>b(n, 1e6);
   s--;
   f--;
   queue->insert(s);
   b[s] = 0;
   while (! queue->empty())
   {
       int v =  queue->get();
       queue->remove();
       for (int i = 0; i < a[v].size(); i++)
       {
           int next = a[v][i];
           if (b[next] > b[v] + 1)
           {
               b[next] = b[v] + 1;
                queue->insert(next);
           }
       }
   }
   if (b[f] < COUNT) cout << b[f];
   else cout <<"IMPOSSIBLE";
    queue->remove();
   return 0;
}
