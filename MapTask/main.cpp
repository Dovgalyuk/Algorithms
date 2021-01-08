#include <iostream>
#include <ctime>
#include "map.h"
#include <map>

using namespace std;

string FromTo(unsigned char start, unsigned char end)
{
	string select ="";
	int string_size = end - start + 1;

	if (string_size > 0)
	{
		select.reserve(string_size);
		for (int i = start; i <= end; i++)
			select += (char)i;
	}

	return select;
}

string StrGenerate()
{
	static const int STRING_SIZE = 10;
	static const string white_list = FromTo('a', 'z') + FromTo('A', 'Z') + FromTo('0', '9');

	string new_string ="";
	new_string.reserve(STRING_SIZE);
	for (int i = 0; i < STRING_SIZE; i++)
		new_string += white_list[rand() % white_list.length() ];
	return new_string;
}

class AverageValue
{
private:
	size_t value;
	size_t number;
public:
	AverageValue()
	{
		value = 0;
		number = 0;
	}
	void add(int value, int number =1)
	{
		this->value += value;
		this->number += number;
	}
	double get_average()
	{
		return (double) value / number;
	}
};

int main()
{
	srand((unsigned int)time(NULL));

	int nodes_number;

	unsigned int clock_start;
	unsigned int clock_finish;

	cout << "number of nodes =";
	cin >> nodes_number;

	pair<Key, Data>* NodesList = new pair<Key, Data>[nodes_number];
	for (int i = 0; i < nodes_number; i++)
		NodesList[i] = make_pair(StrGenerate(), StrGenerate());

	map<string, string> STL_map;
	Map* My_map = map_create();

	cout << "\nadding " << nodes_number << " nodes to the tree:\n";

	clock_start = clock();
	for (int i = 0; i < nodes_number; i++)
		map_add(My_map, NodesList[i].first, NodesList[i].second);
	clock_finish = clock();
	cout << "\t\"Map.h\"\ttime =" << (float)(clock_finish - clock_start) / CLOCKS_PER_SEC << " seconds\n";

	clock_start = clock();
	for (int i = 0; i < nodes_number; i++)
		STL_map.insert(NodesList[i]);
	clock_finish = clock();
	cout << "\t<map>\ttime =" << (float)(clock_finish - clock_start) / CLOCKS_PER_SEC << " seconds\n\n";

	cout << "search for " << nodes_number << " nodes in the tree:\n";

	clock_start = clock();
	for (int i = 0; i < nodes_number; i++)
		map_get_value(My_map, NodesList[i].first);
	clock_finish = clock();
	cout << "\t\"Map.h\"\ttime =" << (float)(clock_finish - clock_start) / CLOCKS_PER_SEC << " seconds\n";

	clock_start = clock();
	for (int i = 0; i < nodes_number; i++)
		STL_map[NodesList[i].first];
	clock_finish = clock();
	cout << "\t<map>\ttime =" << (float)(clock_finish - clock_start) / CLOCKS_PER_SEC << " seconds\n\n";
	
	cout << "create a graph:\n";

	map<int, AverageValue> Graph;
	const int FIND_PER_CYCLE =1000;
	for (int i = 0, j, height; i < nodes_number; i+= FIND_PER_CYCLE)
	{
		height = map_tree_height(My_map);

		clock_start = clock();
		for (j = 0; j < FIND_PER_CYCLE; j++)
			map_get_value(My_map, NodesList[i + j].first);
		clock_finish = clock();

		Graph[height].add(clock_finish - clock_start , FIND_PER_CYCLE);

		for (j = 0; j < FIND_PER_CYCLE; j++)
			map_remove(My_map, NodesList[i + j].first);

		cout << 100 * i / nodes_number << "%\r";
	}

	cout << endl;

	for (auto it = Graph.begin(); it != Graph.end(); ++it)
	{
		cout << "\theight = " << it->first << "\t time = " << it->second.get_average() << endl;
	}

	delete[] NodesList;
	map_delete(My_map);
}
