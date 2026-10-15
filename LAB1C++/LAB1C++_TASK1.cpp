#include <iostream>
#include <fstream>
#include "array.h"

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

	Array *Arre = array_create(y);
    for (int i = 0; i < n; ++i) {
        int value;
        filetask1 >> value;

        array_set(Arre, i, value);
    }

    short int count2 = 0, count3 = 0, count4 = 0, count5 = 0;
   for (size_t i = 0; i < array_size(Arre); ++i) {
        int num = array_get(Arre, i);

        if (num == 2) count2++;
        if (num == 3) count3++;
        if (num == 4) count4++;
        if (num == 5) count5++;
    }

	cout << "Quantity 2: " << count2 << endl;
	cout << "Quantity 3: " << count3 << endl;
	cout << "Quantity 4: " << count4 << endl;
	cout << "Quantity 5: " << count5 << endl;

	array_delete(Arre);
}