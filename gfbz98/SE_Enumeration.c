#include "SE_Enumeration.h"
#include "variables.h"

extern int size;

float sum_of_coeff(float (*list_of_coeff)[size], float v[], int lower, int upper) {
     
    int result = 0;
    float mu = 1;

    while (lower <= upper) {
        if (list_of_coeff[lower][lower-1] != 0) {
            mu = list_of_coeff[lower][lower-1];
        }
        result += v[lower-1] * mu;
        lower += 1;
    }

    return result; 
}
