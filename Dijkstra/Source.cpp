#include <iostream>
#include "graph.hpp"
#include <utility>

using namespace std;

int main()
{
	size_t n;
	int i;
	cout << "Enter count of vertex:";
	cin >> n;
	cout << "Enter start vertex:";
	cin >> i;
	Graph<pair<int, size_t>, size_t> data(n);
	cout << "Enter matrix:" << endl;
	for (size_t i=0; i< n; i++)
		for (size_t j = 0; j < n; j++)
		{
			cin >> data.edge(i, j);
			if (data.edge(i, j) != -1)
				data.add_edge(i, j);
		}
	data.vertex(0) = make_pair(1, 0);
	for (size_t i = 1; i < n; i++)
		data.vertex(i) = make_pair(1, (size_t)1e9);
	//cout << *(data.vertex_n(i));
	while (i != -1)
	{
		auto start = data.vertex_n(i);
		auto it = start;
		if (*it != -1)
			do {
				if (data.vertex(*it).second > data.vertex(i).second + data.edge(i, *it))
				{
					data.vertex(*it).second = data.vertex(i).second + data.edge(i, *it);
					data.vertex(*it).first = 0;
				}
				++it;
			} while (it != start);
		data.vertex(*start).first = -1;
		size_t min = -1;
		for (size_t j=0; j<n; j++)
			if (data.vertex(j).first == 0 && (min == -1 || data.vertex(j).second < data.vertex(min).second))
				min = j;
		i = min;
	}
	cout << "Distances to vertexs:" << endl;
	for (size_t j = 0; j < n; j++)
		cout << data.vertex(j).second << " ";
}