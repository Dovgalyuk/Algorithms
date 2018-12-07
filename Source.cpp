#include <iostream>
#include "Graf.h"
using namespace std;

const int MinEl = 9999999;

Iterator* FindMinVertex(Graf* graf, int n)
{
	Iterator* min = create_iterator_begin(graf, 0);
	for (int i = 0; i < n; i++)
	{
		Iterator* it = create_iterator_begin(graf, i);
		Iterator* end = create_iterator_end(graf, i);
		for (; comp(it, end); up(it))
		{
			if (DerCur(it) != 0 && ((DerCur(min) == 0) || (DerCur(it)<DerCur(min))) && DerColorj(it) != DerColori(it))
				assign_it(min, it);
		}
	}
	DerVis(min) = 1;
	return min;
}

void ChangeMark(Graf* graf, Iterator* it, int size)
{
	int find_color = DerColori(it);
	int need_color = DerColorj(it);
	for (int i = 0; i < size; i++)
		if (get_mark_vertex(graf, i) == find_color)
			add_mark_vertex(graf, i, need_color);
}

void Cout_Res(Graf* graf, int n)
{
	for (int i = 0; i < n; i++)
	{
		Iterator* it = create_iterator_begin(graf, i);
		Iterator* end = create_iterator_end(graf, i);
		for (; comp(it, end); up(it))
		{
			if (DerVis(it))
				cout << DerCur(it) << " ";
			else
				cout << "0 ";
		}
		cout << endl;
	}
}

int main()
{
	int n, v_tree=0;
	cin >> n;
	Graf* graf = graf_create(n);
	int x,y,v;
	for (int i = 0; i < n; i++)
	{
		add_mark_vertex(graf, i, i);
	}
	while (cin >> x)
	{
		cin >> y >> v;
		add_mark_edge(graf, x, y, v);
		add_mark_edge(graf, y, x, v);
	}
	int ch = n - 1;
	while(ch!=0)
	{
		Iterator* min = FindMinVertex(graf, n);
		v_tree += DerCur(min);
		ChangeMark(graf, min, n);
		ch--;
	}
	cout << endl;
	Cout_Res(graf,n);
	cout << v_tree;
	delete_graf(graf);
}