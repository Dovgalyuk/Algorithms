﻿#include <iostream>
#include <chrono>
#include <vector>
#include <queue>
#include <string>
#include "BinaryHeap.h"
using namespace std;

typedef milli Ratio;

void Comparison(int length)
{
	auto* BinH = new Heap;

	int n = length;
	vector < vector < pair<int, int> > > g(n);
	int s = 1;                               
	vector<int> d(n, length), p(n);
	d[s] = 0;

	auto start = chrono::system_clock::now();
	priority_queue < pair<int, int> > q;
	q.push(make_pair(0, s));
	while (!q.empty()) {
		int v = q.top().second, cur_d = q.top().first;
		q.pop();
		if (cur_d > d[v])  continue;

		for (size_t j = 0; j < g[v].size(); ++j) {
			int to = g[v][j].first,
				len = g[v][j].second;
			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				p[to] = v;
				q.push(make_pair(-d[to], to));
			}
		}
	}
	auto end = chrono::system_clock::now();
	chrono::duration<double, Ratio> Queue = end - start;

	start = chrono::system_clock::now();
	BinH->Insert(0);
	BinH->Insert(s);


	while (!BinH->Empty()) 
	{
		int cur_d = BinH->GetMax();
		BinH->RemoveMax();
		int v = BinH->GetMax();
		BinH->Insert(cur_d);
		BinH->RemoveMax();
		if (cur_d > d[v])  continue;

		for (size_t j = 0; j < g[v].size(); ++j) {
			int to = g[v][j].first,
				len = g[v][j].second;
			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				p[to] = v;
				BinH->Insert(-d[to]);
				BinH->Insert(to);
			}
		}
	}
	 end = chrono::system_clock::now();
	chrono::duration<double, Ratio> Heap = end - start;

	string StrQueue = to_string(Queue.count());             // Привожу к строчному типу
	StrQueue.replace(StrQueue.find('.'), 1, 1, ',');       // Заменяю '.' на ',' чтобы удобно было в Excel вставлять
	string StrHeap = to_string(Heap.count());
	StrHeap.replace(StrHeap.find('.'), 1, 1, ',');

	cout << "\t" << length << "   | " << StrHeap << "\t\t| " << StrQueue << "\n";
	delete BinH;
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


