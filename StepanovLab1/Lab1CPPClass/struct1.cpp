
#include <iostream>
#include <fstream>
#include <limits>
#include "array.h"

using namespace std;

Data f1(const Array& prarr) {
	double sum = 0;
	size_t asize = prarr.size();

	for (size_t i = 0; i < asize; i++) {
		sum += prarr.get(i);
	}
	double average = sum / asize;

	Data felem = prarr.get(0);
	double min_diff = abs(prarr.get(0) - average);

	for (size_t i = 1; i < asize; i++) {
		double diff = abs(prarr.get(i) - average);
		if (diff < min_diff) {
			min_diff = diff;
			felem = prarr.get(i);
		}
	}
	return felem;
}

Data f2(const Array& prarr) {

	Data mdiff = numeric_limits<Data>::max();
	size_t asize = prarr.size();
	for (size_t i = 0; i < asize; i++) {
		for (size_t j = i + 1; j < asize; j++) {
			if ((prarr.get(i) % 2 == 0 && prarr.get(j) % 2 == 0) && (prarr.get(i) != prarr.get(j))) {
				Data diff = abs(prarr.get(i) - prarr.get(j));
				if (diff < mdiff) {
					mdiff = diff;
				}
			}
		}
	}
	return mdiff;
}

void printarr(const Array& prarr) {
	size_t asize = prarr.size();
	for (size_t i = 0; i < asize; i++) {
		cout << prarr.get(i) << " ";
	}
	cout << endl;
}

int main(int argc, char* argv[])
{
	size_t asize1 = 0;
	ifstream in(argv[1]);
	if (in.is_open()) {
		in >> asize1;
		if (asize1 > 0) {

			Array arr  = Array(asize1);

			int n = 0;
			for (int i = 0; i < asize1; i++) {
				in >> n;
				arr.set(i, n);
			}
			Data res1 = f1(arr);
			Data res2 = f2(arr);
			cout << res1 << " " << res2 << endl;
		}
		in.close();
	}
	return 0;
}