#include <iostream>
#include "queue.h"
#include <vector>
#include <string>
#include <map>
#include <fstream>

using namespace std;
size_t FindRootIndex(vector<vector<string>> v, string root) {
	if (!v.empty()) {
		for (size_t i = 0; i < v.size(); i++) {
			if (v[i][0] == root)
				return i;
		}
	}
	return (size_t)(-1);
}
size_t FindRootIndexForNode(vector<vector<string>> v, string node, size_t start = 0) {
	if (!v.empty() && (start < v.size())) {
		for (size_t i = start; i < v.size(); i++) {
			for (size_t j = 1; j < v[i].size(); j++)
				if (v[i][j] == node)
					return i;
		}
	}
	return (size_t)(-1);
}
vector<vector<string>> InputGraph(string* start, string* end) {
	vector<vector<string>> graph;
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
				node1 += str[i];
				i++;
			}
			i++;
			while (i < str.length()) {
				node2 += str[i];
				i++;
			}

			size_t index = FindRootIndex(graph, node1);
			if (index == -1)
				graph.push_back(vector<string> {node1});
			index = FindRootIndex(graph, node1);
			graph[index].push_back(node2);
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
	*start = node1;
	*end = node2;

	return graph;
}
vector<string> findNodes(vector<vector<string>>graph, string node) {
	vector<string> nodes;
	size_t index = FindRootIndex(graph, node);
	if (index != -1) {
		for (size_t i = 1;i < graph[index].size();i++) {
			nodes.push_back(graph[index][i]);
		}
	}
	index = FindRootIndexForNode(graph, node);
	while (index != -1) {
		nodes.push_back(graph[index][0]);
		index = FindRootIndexForNode(graph, node, index + 1);
	}
	return nodes;
}
char* Cstring(string s) {
	size_t size = s.length();
	char* cstring = (char*)malloc(sizeof(char) * (size + 1));
	for (size_t i = 0;i < size;i++) {
		cstring[i] = s[i];
	}
	cstring[size] = '\0';
	return cstring;
}
string CPPstring(char* s) {
	string cppstring = "";
	size_t i = 0;
	while (s[i] != '\0') {
		cppstring += s[i];
		i++;
	}
	return cppstring;
}
map<string, string> BFS(vector<vector<string>>graph, string node, string goalNode) {
	map<string, bool> visited;
	map<string, string> parent;
	parent[node] = node;
	visited[node] = true;
	Queue* queue = queue_create(NULL);
	queue_insert(queue, Cstring(node));
	while (!queue_empty(queue))
	{
		node = CPPstring((char*)queue_get(queue));
		queue_remove(queue);
		if (node == goalNode) {
			break;
		}
		vector<string> nodes = findNodes(graph, node);
		if (nodes.size() > 0) {
			for (auto n : nodes) {
				if (!visited[n]) {
					visited[n] = true;
					parent[n] = node;
					queue_insert(queue, Cstring(n));
				}
			}
		}

	}
	queue_delete(queue);
	return parent;
}
void PrintWay(map<string, string> parent, string node, string* message) {
	if (parent[node] != node)
		PrintWay(parent, parent[node], message);
	*message += node + " ";
}
int main()
{
	vector<vector<string>> graph;
	string start, end;
	graph = InputGraph(&start, &end);
	map<string, string> parent = BFS(graph, start, end);
	ofstream fout("Way.txt");
	string message = "";
	PrintWay(parent, end, &message);
	fout << message;
	fout.close();
}
