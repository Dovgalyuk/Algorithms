#include <iostream>
#include "map.hpp"
#include <string>

using namespace std;

int main()
{
	Map<string, string> test;
	test.add("test1", "1");
	test.add("test2", "2");
	test.add("test3", "3");
	cout << test.find("test2") << "  " << test.find("test2")->second() << endl;
	test.RemovePair("test2");
	cout << test.find("test2") << endl;
}