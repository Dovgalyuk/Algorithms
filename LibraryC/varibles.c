#include "varibles.h"

typedef struct Varibles {
    Array* data;
} Varibles;

Varibles* vars_create(FFree f) {
    Varibles* vars = (Varibles*)malloc(sizeof(Varibles));
    if(vars == NULL)
        return NULL;

    vars->data = array_create(4, f);
    if(vars->data == NULL) {
        free(vars);
        return NULL;
    }
    
    return vars;
}

void vars_set(Varibles* vars, const Data data, const size_t var_number) {
    if (vars == NULL )
        return;
    
    array_set(vars->data, var_number - 1, data);   
}

Data vars_get(Varibles* vars, const size_t var_number) {
    if (vars == NULL)
        return NULL;

    return array_get(vars->data, var_number - 1);
}

void vars_delete(Varibles* vars) {
    if(vars == NULL) 
        return;

    array_delete(vars->data);
    free(vars);
}