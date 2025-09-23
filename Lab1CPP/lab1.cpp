#include <iostream>
#include <../LibraryCPPClass/array.h>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <map>


using namespace std;

void fiboFunction(size_t size)
{
	Array fibo_box(size);

	if (size >= 1) { fibo_box.set(0, 0); }
	if (size >= 2) { fibo_box.set(1, 1); }

	for (size_t i = 2; i < size; i++)
	{
		int result = fibo_box.get(i-1) + fibo_box.get(i-2);
		fibo_box.set(i, result);
	}
	cout << "==========================================================" << endl;
	cout << "Fibo numbers: ";
	for (size_t i = 0; i < fibo_box.size(); i++)
	{
		cout << fibo_box.get(i) <<" ";
	}
	cout << endl;
}

void findDublicates(Array& box)
{
	bool isFound = false;
	map<int, int> num_duble;

	for (size_t i = 0; i < box.size(); i++)
	{
		int num = box.get(i);
		num_duble[num]++;
	}

	
	for (const auto& n: num_duble)
	{
		if (n.second == 2)
		{
			cout << "Found: " << n.first<<endl;
			isFound = true;
		}

	}

	if (!isFound)
	{
		cout << "The numbers were not found!" << endl;
	}
	cout << "================================================" << endl;
}

int main(int args,char* argv[]) {
	size_t size_box,size_two;
	string  data_line;

	if (args < 2)
	{
		cerr << "Error: File not specified" << endl; 
		return 1;
	}

	//Открытие файла
	ifstream read_file(argv[1]);

	if (!read_file.is_open())
	{
		cerr << "Error: Cannot open file: " << argv[1] << endl;
		return 1;
	}
	
	try {


		if (!(read_file >> size_box))
		{
			cerr << "Error: invalid arguments";
			return 1;
		}


		if (!(read_file >> size_two))
		{
			cerr << "Error: invalid arguments";
			return 1;
		}

		fiboFunction(size_box);

		 Array box(size_two); 
		 
		 for (size_t i = 0; i < size_two; i++)
			{
			 int value;
			 if (!(read_file >> value)) {

				 cerr << "Error: not enough numbers" << endl;
				 return 1;
			 }
			 box.set(i, value);
			}


		 findDublicates(box);

		
	 }
	
	 catch (const std::exception& error)
	 {
		 cerr << "ERROR:" << error.what();
		 read_file.close();
		 return 1;
	 }
		
	if (read_file.is_open())
	{
		read_file.close();
	}
	return 0;
	
}

