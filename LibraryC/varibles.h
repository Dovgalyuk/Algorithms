#ifndef VARIBLES_H
#define VARIBLES_H

#include "array.h"

// Stores pointer to custom user data
typedef void* Data;
// Custom function to free user pointers on delete
typedef void (FFree)(void*);

// Varibles structure
typedef struct Varibles Varibles;

#ifdef __cplusplus
extern "C" {
#endif

// Varibles empty create
Varibles* vars_create();

// Set one of Varibles
void vars_set();

// Get one of Varibles
Data vars_get();

// Delete Varibles
void vars_delete();

#ifdef __cplusplus
}
#endif

#endif