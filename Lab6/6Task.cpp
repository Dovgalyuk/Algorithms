#include <iostream>
#include <chrono>
#include <vector>
#include <queue>
#include <string>
#include "BinaryHeap.h"
using namespace std;

typedef milli Ratio;

void Comparison(int length)
{
	auto* BinH = new Heap <pair<int, int>>;
	const int INF = 1000000000;
	int n = length;
	vector < vector < pair<int, int> > > g(n);
	for (int i = 1; i < length; i++)           // наполняем 
	{
		int j = i-1 , w = j+6/2;
		g[i].push_back(make_pair(j, w));
		g[j].push_back(make_pair(i, w));
	}
	int s = 1;                               
	vector<int> d(n, INF), p(n);
	d[s] = 0;

	auto start = chrono::system_clock::now();
	priority_queue < pair<int, int> > q;
	q.push(make_pair(0, s));
	while (!q.empty()) {
		int v = q.top().second, cur_d = -q.top().first;
		q.pop();
		if (cur_d > d[v])  continue;

		for (size_t j = 0; j < g[v].size(); ++j) 
		{
			int to = g[v][j].first,
				len = g[v][j].second;
			if (d[v] + len < d[to]) 
			{
				d[to] = d[v] + len;
				p[to] = v;
				q.push(make_pair(-d[to], to));
			}
		}
	}
	auto end = chrono::system_clock::now();
	chrono::duration<double, Ratio> Queue = end - start;




	int N = length;
	vector < vector < pair<int, int> > > G(N);
	for (int I = 1; I < length; I++)          // наполняем 
	{
		int J = I - 1, W = J + 6 / 2;
		G[I].push_back(make_pair(J, W));
		G[J].push_back(make_pair(I, W));
	}
	int S = 1;
	vector<int> D(N, INF), P(N);
	D[S] = 0;

	start = chrono::system_clock::now();
	BinH->Insert(make_pair(0, S));

	while (!BinH->Empty()) 
	{
		int V = BinH->GetMax().second, Cur_d = -BinH->GetMax().first;
		BinH->RemoveMax();
		if (Cur_d > D[V])  continue;

		for (size_t j = 0; j < G[V].size(); ++j) 
		{
			int To = G[V][j].first,
				Len = G[V][j].second;
			if (D[V] + Len < D[To]) 
			{
				D[To] = D[V] + Len;
				P[To] = V;
				BinH->Insert(make_pair(-D[To], To));
			}
		}
	}
	 end = chrono::system_clock::now();
	chrono::duration<double, Ratio> Heap = end - start;

	string StrQueue = to_string(Queue.count());             // Привожу к строчному типу
	StrQueue.replace(StrQueue.find('.'), 1, 1, ',');       // Заменяю '.' на ',' чтобы удобно было в Excel вставлять
	string StrHeap = to_string(Heap.count());
	StrHeap.replace(StrHeap.find('.'), 1, 1, ',');
	delete BinH;
	cout << "\t" << length << "   | " << StrHeap << "\t\t| " << StrQueue << "\n";
}


int main()
{
	const int MIN = 50000;
	const int MAX = 1000000;

	cout << "\tLength   | Binary Heap		| Priority Queue\n";
	cout << "\t         |            		| \n";
	for (int i = MIN; i <= MAX; i += MIN)
	{
		Comparison(i);
	}

}
