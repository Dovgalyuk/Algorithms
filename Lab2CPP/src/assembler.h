#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include "operations.h"
#include "stack.h"

char *readExpression(FILE *input);
bool checkEnd(const char *element);

void parseExpression(const char *p, Stack *stack);

#endif