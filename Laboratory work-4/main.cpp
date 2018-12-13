// АВЛ - дерево.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include "tree.h"
#include <map>
#define MAX 5000000
#include <ctime>
#include <vector>

using namespace std;

void test_tree(Tree* p)
{

	Data str1, str2;

	cout << "------------------------------------" << endl;

	while (true)
	{
		cout << "Key | Value" << endl;
		cin >> str1 >> str2;

		if (str1 == "-1")
		{
			break;
		}

		insert_leaf(p, str1, str2);

		cout << "====================================" << endl;

		if (balance_tree(get_root(p), get_height(p)))
		{
			cout << "Balance" << endl;
		}
		else
		{
			cout << "Not balance" << endl;
		}

		cout << "************************************" << endl;

		cout << "Root is: " << get_root_key(p) << endl;
		cout << "------------------------------------" << endl;
	}

	cout << "\n\n";

	while (true)
	{
		cout << "------------------------------------" << endl;
		cout << "Key:";
		cin >> str1;
		cout << "====================================" << endl;

		if (str1 == "-1")
		{
			break;
		}

		cout << "Value: " << get_value_of_leaf(p, str1) << endl;
	}

	while (true)
	{
		cout << "------------------------------------" << endl;
		cout << "Delete key:";
		cin >> str1;
		cout << "====================================" << endl;

		if (str1 == "-1")
		{
			break;
		}

		delete_leaf(p, str1);

		cout << "====================================" << endl;

		if (balance_tree(get_root(p), get_height(p)))
		{
			cout << "Balance" << endl;
		}
		else
		{
			cout << "Not balance" << endl;
		}

		cout << "************************************" << endl;
		cout << "Root is: " << get_root_key(p) << endl;
		cout << "------------------------------------" << endl;
	}
}

Data randomStrGen(size_t length)
{
	static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	string result;
	result.resize(length);

	for (size_t i = 0; i < length; i++)
		result[i] = charset[rand() % charset.length()];

	return result;
}

void AVL_vs_map(Tree* OwnTree)
{
	map <Data, Data> example;

	cout << "------------------------------------------------------------" << endl;
	cout << "AVL - tree" << endl;

	int startAVL = clock();
	cout << (float(startAVL)) / CLOCKS_PER_SEC << endl;

	srand(time(NULL));

	for (size_t i = 0; i < MAX; i++)
	{
		insert_leaf(OwnTree, randomStrGen(rand() % 5), randomStrGen(rand() % 5));
	}

	int endAVL = clock();
	cout << (float(endAVL)) / CLOCKS_PER_SEC << endl;

	cout << "------------------------------------------------------------" << endl;

	cout << "MAP" << endl;

	int startMAP = clock();
	cout << (float(startMAP)) / CLOCKS_PER_SEC << endl;

	for (size_t i = 0; i < MAX; i++)
	{
		example.insert(make_pair(randomStrGen(rand() % 5), randomStrGen(rand() % 5)));
	}

	int endMAP = clock();
	cout << (float(endMAP)) / CLOCKS_PER_SEC << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "Result:" << endl;
	cout << "AVL - tree: " << (float(endAVL - startAVL)) / CLOCKS_PER_SEC << endl;
	cout << "MAP: " << (float(endMAP - startMAP)) / CLOCKS_PER_SEC << endl;
}

int main()
{
	Tree* OwnTree = tree_create();
	
	AVL_vs_map(OwnTree);

	system("Pause");
	return 0;
}
