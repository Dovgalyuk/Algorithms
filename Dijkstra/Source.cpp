#include <iostream>
#include "graph.hpp"
#include <utility>

using namespace std;

int main()
{
	size_t n;
	cout << "Enter count of vertex:";
	cin >> n;
	Graph<pair<int, size_t>> data(n);
	data.vertex(0) = make_pair(1, 0);
	for (size_t i = 1; i < n; i++)
		data.vertex(i) = make_pair(1, 1e9);
	cout << "Enter matrix:" << endl;
	for (size_t i=0; i< n; i++)
		for (size_t j = 0; j < n; j++)
		{
			int temp;
			cin >> temp;
			if (temp)
				data.add_edge(i, j);
		}
	int i = 0;
	cout << *(data.vertex_n(i));
	/*while (i != -1)
	{
		auto start = data.vertex_n(i);
		auto it = start;
		if (*it != -1)
			do {
				if (data.vertex[*it].second > data.vertex[i].second + 1)
				{
					data.vertex[*it].second = data.vertex[i].second + 1;
					data.vertex[*it].first = 0;
				}
				++it;
			} while (it != start);
		data.vertex[*start].first = -1;
		size_t min = -1;
		for (size_t i=0; i<n; i++)
			if (data.vertex[i].first != -1 && (min == -1 || data.vertex[i].second < data.vertex[min].second))
				min = i;
		i = min;
	}
	*/
}