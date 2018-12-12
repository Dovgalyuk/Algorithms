#include "stdafx.h"
#include <iostream>
#include "tree.h"
#include <vector>

using namespace std;


int main()
{
	size_t N;
	
	cin >> N;

	vector<Data> input(N);

	for (size_t i = 0; i < N; i++)
	{
		cin >> input[i];
	}

	Tree* OwnTree = tree_create();

	for (size_t i = 0; i < N; i++)
	{
		insert(get_root(OwnTree), input[i]);
	}

	get_result_hight(get_root(OwnTree));
	get_result_length(get_root(OwnTree));

	cout << endl;
	system("Pause");
	return 0;
}
