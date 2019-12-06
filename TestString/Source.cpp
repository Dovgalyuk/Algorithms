#include <iostream>
#include <string>
#include "String.hpp"

using namespace std;

int main()
{
	String test;
	if (test.length())
		cout << "start size error" << endl;
	const char* data = "123";
	String test1(data);
	if (test1.length() != 3)
		cout << "c string init error" << " " << test1.std_type() << endl;
	string data1 = "321";
	String test2(data1);
	if (test2.length() != 3)
		cout << "std string init error" << " " << test2.std_type() << endl;
	String test3(test1);
	if (test1.length() != test3.length())
		cout << "string copy constryctor error" << " " << test3.std_type() << endl;
	String test4(test1 + test2);
	if (test4.length() != test1.length() + test2.length())
		cout << "string sum error" << " " << test4.std_type() << endl;
	test += test1;
	if (test.length() != test1.length())
		cout << "+= error" << " " << test.std_type() << endl;
	test = test2;
	if (test.length() != test2.length())
		cout << "copy error" << " " << test.std_type() << endl;
	if (test1 == test2)
		cout << "compare error ==" << " " << endl;
	if (test != test2)
		cout << "compare error !=" << " " << endl;
	if (test[0] != '3' || test[2] != '1')
		cout << "operator [] error" << ' ' << endl;
	test.resize(6, 254);
	if (test.length() != test4.length())
		cout << "resize error bigger" << ' ' << test.std_type() << endl;
	test.resize(2, 254);
	if (test.length() != 2)
		cout << "resize error smoller" << ' ' << test.std_type() << endl;
	String testfind("qwerty");
	if (testfind.find("ert") != 2)
		cout << "find error" << ' ' << testfind.find("ert") << endl;
	cout << test.c_type();
}