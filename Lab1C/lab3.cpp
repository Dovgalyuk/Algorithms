#include <iostream>
#include "queue.h"
#include <vector>
#include <string>
#include <map>
#include <fstream>

using namespace std;
typedef vector<vector<size_t>> graph;
size_t FindRootIndexForNode(const graph& g, size_t node, size_t start = 0) {
	if (!g.empty() && (start < g.size())) {
		for (size_t i = start; i < g.size(); i++) {
			if (g[i].size() > 0)
				for (size_t j = 0; j < g[i].size(); j++)
					if (g[i][j] == node)
						return i;
		}
	}
	return SIZE_MAX;
}
graph InputGraph(size_t* start, size_t* end, size_t* size, vector<string>& points) {
	graph graph;
	string str = "";
	string node1 = "";
	string node2 = "";
	bool flag = true;
	cout << "input 'Enter' for exit from Input" << endl;
	while (flag) {
		cout << "input node1-node2: ";
		getline(cin, str);
		if (str != "") {
			node1 = "";
			node2 = "";
			size_t i = 0;
			while ((str[i] != '\0') && (str[i] != ' ')) {
				if (str[i] != ' ')
					node1 += str[i];
				i++;
			}
			i++;
			while (i < str.length()) {
				if (str[i] != ' ')
					node2 += str[i];
				i++;
			}

			size_t index1 = SIZE_MAX;
			size_t index2 = SIZE_MAX;

			for (size_t j = 0;j < points.size();j++) {
				if (points[j] == node1)
					index1 = j;
				if (points[j] == node2)
					index2 = j;
			}
			if (index1 == SIZE_MAX)
			{
				index1 = points.size();
				points.push_back(node1);
			}
			if (index2 == SIZE_MAX)
			{
				index2 = points.size();
				points.push_back(node2);
			}
			graph.resize(points.size());
			graph[index1].push_back(index2);
		}
		else flag = false;
	}

	cout << "input 'start' 'end' positions: ";
	getline(cin, str);
	node1 = "";
	node2 = "";
	size_t i = 0;
	while ((str[i] != '\0') && (str[i] != ' ')) {
		node1 += str[i];
		i++;
	}
	i++;
	while (i < str.length()) {
		node2 += str[i];
		i++;
	}

	size_t index1 = SIZE_MAX;
	size_t index2 = SIZE_MAX;

	for (size_t j = 0;j < points.size();j++) {
		if (points[j] == node1)
			index1 = j;
		if (points[j] == node2)
			index2 = j;
	}
	*size = points.size();
	*start = index1;
	*end = index2;

	return graph;
}
vector<size_t> findNodes(const graph& g, size_t node) {
	vector<size_t> nodes;
	size_t size = g[node].size();
	if (size > 0) {
		for (size_t i = 0;i < size;i++) {
			nodes.push_back(g[node][i]);
		}
	}
	size_t index = FindRootIndexForNode(g, node);
	while (index != SIZE_MAX) {
		nodes.push_back(index);
		index = FindRootIndexForNode(g, node, index + 1);
	}
	return nodes;
}
vector<size_t> BFS(const graph& g, size_t node, size_t goalNode, size_t size) {
	vector<bool> visited(size, false);
	vector<size_t> parent(size, SIZE_MAX);
	parent[node] = node;
	visited[node] = true;
	Queue* queue = queue_create(NULL);
	size_t* startNode = (size_t*)malloc(sizeof(size_t));
	*startNode = node;
	queue_insert(queue, startNode);
	while (!queue_empty(queue))
	{
		node = *((size_t*)queue_get(queue));
		queue_remove(queue);
		if (node == goalNode) {
			break;
		}
		vector<size_t> nodes = findNodes(g, node);
		if (nodes.size() > 0) {
			for (auto n : nodes) {
				if (!visited[n]) {
					visited[n] = true;
					parent[n] = node;
					size_t* q = (size_t*)malloc(sizeof(size_t));
					*q = n;
					queue_insert(queue, q);
				}
			}
		}
	}
	queue_delete(queue);
	return parent;
}
void PrintWay(const vector<size_t>& parent, const vector<string>& points, size_t node, string* message) {
	if (parent[node] != node)
		PrintWay(parent, points, parent[node], message);
	*message += points[node] + " ";
}
int main()
{
	vector<string> points;
	size_t start, end, size;
	graph g = InputGraph(&start, &end, &size, points);
	vector<size_t> parent = BFS(g, start, end, size);
	ofstream fout("Way.txt");
	string message = "";
	PrintWay(parent, points, end, &message);
	fout << message;
	fout.close();
	system("pause");
}
