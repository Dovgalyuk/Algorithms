#include "array.h"
#include<iostream>
using namespace std;



void Max(int Size_,Array A_){
	int max= array_get(A_, 0);
	for (int i = 0; i < Size_; i++) {
		if ((i % 2 == 0)&&(max< array_get(A_, i))) {
			max=array_get(A_ ,i);
		}
	}
	cout << endl<<"Максимальное число из четных индексов"<<max;
}




int main() {
	setlocale(LC_ALL, "Rus");
	int Size;
	cout << "Введите размер массива: ";
	cin >> Size;
	Array A(Size);
	for (int i = 0; i < Size; i++) {
		int k;
		cin >> k;
		array_set(A, i, k);
	}
	for (int i = 0; i < Size; i++) {
		cout<<array_get(A, i)<<" ";
	}
	Max(Size, A);
}
