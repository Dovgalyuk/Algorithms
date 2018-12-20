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
/*
vector<int> output;
vector<int> tmp;								//Вектор возможной последовательности.

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
}*/

//Считает максимальную длину возрастающей последовательности для каждого элемента в массиве.
int processing2(vector<int>& input, int i)
{
	int max = 1;
	int Length = 1;

	if (i + 1 >= input.size())
	{
		return 1;
	}

	for (int j = i + 1; j < input.size(); j++)
	{
		if (input[i] < input[j])
		{
			Length += processing2(input, j);

			if (max < Length)
			{
				max = Length;
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

	for (size_t i = 0; i < N; i++)
	{
		cin >> input[i];
	}

	for (size_t i = 0; i < N; i++)
	{
		cout << processing2(input, i) << " ";

		/*processing(input, i);
		tmp.clear();*/
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
