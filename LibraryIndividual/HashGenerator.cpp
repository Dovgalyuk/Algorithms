#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <time.h>
#include "HashMap.h"
using namespace std;

string generate_filename = "rand1.txt";
string input_filename = "rand1.txt";
string output_filename = "output.txt";


void generate_file(ofstream& file, const size_t size)
{
	srand(time(NULL));

	std::string text;

	for (int i = 0, j = 0; i < size; i++)
	{
		j = rand() % 10 + 1;

		if (j > size - i) j = size - i;
		i += j;

		for (int k = 0; k < j; k++)
		{
			text += static_cast<char>(rand() % 26 + 97);
		}
		text += ' ';
	}
	text[text.size() - 1] = '.';

	file << text;
	file.close();
}

void try_open_file(fstream& file, const string open_path, const string error_message)
{
	file.open(open_path);
	while (!file.is_open())
	{
		cerr << error_message << endl;
		
		string new_path;
		cin >> new_path;
		file.open(new_path);
	}
}

void try_open_file(ofstream& file, const string open_path, const string error_message)
{
	file.open(open_path);
	while (!file.is_open())
	{
		cerr << error_message << endl;

		string new_path;
		cin >> new_path;
	}
}

int main()
{
	char answ = 'N';
	cout << "Do you need to generate file? Y/N: ";
	cin >> answ;
	cout << endl;
	while (answ == 'Y')
	{
		ofstream file;
		try_open_file(file, generate_filename, "Bad generate filepath! Try new one: ");

		generate_file(file, rand() % 10000 + 5000);
		cout << "Success!" << endl;

		cout << "Do you need to generate file? Y/N: ";
		cin >> answ;

		cout << endl;
		generate_filename = "";
	}

	unordered_map<string, string> unordered_map;
	HashMap hash_map;

	fstream input;
	try_open_file(input, input_filename, "Bad input filepath! Try new one: ");

	vector<string> text;
	while (!input.eof())
	{
		string str;
		input >> str;
		text.push_back(str);
	}

	clock_t end;
	clock_t start = clock();
	for (int i = 0; i < text.size(); i++)
	{
		hash_map.Add(std::to_string(i), text[i]);
	}
	end = clock();
	cout << "HashMap insert time: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

	ofstream output;
	try_open_file(output, output_filename, "Bad output filepath! Try new one: ");
	
	output << "Hash: " << endl;
	start = clock();
	for (int i = 0; i < text.size(); i++)
	{
		output << hash_map.Find(std::to_string(i));
	}
	end = clock();
	cout << "HashMap find time: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

	fstream file2(input_filename);

	start = clock();
	for (int i = 0; i < text.size(); i++)
	{
		unordered_map.insert(pair<string, string>(std::to_string(i), text[i]));
	}
	end = clock();
	cout << "Unordered map insert time: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

	output << endl << "Std unordered: " << endl;
	start = clock();
	for (int i = 0; i < text.size(); i++)
	{
		output << unordered_map.at(std::to_string(i));
	}
	end = clock();
	cout << "Unordered find time: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

}