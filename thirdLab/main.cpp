#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include "queue.h"

using namespace std;


int main() {
    string fileInputName  = "input.txt";
	string fileOutputName = "result.txt";
	const Data arrSize = 20;

	Queue* queue = queue_create();
	vector<list<Data>> graph;
	map<string,Data> cityIdx;
	vector< string> cityName;

	string Start;
	string end;

	ofstream fout;
	fout.open(fileOutputName);

	ifstream fin;
	fin.open(fileInputName);

	if (!fin.is_open()) {
		cout << fileInputName <<"Error while opening file";
	}

	Data cityAmount = 0;
	while (!fin.eof()) {
		fin >> Start;
		fin >> end;

		if (cityIdx.find(Start) == cityIdx.end()) {
			cityIdx.insert(make_pair(Start, cityAmount++));
			cityName.push_back(Start);
			graph.push_back({});
		}

		if (cityIdx.find(end) == cityIdx.end()) {
			cityIdx.insert(pair<string, int>(end, cityAmount++));
			cityName.push_back(end);
			graph.push_back({});
		}

		graph[cityIdx[Start]].push_back(cityIdx[end]);
	}

	graph[cityIdx[Start]].pop_back();

	Data from[arrSize];
	bool flag[arrSize];

	fill(from, from + arrSize, -1);
	fill(flag, flag + arrSize, false);

	queue_insert(queue, cityIdx[Start]);
	while (!queue_empty(queue)) {
		int rightIdx = queue_get(queue);
		queue_remove(queue);
		for (auto& x : graph[rightIdx]) {
			if (!flag[x]) {
				flag[x] = true;
				from[x] = rightIdx;
				queue_insert(queue, x);
			}
		}
	}

	int count = 0;
	vector <list<Data>> path(arrSize);
	Data d = cityIdx[end];


	while(from[d] != -1) {
		path[count].push_back(d);
		count++;
		d = from[d];
	}

	path[count].push_back(d);
	count++;
	
	for (int i = count - 1; i >= 0; i--) {
		for (int item : path[i]) {
			fout << cityName[item] << " ";
		}
	}
	queue_delete(queue);

	fin.close();
	fout.close();

    cout << "Data was written in: " << fileOutputName <<'\n';

	return 0;
}
