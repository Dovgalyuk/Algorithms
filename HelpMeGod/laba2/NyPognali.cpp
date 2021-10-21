#include <iostream>
#include "stack.h"
#include "vector.h"
#include <string>
#include <cctype>
#include <math.h>
#include <stdlib.h>

using namespace std;

int pervSlog(char* primer, int i) {
	int j = 0; int h = 1;
	while (1) {
		if (i == -1) {
			return j;
		}
		else {
			if (isdigit(primer[i])) {
				j = j + (primer[i] - '0') * h;
				h = h * 10;
				i--;
			}
			else {
				return j;
			}
		}
	}
	return j;
}

int ftorSlog(char* primer, int i, int size) {
	while (isdigit(primer[i]) && i < size) {
		i++;
	}
	int j = 0; int h = 1; i--;
	while (isdigit(primer[i])) {
		j = j + (primer[i] - '0') * h;
		h = h * 10;
		i--;
	}
	return j;
}

int dlinaChisla(int i) {
	int j = 0;
	while (i > 0) {
		i = i / 10;
		j++;
	}
	return j;
}

void zapol(char* primer, int m, int i, int& dlina) {
	dlina = dlinaChisla(m);
	int man = dlina;
	while (man > 0) {
		int o = pow(10, man - 1);
		primer[i] = m / o + '0';
		m = m % o;
		i++;
		man--;
	}
}

bool check1(char* primer, int size) {
	for (int i = 0; i < size; i++) {
		if (primer[i] == '*' || primer[i] == '/') {
			return true;
		}
	}
	return false;
}

int resh1(char* primer, Stack* sta, int& m, int& size, int& i) {
	if (primer[i] == '*' || primer[i] == '/') {
		if (primer[i] == '*') {
			m = pervSlog(primer, i - 1) * ftorSlog(primer, i + 1, size);
			stack_push(sta, m);
			int c = dlinaChisla(pervSlog(primer, i - 1));
			int d = dlinaChisla(ftorSlog(primer, i + 1, size));
			int dlina = 0;
			zapol(primer, m, i - c, dlina);
			int b = i + d + 1;
			for (int a = i - c + dlina; b < size; a++) {
				primer[a] = primer[b];
				b++;
			}
			i = i - c + dlina - 1;
			size = size - c - d - 1 + dlina;
		}
		else if (primer[i] == '/') {
			m = pervSlog(primer, i - 1) / ftorSlog(primer, i + 1, size);
			stack_push(sta, m);
			int c = dlinaChisla(pervSlog(primer, i - 1));
			int d = dlinaChisla(ftorSlog(primer, i + 1, size));
			int dlina = 0;
			zapol(primer, m, i - c, dlina);
			int b = i + d + 1;
			for (int a = i - c + dlina; b < size; a++) {
				primer[a] = primer[b];
				b++;
			}
			i = i - c + dlina;
			size = size - c - d - 1 + dlina;
		}
	}
	if (check1(primer, size) == false) {
		i = 0;
	}
	return 0;
}

int resh2(char* primer, Stack* sta, int& m, int& size, int& i) {
	if (primer[i] == '+') {
		m = pervSlog(primer, i - 1) + ftorSlog(primer, i + 1, size);
		stack_push(sta, m);
		int c = dlinaChisla(pervSlog(primer, i - 1));
		int d = dlinaChisla(ftorSlog(primer, i + 1, size));
		int dlina = 0;
		zapol(primer, m, i - c, dlina);
		int b = i + d + 1;
		for (int a = i - c + dlina; b < size; a++) {
			primer[a] = primer[b];
			b++;
		}
		i = i - c + dlina;
		size = size - c - d - 1 + dlina;
	}
	if (primer[i] == '-') {
		m = pervSlog(primer, i - 1) - ftorSlog(primer, i + 1, size);
		stack_push(sta, m);
		int c = dlinaChisla(pervSlog(primer, i - 1));
		int d = dlinaChisla(ftorSlog(primer, i + 1, size));
		int dlina = 0;
		zapol(primer, m, i - c, dlina);
		int b = i + d + 1;
		for (int a = i - c + dlina; b < size; a++) {
			primer[a] = primer[b];
			b++;
		}
		i = i - c + dlina;
		size = size - c - d - 1 + dlina;
	}
	return 0;
}

bool check(char* primer, int size) {
	for (int i = 0; i < size; i++) {
		if (primer[i] == '*' || primer[i] == '/' || primer[i] == '+' || primer[i] == '-') {
			return true;
		}
	}
	return false;
}



int main() {
	char primer[200];
	int size = 0;
	cout << "Input primer: ";
	do
	{
		primer[size] = getchar();
		if (primer[size] == '\n') break;
		size++;
	} while (true);
	Stack* sta = stack_create();
	int m = 0;
	while (check(primer, size)) {
		int i = 0;
		while (i < size) {
			if (check1(primer, size)) {
				resh1(primer, sta, m, size, i);
			}
			else {
				resh2(primer, sta, m, size, i);
			}
			i++;
		}
	}
	cout << "\n" << stack_get(sta);
	stack_delete(sta);
}
