#include "variables.h"

extern int size;

float * sum_of_coeff(float **matrix_basis, float v[], int lower, int upper);

float sum_of_mu(float (*list_of_coeff)[size], float v[], int lower, int upper); 

float * SE_enumeration(float **matrix_basis, float (*p_list_of_coeff)[size], float v_list[]);
