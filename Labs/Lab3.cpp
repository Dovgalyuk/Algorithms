#include<iostream>
#include<queue.h>
#include<vector.h>
#include<vector>

using namespace std;

vector<vector<string>> makeGraph(string input) {
	vector<vector<string>> graph;

	int indexV = (int)input[0];
	int indexS = (int)input[3];
	for (int i = 0; i < indexV + 1; i++) {
		if(graph[i][indexV] != "") {
			graph[i][indexS] = input[3];
		}
		else {
			graph[i][indexV] = input[0];
			graph[i][indexS] = input[3];
		}
	}
	return graph;
}
int main() {
	vector<vector<string>> graph;
	vector<bool> used;

	Queue* queue = queue_create();
}