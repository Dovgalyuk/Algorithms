#include<iostream>
#include<queue.h>
#include<vector.h>
#include<vector>
#include<stdlib.h>
#include<string>

using namespace std;

vector<bool> makeUsed(vector<vector<int>> graph,char Inital,Queue* queue) {
	vector<bool> used(255);

	int Init = (int)Inital;
	queue_insert(queue, Init);
	used[Init] = true;

	while(!queue_empty(queue)) {
		int cur = queue_get(queue);
		queue_remove(queue);

		for (int neighboor : graph[cur]) {
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
	
	size_t n;
	char Inital;
	string input;
	vector<bool> used;

	vector<vector<int>> graph(255, vector<int>());
	cout << "¬ведите кол-во химических элементов\n";
	cin >> n;
	cout << "¬ведите исходный химический элемент\n";
	cin >> Inital;
	cout << "¬водите химические реакции (через enter) по примеру:'A->B'\n";
	for (size_t i = 0; i < n - 1; i++) {
		cin >> input;
		int indexV = (int)input[0];
		int indexS = (int)input[3];

		graph[indexV].push_back(indexS);
	}

	Queue* queue = queue_create();
	used = makeUsed(graph, Inital, queue);
	cout << "Ёлементы, которые мы можем получить из исходного\n";
	for (int i = 0; used.size(); i++) {
		if (used[i]) {
			cout << char(i) << "\n";
		}
	}
}