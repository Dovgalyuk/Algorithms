#ifndef LAB1CPP_H
#define LAB1CPP_H

#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

void array_print(ostream& out, Array* arr);
Array* array_create_and_read(ifstream& input);

#endif