#include "iostream"

#include "vector.h"
#include "graph.h"

void make_set(Vector<int> &vec, Vector<int> &ranks)
{
	for (int ind = 0; ind < (int)vec.size(); ind++) {
		vec[ind] = ind;
		ranks[ind] = 0;
	}
}

int find(Vector<int> &vec, int ind)
{
	if (vec[ind] == ind)
		return ind;
	else 
		return (vec[ind] = find(vec, vec[ind])); 
}

void Union(Vector<int> &vec, Vector<int> &ranks, int x, int y)
{
	if ((x = find(vec, x)) == (y = find(vec, y)))
		return;

	if (ranks[x] < ranks[y]) 
		vec[x] = y;
	else if (ranks[y] < ranks[x]) 
		vec[y] = x;
	else {
		vec[x] = y;
		(ranks[y])++;
	}
}

void qsort(Vector<int> &vec, Graph<int, int> &g, int start, int end)
{
	if (start >= end)
		return;

	int pivot = start + (end - start) / 2;
	pivot = g.get_edge_mark(vec[pivot]);
	int left = start;
	int right = end;

	while (left <= right) {
		while (g.get_edge_mark(vec[left]) < pivot) 
			left++;
		while (g.get_edge_mark(vec[right]) > pivot) 
			right--;

		if (left <= right) {
			int temp = vec[left];
			vec[left] = vec[right];
			vec[right] = temp;
			left++;
			right--;
		}
	}

	qsort(vec, g, start, right);
	qsort(vec, g, left, end);
}

int main(int argc, char **argv)
{
	if (argc > 1) {
		if (!std::freopen(argv[1], "r", stdin)) {
			std::cout << "Could not open the file\n";
			return 1;
		}
	}

	int n, m;
	int a, b, c;

	std::cin >> n >> m;
	Graph<int, int> g(n);
	Vector<int> edges(m);
	for (int ind = 0; ind < n; ind++) 
		g.set_vertex_mark(ind, ind);
	for (int ind = 0; ind < m; ind++) {
		std::cin >> a >> b >> c;
		g.add_edge(a, b, c);
		edges[ind] = ind;
	}
	qsort(edges, g, 0, m - 1);

	int cnt = 0;
	int ind_edge = 0;
	Vector<int> ans(n - 1);
	Vector<int> vertices(n);
	Vector<int> ranks(n);

	make_set(vertices, ranks);
	while ((cnt < n - 1) and (ind_edge < m)){
		typename Graph<int, int>::edge *e = g.find_edge(edges[ind_edge]);
		a = e->from->get_mark();
		b = e->to->get_mark();

		if (find(vertices, a) != find(vertices, b)) {
			ans[cnt++] = edges[ind_edge];
			Union(vertices, ranks, a, b);
		}

		ind_edge++;
	}
	std::cout << std::endl;

	if (cnt == n - 1){
		for (int ind = 0; ind < n - 1; ind++) {
			typename Graph<int, int>::edge *e = g.find_edge(ans[ind]);
			std::cout << '(' << e->from->get_mark() << ", " << e->to->get_mark() << ", " << e->get_mark() << ")\n";
		}
	} else {
		std::cout << "The graph is not connected. Cannot form a Minimum Spanning Tree.\n";
	}

	if (argc > 1) 
		std::fclose(stdin);
	
	return 0;
}