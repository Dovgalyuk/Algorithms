#include <iostream>
using namespace std;


/*recursion method*/
int next(int step, int n, char c)
{
	int otv = 0;
	if (n == step)
	{
		if (c != 'a')
			return 3;
		else
			return 2;
	}		
	else
	{
		step++;
		if(c != 'a')
			return next(step,n,'a') + 2 * next(step, n, 'b');
		else
			return 2 * next(step, n, 'b');
	}
}

int main()
{
	int n; 
	cin >> n;
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
	int *mem1 = new int[n];
	int *mem2 = new int[n];
	mem1[0] = 1;
	mem2[0] = 3;
	for (int i = 1; i < n; i++)
	{
		mem1[i] = mem2[i - 1] - mem1[i - 1];
		mem2[i] = mem1[i] + 2 * mem2[i - 1];
	}
	if (n < 1)
		cout << "0";
	else
		cout << mem2[n - 1];
}