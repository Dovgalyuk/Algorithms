#ifndef MACHINE_H
#define MACHINE_H

#include "stack.h"
#include <string>

using namespace std;

struct Instruction;
struct Machine;

Machine* machine_create();
void machine_delete(Machine* machine);
Machine* machine_read(Machine* machine, string file);
Machine* machine_run(Machine* machine);

void bipush(Machine* machine);
void pop(Machine* machine);
void imul(Machine* machine);
void iand(Machine* machine);
void ior(Machine* machine);
void ixor(Machine* machine);
void iadd(Machine* machine);
void isub(Machine* machine);

void iload(Machine* machine);
void istore(Machine* machine);

void swap_stack(Machine* machine);
void invokestatic(Machine* machine);
void return_(Machine* machine);

#endif
