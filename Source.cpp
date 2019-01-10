#include <iostream>
using namespace std;

/*recursion method*/

int mas[2][20][20];

int next(int step, int n, char c)
{
	if (n == step)
	{
		if (c != 'a')
			return 3;
		else
			return 2;
	}
	if (mas[c-'a'][step][n] >= 0)
		return mas[c - 'a'][step][n];
	int res = 0;
	step++;
	if(c != 'a')
		res = next(step,n,'a') + 2 * next(step, n, 'b');
	else
		res =  2 * next(step, n, 'b');
	mas[c - 'a'][step-1][n] = res;
	return res;
}

int main()
{
	int n; 
	cin >> n;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < n; j++)
			memset(mas[i][j], -1, sizeof(int)*n);
	if (n < 1)
		cout << "0";
	else
		cout<< next(0, n-1, 'b');
}
/*formula method*/
int main()
{
	int n;
	cin >> n;
	int last1 = 1;
	int last2 = 3;
	for (int i = 1; i < n; i++)
	{
		last1 = last2 - last1;
		last2 = last1 + 2 * last2;
	}
	if (n < 1)
		cout << "0";
	else
		cout << last2;
}