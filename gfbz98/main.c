#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GramSchmidt.h"
#include "SE_Enumeration.h"
#include "variables.h"
#include "ErrorChecking.h"
#include "result_to_file.h"


#define MAX(a,b) (((a)>(b))?(a):(b))

int main(int argc, char** argv) {
    // Creating Lattice Basis
    int dim = error_checking_arg(argc, argv);
    if (dim == 0) {
        return 1;
    }    
     
    float (*lattice_basis)[dim] = calloc(dim, sizeof(*lattice_basis));

    int new_row = 0;
    int new_col = 0;
    for (int i = 1; i < argc; i++) {
        if (strchr(argv[i], ']') != NULL) {
            remove_all_chars(argv[i], ']');
            lattice_basis[new_row][new_col] = atof(argv[i]);
            new_row += 1;
            new_col = 0;
            continue;
        }
        
        if (strchr(argv[i], '[') != NULL) {
            remove_all_chars(argv[i], '[');
        } 
        lattice_basis[new_row][new_col] = atof(argv[i]);
        new_col += 1;
    }
    
    int A = 100;

    int array_size = dim;
    global_array_size(array_size); 

    float *p_basis_norms_squared = malloc(sizeof(array_size));
    float *p_list_of_vectors_v[array_size];
    for (int i = 0; i < array_size; i++) {
        p_list_of_vectors_v[i] = malloc(sizeof(array_size));
    }
    float (*p_list_of_coeff)[array_size] = calloc(array_size, sizeof *p_list_of_coeff); // From https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
   
    // Gram Schmidt
    int size_list_vector = 0; 
    for (int i = 0; i < array_size; i++) {
        if (i == 0) {
            float *v = lattice_basis[i];
            p_list_of_vectors_v[i] = v;
            size_list_vector += 1;
            continue;
        }

        float *u = lattice_basis[i];
        float *overall_proj = malloc(sizeof(array_size));
        for (int j = 0; j < size_list_vector; j++) {
            
            float mu = mu_calculation(p_list_of_vectors_v[j], u, array_size);

            p_basis_norms_squared[j] = dot_product(p_list_of_vectors_v[j], p_list_of_vectors_v[j], array_size);

            p_list_of_coeff[i+1][j+1] = mu;

            float *proj_u = malloc(sizeof(array_size));
            proj_u = scalar_vector_multiplication(mu, p_list_of_vectors_v[j], array_size);

            if (j == 0){
                overall_proj = proj_u;
            } else {
                memset(overall_proj, 0, array_size);
                overall_proj = vector_addition(overall_proj, proj_u, array_size);
            }
        }
        float *v = malloc(sizeof(array_size));
        v = vector_subtraction(overall_proj, u, array_size);
        p_list_of_vectors_v[i] = v;
        size_list_vector += 1;
    }


    
    //SE Euneration
    int last = dim - 1;
    float v[array_size];
    float v_min;
    for (int i = 0; i < array_size; i++) {
        if (i == 0.0) {
            v[i] = 1.0;
            // v_min[i] = 1.0;
        } else {
            v[i] = 0.0;
            // v_min[i] = 0.0;
        }
    }
    float l[array_size];
    memset(l, 0.0, sizeof(l));
    float c[array_size];
    memset(c, 0.0, sizeof(c));
    float Delta[array_size];
    memset(Delta, 0.0, sizeof(Delta));
    float delta[array_size];
    memset(delta, 0.0, sizeof(delta));
    float u[array_size];
    memset(u, 0.0, sizeof(u));
    float s = 1.0;

    int k = 1;
    int n = last - 1;

    while (k < n) {
        l[k-1] = l[k] + (pow((v[k-1] + c[k-1]), 2) * pow(p_basis_norms_squared[k-1], 2));
        if (l[k-1] < A) {
            if (k > 1) {
                k -= 1;
                c[k-1] = sum_of_coeff(p_list_of_coeff,  v, k, n);
                v[k-1] = ceil(-c[k-1]);
                u[k-1] = ceil(-c[k-1]);
                Delta[k-1] = 0.0;

                if (v[k-1] > -c[k-1]) {
                    delta[k-1] = -1;
                } else {
                    delta[k-1] = -1;
                }
            } else {
                A = l[k-1];
                v_min = v[k-1];
            }
        } else {
            k += 1;
            s = MAX(s, k);
            if (k < s) {
                Delta[k-1] = -Delta[k-1];
            }
            if (Delta[k-1] * delta[k-1] >= 0) {
                v[k-1] = u[k-1] + delta[k-1];
            }
        }
    }

    printf("%lf\n", v_min);
    free(p_basis_norms_squared);
    free(p_list_of_coeff);

    int write_to_file = res_to_file(v_min);
    if (write_to_file == 1) {
        return 1;
    }

    return 0;
}

