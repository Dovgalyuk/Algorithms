#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "queue.h"

using namespace std;

int main()
{
	map<size_t, string> index_to_name;
	map<string, size_t> name_to_index;
	size_t size = 0;
	vector<vector<size_t>> mat;
	string first, second;
	do
	{
		cin >> first >> second;
		if (first == "Start" and second == "End")
			break;
		if (name_to_index.find(first) == name_to_index.end())
		{
			index_to_name.insert(make_pair(size, first));
			name_to_index.insert(make_pair(first, size));
			size++;
			mat.resize(size);
		}
		if (name_to_index.find(second) == name_to_index.end())
		{
			index_to_name.insert(make_pair(size, second));
			name_to_index.insert(make_pair(second, size));
			size++;
			mat.resize(size);
		}
		mat[name_to_index.find(first)->second].push_back(name_to_index.find(second)->second);
		mat[name_to_index.find(second)->second].push_back(name_to_index.find(first)->second);
	} while (first != "Start" or second != "End");
	vector<int> dst(size, -1);
	Queue* q = queue_create();
	int start = name_to_index.find("Start")->second;
	int end = name_to_index.find("End")->second;
	dst[start] = 0;
	queue_insert(q, start);
	while (!queue_empty(q))
	{
		size_t curr = queue_get(q);
		queue_remove(q);
		for (size_t i = 0; i < mat[curr].size(); i++)
			if (dst[mat[curr][i]] == -1)
			{
				queue_insert(q, mat[curr][i]);
				dst[mat[curr][i]] = dst[curr] + 1;
			}
	}
	if (dst[end] == -1)
	{
		cout << "There is no way from Start to End\n";
	}
	else
	{
		vector<string> way;
		size_t i = end;
		while (i != start)
		{
			way.push_back(index_to_name.find(i)->second);
			for (size_t j=0; j<mat[i].size();j++)
				if (dst[mat[i][j]] == dst[i] - 1)
				{
					i = mat[i][j];
					break;
				}
			if (i == start)
				way.push_back(index_to_name.find(i)->second);
		}
		for (size_t j = way.size() - 1; j > 0; j--)
			cout << way[j] << " ";
		cout << way[0] << endl;
	}
	queue_delete(q);
}