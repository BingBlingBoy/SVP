#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "GramSchmidt.h"
#include "SE_Enumeration.h"
#include "variables.h"
#include "ErrorChecking.h"
#include "result_to_file.h"


#define MAX(a,b) (((a)>(b))?(a):(b))

extern float list_of_mu[];
extern float list_of_vectors_v[];
extern float (*p_list_of_coeff)[];
extern float v_list[];

int main(int argc, char** argv) {
    // Creating Lattice Basis
    int dim = error_checking_arg(argc, argv);
    if (dim == 0) {
        return 1;
    }    

    float **matrix_basis; 
    matrix_basis = lattice_basis(argc, argv);
    
    int array_size = dim;
    global_array_size(array_size); 

    float *p_list_of_vectors_v[array_size];
    for (int i = 0; i < array_size; i++) {
        p_list_of_vectors_v[i] = malloc(sizeof(array_size));
    }
    float (*p_list_of_coeff)[array_size] = calloc(array_size, sizeof *p_list_of_coeff); // From https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/

    float v_list[array_size];
    
    // Gram Schmidt
    int size_list_vector = 0; 
    for (int i = 0; i < array_size; i++) {
        if (i == 0) {
            float *v = matrix_basis[i];
            p_list_of_vectors_v[i] = v;
            size_list_vector += 1;
            continue;
        }

        float *u = matrix_basis[i];
        float *overall_proj = malloc(sizeof(array_size));
        for (int j = 0; j < size_list_vector; j++) {
            
            float mu = mu_calculation(p_list_of_vectors_v[j], u, array_size);

            p_list_of_coeff[i][j] = mu;

            float *proj_u = malloc(sizeof(array_size));
            proj_u = scalar_vector_multiplication(mu, p_list_of_vectors_v[j], array_size);

            if (j == 0){
                overall_proj = proj_u;
            } else {
                // memset(overall_proj, 0, array_size);
                overall_proj = vector_addition(overall_proj, proj_u, array_size);
            }
        }
        float *v = malloc(sizeof(array_size));
        v = vector_subtraction(u, overall_proj, array_size);
        p_list_of_vectors_v[i] = v;
        size_list_vector += 1;
    }
    
    // Produces the orthogonolised vectors of the basis vectors and stores them in V_List
    for (int i = 0; i < array_size; i++) {
        float result = dot_product(p_list_of_vectors_v[i], p_list_of_vectors_v[i], array_size);
        v_list[i] = result;
    }

    // SE Enumeration    
    float *s = malloc(sizeof(array_size));
    // Produces the shortest non_zero vector
    s = SE_enumeration(matrix_basis, p_list_of_coeff, v_list);
    
    // Using the output of s, it calculates the euclidean norm vector of s
    float v_min = 0;
    for (int i = 0; i < array_size; i++) {
        float x = pow(s[i], 2);
        v_min += x;
    }
    v_min = sqrt(v_min);

    // Writing to file
    int write_to_file = res_to_file(v_min);
    if (write_to_file == 1) {
        return 1;
    }

    return 0;
}

