#include <iostream>
#include <clocale>
#include <time.h>
#include <set>
#include "set.h"
using namespace std;

string* generate_text(unsigned long size)
{
	string* text = new string[size];
	for (int i = 0; i < size; i++)
	{
		int word_size = rand() % 20 + 4;
		for (int j = 0; j < word_size; j++)
		{
			text[i] += char('a' + rand() % 26);
		}
	}
	return text;
}

void set_test(Set* set, Data* elems, unsigned long len)
{
	for (int i = 0; i < len; i++)
	{
		set_insert(set, elems[i]);
	}
	cout << "Elements: " << endl; 
	set_output(set);
	for (int i = 0; i < len; i++)
	{
		set_remove(set, elems[i]);
		cout << endl; set_output(set);
	}
	cout << "After delete: " << endl;
	set_output(set);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	std::set<Data> std_set;
	Set* my_set = set_create();

	string* test = new string[5];
	test[0] = "this"; test[1] = "is"; test[2] = "just"; test[3] = "for"; test[4] = "test";
	set_test(my_set, test, 5);
	cout << endl;

	while (cin)
	{
		cout << "Enter word count: ";
		unsigned long len;
		cin >> len;
		string* text = generate_text(len);

		clock_t start = clock();
		for (int i = 0; i < len; i++)
		{
			set_insert(my_set, text[i]);
		}
		clock_t end = clock();
		cout << "Add time to my Set: " << double(end - start) / CLOCKS_PER_SEC << endl;

		start = clock();
		for (int i = 0, j = len - 1; i < len; i++, j--)
		{
			set_find(my_set, text[j]);
		}
		end = clock();
		cout << "Find time in my Set: " << double(end - start) / CLOCKS_PER_SEC << endl;

		start = clock();
		for (int i = 0; i < len; i++)
		{
			set_remove(my_set, text[i]);
		}
		end = clock();
		cout << "Remove time in my Set: " << double(end - start) / CLOCKS_PER_SEC << endl;

		cout << endl;

		///////////////////////////////////////////////////

		start = clock();
		for (int i = 0; i < len; i++)
		{
			std_set.insert(text[i]);
		}
		end = clock();
		cout << "Add time to std::set: " << double(end - start) / CLOCKS_PER_SEC << endl;

		start = clock();
		for (int i = 0, j = len - 1; i < len; i++, j--)
		{
			std_set.find(text[j]);
		}
		end = clock();
		cout << "Find time in std::set: " << double(end - start) / CLOCKS_PER_SEC << endl;

		start = clock();
		for (int i = 0; i < len; i++)
		{
			std_set.erase(text[i]);
		}
		end = clock();
		cout << "Remove time in std::set " << double(end - start) / CLOCKS_PER_SEC << endl;

		cout << endl;
	}
}