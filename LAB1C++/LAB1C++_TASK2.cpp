#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "The file was not found.\n"; return 1;}

    ifstream filetask1(argv[1]);
    if(!filetask1) {cout << "Error!"; return 1;}
   
    int n;
    size_t y; 
    filetask1 >> n;

	if (n < 0) {y = 0;}
	else {y = static_cast<size_t>(n);}

    vector<int> Arre;
    Arre.resize(y);
	for (int i = 0; i < n; ++i){
		filetask1 >> Arre[i];
	}
    int maxSum = 0;
	for (int i = 0; i + 4 < n; ++i) {
		int currentSum = 0;
		for (int j = i; j < i + 5; ++j){
			currentSum += Arre[j];
		}
		if (currentSum > maxSum) {
			maxSum = currentSum;
		}
		}
	cout << "The maximum sum of 5 adjacent elements: " << maxSum << endl;
}