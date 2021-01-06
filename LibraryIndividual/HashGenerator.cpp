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
	vector<string> text;


	for (int i = 0, j = 0; i < size; i++)
	{
		j = rand() % 10 + 1;

		string str;
		for (int k = 0; k < j; k++)
		{
			str += static_cast<char>(rand() % 26 + 97);
		}

		file << str;
		if (i != size - 1) file << ' ';
	}

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
	/*char answ = 'N';
	cout << "Do you need to generate file? Y/N: ";
	cin >> answ;
	cout << endl;
	while (answ == 'Y')
	{
		ofstream file;
		try_open_file(file, generate_filename, "Bad generate filepath! Try new one: ");

		cout << "Symbols count: ";
		size_t symbolsCount;
		cin >> symbolsCount;
		generate_file(file, symbolsCount);
		cout << "Success!" << endl;

		cout << "Do you need to generate file? Y/N: ";
		cin >> answ;

		cout << endl;
		generate_filename = "";
	}*/

	unordered_map<string, string> unordered_map;
	HashMap hash_map;

	while (cin) // enter different files with different length how much you want. You can use filegenerator (upper) to generate files
	{
		cout << "How much words do you want? ";
		size_t symbols;
		cin >> symbols;

		ofstream file;
		file.open(generate_filename, ofstream::out | ofstream::trunc);
		generate_file(file, symbols);
		ifstream input(generate_filename);
		
		vector<string> text;
		while (!input.eof())
		{
			string str;
			input >> str;
			text.push_back(str);
		}

		cout << "Tests of " << text.size() << " words (elements): " << endl;

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

		string* outputText = new string[text.size()];
		start = clock();
		for (int i = 0; i < text.size(); i++)
		{
			outputText[i] = hash_map.Find(std::to_string(i));
		}
		end = clock();
		cout << "HashMap find time: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

		output << "Hash: " << endl;
		for (int i = 0; i < text.size(); i++)
		{
			output << outputText[i];
		}

		fstream file2(input_filename);

		start = clock();
		for (int i = 0; i < text.size(); i++)
		{
			unordered_map.insert(pair<string, string>(std::to_string(i), text[i]));
		}
		end = clock();
		cout << "Unordered map insert time: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

		start = clock();
		for (int i = 0; i < text.size(); i++)
		{
			outputText[i] = unordered_map.at(std::to_string(i));
		}
		end = clock();
		cout << "Unordered find time: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

		output << endl << "Std unordered: " << endl;
		for (int i = 0; i < text.size(); i++)
		{
			output << outputText[i];
		}

		input_filename = "";
	}
	
	
}