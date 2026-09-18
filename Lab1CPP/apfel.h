#ifndef APFEL_H
#define APFEL_H

#include "array.h"
#include <istream>

Array* read_array(std::istream& stream);

void process_task1(Array* arr);

void process_task2(Array* arr);

#endif