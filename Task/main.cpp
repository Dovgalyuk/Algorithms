#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <list>

#include "queue.h"

#define arraySize 20

int main()
{
	Queue* queue = queue_create();

	std::vector<std::list<int>> graf;

	std::map<std::string, int> cityIndex;
	std::vector<std::string> cityName;

	std::string start;
	std::string end;

	std::ifstream fin;
	std::ofstream fout;

	fin.open("input.txt");
	fout.open("output.txt");

	if (fin.is_open())
	{
		int cityCount = 0;
		while (true)
		{
			fin >> start;
			fin >> end;

			if (fin.eof())
			{
				graf[cityIndex[start]].pop_back();

				std::cout << "Start: " << start << std::endl;
				std::cout << "End: "   << end   << std::endl;
				
				break;
			}

			if (cityIndex.find(start) == cityIndex.end())
			{
				cityIndex.insert(std::pair<std::string, int>(start, cityCount));
				cityName.push_back(start);
				graf.push_back({});
				cityCount++;
			}

			if (cityIndex.find(end) == cityIndex.end())
			{
				cityIndex.insert(std::pair<std::string, int>(end, cityCount));
				cityName.push_back(end);
				graf.push_back({});
				cityCount++;
			}
			
			graf[cityIndex[start]].push_back(cityIndex[end]);
		}
	}
	else
	{
		std::cout << "File is not open" << std::endl;
		return 1;
	}

	int from[arraySize];
	bool isVisited[arraySize];

	std::fill(from, from + arraySize, -1);
	std::fill(isVisited, isVisited + arraySize, false);

	// BFS
	queue_insert(queue, cityIndex[start]);
	while (!queue_empty(queue))
	{
		int currectIndex = queue_get(queue);
		queue_remove(queue);
		for (auto& x : graf[currectIndex])
		{
			if (!isVisited[x])
			{
				isVisited[x] = true;
				from[x] = currectIndex;
				queue_insert(queue, x);
			}
		}
	}
	
	// Restore the shortest path
	int count = 0;
	int path[arraySize];
	int d = cityIndex[end];

	while (from[d] != -1)
	{
		path[count] = d;
		count++;
		d = from[d];
	}

	path[count] = d; 
	count++;

	for (int i = count - 1; i >= 0; i--)
	{
		std::cout << cityName[path[i]] << " ";
		fout << cityName[path[i]] << " ";
	}
	
	queue_delete(queue);

	fin.close();
	fout.close();

	return 0;
}
