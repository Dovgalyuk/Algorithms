/*
Задача №5:
----------------------------------------------------------
Дана последовательность чисел X1, X2, ..., Xn.
Требуется вычеркнуть минимальное число цифр так, чтобы
оставшиеся шли в порядке возрастания.
На экран выводится число невычеркнутых цифр, а затем сама
последовательность.
----------------------------------------------------------
*/

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;

vector<int> output;
vector<int> tmp;								//Вектор возможной последовательности.
vector<int> Lengths;

//Перебирает все возможные последовательсноти.
void processing(vector<int>& input, int i)
{
	tmp.push_back(input[i]);
		
	for (int j = i + 1; j < input.size(); j++)
	{
		if (tmp[tmp.size() - 1] < input[j])
		{
			processing(input, j);
			tmp.resize(tmp.size() - 1);
		}
	}

	if (tmp.size() >= output.size())
	{
		output.resize(tmp.size());

		for (int i = 0; i < tmp.size(); i++)
		{
			output[i] = tmp[i];
		}
	}
}

ofstream fout("output.txt");

//Считает максимальную длину возрастающей последовательности для каждого элемента в массиве.
int processing2(vector<int>& input, int i)
{
	int max = 1;
	int Length = 1;

	Lengths[i] = 1;

	for (int j = i + 1; j < input.size(); j++)
	{
		if (input[i] < input[j])
		{
			if (Lengths[j] != 0)
			{
				Length += Lengths[j];
			}
			else
			{
				Length += processing2(input, j);
			}

			if (max <= Length)
			{
				max = Length;
				Lengths[i] = Length;
			}

			Length = 1;
		}
	}

	return max;
}

int main()
{
	size_t N;

	cin >> N;

	vector<int> input(N);

	srand(time(NULL));

	for (size_t i = 0; i < N; i++)
	{
		input[i] = rand();
	}

	cout << endl;

	chrono::time_point<chrono::high_resolution_clock> startProcessing2, endProcessing2;

	for (size_t i = 0; i < N; i += 1000)
	{
		Lengths.resize(N);
		
		startProcessing2 = chrono::high_resolution_clock::now();
		processing2(input, i);
		endProcessing2 = chrono::high_resolution_clock::now();
	
		double delta = chrono::duration_cast<chrono::microseconds> (endProcessing2 - startProcessing2).count();
		
		cout << "----------------------------------------------------" << endl;
		cout << "Length for " << i + 1 << ": " << Lengths[i] << endl;
		cout << i + 1 << ": " << "Processing2(): " << delta << " microseconds" << endl;
		cout << "----------------------------------------------------" << endl;


		Lengths.clear();
	}

	cout << endl;
	cout << endl;

	chrono::time_point<chrono::high_resolution_clock> startProcessing, endProcessing;

	for (size_t i = 0; i < N; i += 1000)
	{
		startProcessing = chrono::high_resolution_clock::now();

		processing(input, i);

		endProcessing = chrono::high_resolution_clock::now();

		double delta = chrono::duration_cast<chrono::microseconds> (endProcessing - startProcessing).count();

		cout << i + 1 << ": " <<"Processing():" << delta << " microseconds" << endl;
	}

	/*
	cout << output.size() << endl;

	for (size_t i = 0; i < output.size(); i++)
	{
		cout << output[i] << " ";
	}
	*/

	cout << endl;
	system("Pause");
	return 0;
}
