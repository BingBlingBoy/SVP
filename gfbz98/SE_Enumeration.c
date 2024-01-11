#include "SE_Enumeration.h"
#include "variables.h"
#include "GramSchmidt.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

extern int size;

float * sum_of_coeff(float **lattice_basis, float v[], int lower, int upper) { // Performs the sum of the multiplication of scalar value of v and basis vector
    
    
    int array_size = size;
    float *result = malloc(sizeof(array_size));
    float *x = malloc(sizeof(array_size));

    while (lower <= upper) {
        if (lower == 1) {
            result = scalar_vector_multiplication(v[lower-1], lattice_basis[lower-1], array_size);
        }
        else {
            x = scalar_vector_multiplication(v[lower-1], lattice_basis[lower-1], array_size);
            result = vector_addition(result, x, array_size);
        }
        lower += 1;
    }

    return result; 
}

float sum_of_mu(float (*list_of_coeff)[size], float v[], int lower, int upper) { // Performs the sum of the multiplication of Gram schmidt coefficient and element v_i
    float result = 0;
    
    while (lower <= upper) {
        result += v[lower-1] * list_of_coeff[lower-1][lower-2];
        lower += 1;
    }
    return result;
}

float * SE_enumeration(float **matrix_basis, float (*p_list_of_coeff)[size], float v_list[]) {
    int array_size = size;
    int A = 10;

    int last = array_size - 1;
    float v[array_size];
    for (int i = 0; i < array_size; i++) {
        if (i == 0) {
            v[i] = 1.0;
        } else {
            v[i] = 0.0;
        }
    }
    float p[array_size];
    memset(p, 0.0, sizeof(p));
    float c[array_size];
    memset(c, 0.0, sizeof(c));
    float w[array_size];
    memset(w, 0.0, sizeof(w));
    float *s = malloc(sizeof(array_size));

    int k = 1;
    int last_nonzero = 1;
    float R = pow(A, 2);

    while (true) {
        float first_calc = pow(v[k-1] - c[k-1], 2);
        p[k-1] = p[k] + (first_calc * v_list[k-1]);

        if (p[k-1] < R) {
            if (k == 1) {
                R = p[k-1];
                s = sum_of_coeff(matrix_basis, v, 1, array_size);
            }
            else {
                k -= 1;
                float check = sum_of_mu(p_list_of_coeff, v, k+1, array_size);
                if (check == 0.0) {
                    c[k-1] = check;
                } 
                else {
                    c[k-1] = -(check);
                    v[k-1] = round(c[k-1]);
                    w[k-1] = 1;
                }
            }
        } 
        else {
            k += 1;
            if (k == array_size + 1) {
                return s;
            }
            if (k >= last_nonzero) {
                last_nonzero = k;
                v[k-1] = v[k-1] + 1;
            }
            else {
                if (v[k-1] > c[k-1]) {
                    v[k-1] = v[k-1] - w[k-1];
                }
                else {
                    v[k-1] = v[k-1] + w[k-1];
                }
                w[k-1] = w[k-1] + 1;
            }

        }
    } 
}
