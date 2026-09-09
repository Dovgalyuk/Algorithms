#include "array.h"
#include "task1.h"

double task1(Array *arr) {
    size_t count = array_size(arr);
    if (count == 0) {
        return 0;
    }

    double elect_cond = 0;

    for (size_t i = 0; i < count; i++) {
        double val = array_get(arr, i);

        if (val == 0) {
            return 0;
        }

        elect_cond += (1.0/val);
    }

    return 1.0/elect_cond;

}