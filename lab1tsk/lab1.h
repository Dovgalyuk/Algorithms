#ifndef LAB1_H
#define LAB1_H

#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

void array_print(ostream& out, Array* arr);
Array* array_create_and_read(ifstream& input, bool num = false);

#endif