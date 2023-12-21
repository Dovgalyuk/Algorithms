#include<iostream>
#include<queue.h>
#include<vector.h>
#include<vector>
#include<stdlib.h>
#include<string>

using namespace std;

vector<vector<int>> makeGraph(string input) 
{
	vector<vector<int>> graph;
	graph.assign(10000, vector<int>(10000));

	int indexV = (int)input[0];
	int indexS = (int)input[3];
	for (int i = 0; i < indexV; i++) {
		if(graph[i][indexV] == NULL) {
			graph[i][indexS] = indexS;
		}
		else {
			graph[i][indexV] = indexV;
			graph[i][indexS] = indexS;
		}
	}
	return graph;
}
vector<bool> makeUsed(vector<vector<int>> graph,char Inital,Queue* queue) {
	vector<bool> used(10000);

	int Init = (int)Inital;
	queue_insert(queue, Init);
	used[Init] = true;

	while(!queue_empty(queue)) {
		int cur = queue_get(queue);
		queue_remove(queue);

		for (Data neighboor : graph[cur]) {
			if (!used[neighboor]) {
				queue_insert(queue, neighboor);
				used[neighboor] = true;
			}
		}
	}
	return used;
}
int main() {
	setlocale(LC_ALL, "Rus");
	vector<vector<int>> graph;

	
	size_t n;
	char Inital;
	string input;
	vector<bool> used;

	cout << "¬ведите кол-во химических элементов\n";
	cin >> n;
	cout << "¬ведите исходный химический элемент\n";
	cin >> Inital;
	cout << "¬водите химические реакции (через enter) по примеру:'A->B'";
	for (size_t i = 0; i < n - 1; i++) {
		cin >> input;
		graph = makeGraph(input);
	}

	Queue* queue = queue_create();
	used = makeUsed(graph, Inital, queue);
	cout << "Ёлементы, которые мы можем получить из исходного\n";
	for (int i = 0; used.size();i++) {
		if (used[i]) {
			cout << char(i) << "\n";
		}
	}
}