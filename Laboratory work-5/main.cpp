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

using namespace std;

vector<int> output;
vector<int> tmp;								//Вектор возможной последовательности.

void processing(vector<int>& input, int i)
{
	tmp.push_back(input[i]);
		
	for (int j = i + 1; j < input.size(); j++)
	{
		if (tmp[tmp.size() - 1] < input[j])
		{
			processing(input, j);
			
			if (tmp.size() != 0)
			{
				tmp.resize(tmp.size() - 1);
			}
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

int main()
{
	size_t N;

	cin >> N;

	vector<int> input(N);

	for (size_t i = 0; i < N; i++)
	{
		cin >> input[i];
	}

	for (size_t i = 0; i < N; i++)
	{
		processing(input, i);
		tmp.clear();
	}

	cout << output.size() << endl;

	for (size_t i = 0; i < output.size(); i++)
	{
		cout << output[i] << " ";
	}

	cout << endl;
	system("Pause");
	return 0;
}
