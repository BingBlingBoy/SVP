#include "LLL.h"
#include "variables.h"
#include <stdio.h>
#include <stdlib.h>
#include "GramSchmidt.h"
#include <math.h>
#include <string.h>

extern int size;

#define MAX(a,b) (((a)>(b))?(a):(b))

float ** LLL(float **matrix_basis) {
    
    int array_size = size;

    float *p_list_of_vectors_v[array_size];
    for (int i = 0; i < array_size; i++) { // Storing an array of arrays
        p_list_of_vectors_v[i] = malloc(sizeof(array_size));
        free(p_list_of_vectors_v[i]);
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
        float *overall_proj;
        for (int j = 0; j < size_list_vector; j++) {
            
            float mu = mu_calculation(p_list_of_vectors_v[j], u, array_size);
            p_list_of_coeff[i][j] = mu;

            float *proj_u;
            proj_u = scalar_vector_multiplication(mu, p_list_of_vectors_v[j], array_size);
            if (j == 0){
                overall_proj = proj_u;
            } else {
                // memset(overall_proj, 0, array_size);
                overall_proj = vector_addition(overall_proj, proj_u, array_size);
            }
        }
        float *v;
        v = vector_subtraction(u, overall_proj, array_size);
        p_list_of_vectors_v[i] = v;
        size_list_vector += 1;
        free(overall_proj);
    }

    // Produces the orthogonolised vectors of the basis vectors and stores them in V_List
    for (int i = 0; i < array_size; i++) {
        float result = dot_product(p_list_of_vectors_v[i], p_list_of_vectors_v[i], array_size);
        v_list[i] = result;
    }

    float delta = 0.75;
    int k = 3;

    while (k <= size) {
        for (int j = k - 1; j > 0 ; j--) {
            float x = p_list_of_coeff[k-1][j-1];

            if (fabsf(x) > 0.5) {
                float *svm = scalar_vector_multiplication(round(x), matrix_basis[j-1], array_size);
                float *replacement_basis = vector_subtraction(matrix_basis[k-1], svm, array_size);

                for (int z = 0; z < array_size; z++) {
                    matrix_basis[k-1][z] = replacement_basis[z];
                }

                // Clearing the data in the heap for new values
                for (int i = 0; i < array_size; i++) { // Storing an array of arrays
                    memset(p_list_of_vectors_v, 0, array_size);
                }
                memset(v_list, 0.0, sizeof(v_list));
                memset(p_list_of_coeff, 0.0, sizeof(float) * array_size * array_size);
                
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
                    float *overall_proj;
                    for (int j = 0; j < size_list_vector; j++) {
                        
                        float mu = mu_calculation(p_list_of_vectors_v[j], u, array_size);
                        p_list_of_coeff[i][j] = mu;

                        float *proj_u;
                        proj_u = scalar_vector_multiplication(mu, p_list_of_vectors_v[j], array_size);
                        if (j == 0){
                            overall_proj = proj_u;
                        } else {
                            // memset(overall_proj, 0, array_size);
                            overall_proj = vector_addition(overall_proj, proj_u, array_size);
                        }
                    }
                    float *v;
                    v = vector_subtraction(u, overall_proj, array_size);
                    p_list_of_vectors_v[i] = v;
                    size_list_vector += 1;
                    free(overall_proj);
                }

                // Produces the orthogonolised vectors of the basis vectors and stores them in V_List
                for (int i = 0; i < array_size; i++) {
                    float result = dot_product(p_list_of_vectors_v[i], p_list_of_vectors_v[i], array_size);
                    v_list[i] = result;
                }
            }
            
        }
        
        float dmu = p_list_of_coeff[k-1][k-2];
        float dp = dot_product(matrix_basis[k-1], matrix_basis[k-1], array_size);
        if (dp > ((delta - (pow(dmu, 2))) * dot_product(matrix_basis[k-2], matrix_basis[k-2], array_size))) {
            k += 1;
        }
        else {
            float *temp = malloc(array_size * sizeof(float));

            for (int z = 0; z < array_size; z++) {
                temp[z] = matrix_basis[k-1][z];
            }

            for (int z = 0; z < array_size; z++) {
                matrix_basis[k-1][z] = matrix_basis[k-2][z];
            }

            for (int z = 0; z < array_size; z++) {
                matrix_basis[k-2][z] = temp[z];
            }

            for (int a = 0; a < array_size; a++) {
                for (int b = 0; b < array_size; b++) {
                }
            }
            // Clearing the data in the heap for new values
            for (int i = 0; i < array_size; i++) { // Storing an array of arrays
                memset(p_list_of_vectors_v, 0, array_size);
            }
            memset(v_list, 0.0, sizeof(v_list));
            memset(p_list_of_coeff, 0.0, sizeof(float) * array_size * array_size);

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
                float *overall_proj;
                for (int j = 0; j < size_list_vector; j++) {
                    
                    float mu = mu_calculation(p_list_of_vectors_v[j], u, array_size);
                    p_list_of_coeff[i][j] = mu;

                    float *proj_u;
                    proj_u = scalar_vector_multiplication(mu, p_list_of_vectors_v[j], array_size);
                    if (j == 0){
                        overall_proj = proj_u;
                    } else {
                        // memset(overall_proj, 0, array_size);
                        overall_proj = vector_addition(overall_proj, proj_u, array_size);
                    }
                }
                float *v;
                v = vector_subtraction(u, overall_proj, array_size);
                p_list_of_vectors_v[i] = v;
                size_list_vector += 1;
                free(overall_proj);
            }

            // // Produces the orthogonolised vectors of the basis vectors and stores them in V_List
            for (int i = 0; i < array_size; i++) {
                float result = dot_product(p_list_of_vectors_v[i], p_list_of_vectors_v[i], array_size);
                v_list[i] = result;
            }
            k = MAX(k-1, 2);

        }

        free(p_list_of_coeff);
        for (int i = 0; i < array_size; i++) {
            free(p_list_of_vectors_v[i]);
        }
    }
    return matrix_basis;
}
