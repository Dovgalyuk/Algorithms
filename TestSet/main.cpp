#include <iostream>
#include <string>
#include <algorithm>
#include "set.hpp"

using namespace std;

int main()
{
	size_t sc = 0;
	Set <int> set(100);
	for (int i = 0; i < 26; i++)
	{
		set.set_add(i);
		sc++;
	}
	if (set.set_size() == sc)
	{
		cout << "First test ok." << endl;
		cout << "Size of set: " << set.set_size() << endl;
	}
	else
	{
		cout << "First test failed;(" << endl;
		cout << "Size of set: " << set.set_size() << endl;
	}
	size_t sc2 = 0;
	int t = 0;
	for (size_t i = 0; i < 10; i++)
	{
		set.set_remove(t);
		t++;
		sc2++;
	}
	if (set.set_size() == sc - sc2)
	{
		cout << "Second test ok." << endl;
		cout << "Size of set: " << set.set_size() << endl;
	}
	else
	{
		cout << "Second test failed;(" << endl;
		cout << "Size of set: " << set.set_size() << endl;
	}

	cout << "End of tests." << endl;
	set.set_add(5);
	set.set_add(5);
	cout << "Size of set: " << set.set_size() << endl;
	set.set_remove(5);
	cout << "Size of set: " << set.set_size() << endl;

	Set <string> set1(200);
	set1.set_add("hello");
	set1.set_add("my");
	set1.set_add("dear");
	set1.set_add("friend");

	cout << set1.set_size() << endl;
	set1.set_remove("friend");
	cout << set1.set_size() << endl;
	set1.set_remove("de");
	cout << set1.set_size() << endl;
	cout << set1.set_search("dear") << endl;

	for (size_t i = 0; i < set.set_size(); i++)
	{
		cout << set.set_iter(i) << " ";
	}
	cout << endl;
}