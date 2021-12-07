#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include "queue.h"

int main()
{
	const std::string input_name  = "input.txt";
	const std::string output_name = "output.txt";
	const Data array_size = 20;

	Queue* queue = queue_create();
	std::vector<std::list<Data>> graph;
	std::map<std::string,Data> city_index;
	std::vector<std::string>  city_name;

	std::string start;
	std::string end;

	std::ofstream fout;
	fout.open(output_name);

	std::ifstream fin;
	fin.open(input_name);
	if (!fin.is_open())
	{
		std::cout << input_name <<"-This file did not open\n";
		system("pause");
		exit(0);
	}

	Data city_count = 0;
	while (!fin.eof())
	{
		fin >> start;
		fin >> end;

		if (city_index.find(start) == city_index.end())
		{
			city_index.insert(std::pair<std::string, int>(start, city_count++));
			city_name.push_back(start);
			graph.push_back({});
		}

		if (city_index.find(end) == city_index.end())
		{
			city_index.insert(std::pair<std::string, int>(end, city_count++));
			city_name.push_back(end);
			graph.push_back({});
		}

		graph[city_index[start]].push_back(city_index[end]);
	}

	graph[city_index[start]].pop_back();

	Data from[array_size];
	bool is_visited[array_size];

	std::fill(from, from + array_size, -1);
	std::fill(is_visited, is_visited + array_size, false);

	queue_insert(queue, city_index[start]);
	while (!queue_empty(queue))
	{
		int currect_index = queue_get(queue);
		queue_remove(queue);
		for (auto& x : graph[currect_index])
		{
			if (!is_visited[x])
			{
				is_visited[x] = true;
				from[x] = currect_index;
				queue_insert(queue, x);
			}
		}
	}

	Data count = 0;
	Data path[array_size];
	Data d = city_index[end];

	while (from[d] != -1)
	{
		path[count++] = d;
		d = from[d];
	}

	path[count++] = d;

	for (int i = count - 1; i >= 0; i--)
		fout << city_name[path[i]] << " ";

	queue_delete(queue);

	fin.close();
	fout.close();

	return 0;
}