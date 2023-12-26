#include<iostream>
#include<queue.h>
#include<vector.h>
#include<vector>
#include<stdlib.h>
#include<string>

using namespace std;

vector<bool> makeUsed(vector<vector<int>> &graph,char Inital,Queue* queue) {
	vector<bool> used(1000);

	int Init = static_cast<int>(Inital);
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
	used[Init] = false;
	return used;
}
int main() {
	setlocale(LC_ALL, "Rus");
	
	size_t n;
	char Inital;
	string input;
	vector<bool> used(500);

	vector<vector<int>> graph(500, vector<int>(1));
	cout << "¬ведите кол-во химических элементов\n";
	cin >> n;
	cout << "¬ведите исходный химический элемент\n";
	cin >> Inital;
	cout << "¬водите химические реакции (через enter) по примеру:'A->B'\n";
	for (size_t i = 0; i < n - 1; i++) {
		cin >> input;
		int indexV = static_cast<int>(input[0]);
		int indexS = static_cast<int>(input[3]);

		if (graph[indexV][0] != indexV) {
			graph[indexV][0] = indexV;
		}
		graph[indexV].push_back(indexS);
	}

	Queue* queue = queue_create();
	used = makeUsed(graph, Inital, queue);
	cout << "Ёлементы, которые мы можем получить из исходного\n";
	for (int i = 0; i < (int)used.size(); i++) {
		if (used[i]) {
			cout << char(i) << " ";
		}
	}
	while(used.size()>0) {
		used.pop_back();
	}
}