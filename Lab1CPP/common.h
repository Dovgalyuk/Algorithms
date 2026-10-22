#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

void print_array(ostream &out, Array *arr);
Array *array_create_and_read(ifstream &input);
void print_error(const char* message, ofstream &output);

#endif
