#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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
    short int count2 = 0, count3 = 0, count4 = 0, count5 = 0;
    for (int num : Arre){
		if (num == 2) count2++;}
	Arre.erase(remove(Arre.begin(), Arre.end(), 2), Arre.end());

	for (int num : Arre){
		if (num == 3) count3++;}
	Arre.erase(remove(Arre.begin(), Arre.end(), 3), Arre.end());

	for (int num : Arre){
		if (num == 4) count4++;}
	Arre.erase(remove(Arre.begin(), Arre.end(), 4), Arre.end());

	for (int num : Arre){
		if (num == 5) count5++;}
	Arre.erase(remove(Arre.begin(), Arre.end(), 5), Arre.end());

	cout << "Quantity 2: " << count2 << endl;
	cout << "Quantity 3: " << count3 << endl;
	cout << "Quantity 4: " << count4 << endl;
	cout << "Quantity 5: " << count5 << endl;
}