#include "GramSchmidt.h" 
#include "variables.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

int extern size;

float *list_of_vectors_v;
float *final_v_list;
float *list_of_coeff;

float dot_product(float vector_1[], float vector_2[], int array_size) { // Calculates the dot product of 2 given vectors
    float result = 0;

    for (int i = 0; i < array_size; i++) {
        result += (vector_1[i] * vector_2[i]);
    }
    return result;
}

float * vector_addition(float vector_1[], float vector_2[], int array_size) { // Performs vector addition of 2 given vectors
    float *result = malloc(array_size * sizeof(float));
    if (result == NULL) exit(1);
    // float result[array_size];

    for (int i = 0; i < array_size; i++) {
        float value = vector_1[i] + vector_2[i];
        result[i] = value;
    }

    return result;
}

float * vector_subtraction(float vector_1[], float vector_2[], int array_size) { // Performs vector subtraction of 2 given vectors
    float *result = malloc(array_size * sizeof(float));
    if (result == NULL) exit(1);

    for (int i = 0; i < array_size; i++) {
        float value = vector_1[i] - vector_2[i];
        result[i] = value;
    }

    return result;
}

float * scalar_vector_multiplication(float scalar, float vector[], int array_size) { // Performs multiplication of a scalar and vector
    float *result = malloc(array_size * sizeof(float));
    if (result == NULL) exit(1);

    for (int i = 0; i < array_size; i++) {
        float value = scalar * vector[i];
        result[i] = value;
    }
    // float *result = calloc(array_size, sizeof(*result));   
    return result;
}

ld mu_calculation(float vector_v[], float vector_u[], int array_size) { // Calculates mu_i_j which is the coefficient of the gram schmidt orthogonalisation
    float dp = dot_product(vector_v, vector_u, array_size);
    float norm = dot_product(vector_v, vector_v, array_size);
    
    return dp/norm;
}

// void gram_schmidt(float **matrix_basis) {
//     int array_size = size;
//
//     float *p_list_of_vectors_v[array_size];
//     for (int i = 0; i < array_size; i++) { // Storing an array of arrays
//         p_list_of_vectors_v[i] = malloc(sizeof(array_size));
//         free(p_list_of_vectors_v[i]);
//     }
//     float (*p_list_of_coeff)[array_size] = calloc(array_size, sizeof *p_list_of_coeff); // From https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
//
//     float *v_list = malloc(array_size * sizeof(float));
//     
//     // Gram Schmidt
//     int size_list_vector = 0; 
//     for (int i = 0; i < array_size; i++) {
//         if (i == 0) {
//             float *v = matrix_basis[i];
//             p_list_of_vectors_v[i] = v;
//             size_list_vector += 1;
//             continue;
//         }
//
//         float *u = matrix_basis[i];
//         float *overall_proj;
//         for (int j = 0; j < size_list_vector; j++) {
//             
//             float mu = mu_calculation(p_list_of_vectors_v[j], u, array_size);
//
//             p_list_of_coeff[i][j] = mu;
//
//             float *proj_u;
//             proj_u = scalar_vector_multiplication(mu, p_list_of_vectors_v[j], array_size);
//
//             if (j == 0){
//                 overall_proj = proj_u;
//             } else {
//                 // memset(overall_proj, 0, array_size);
//                 overall_proj = vector_addition(overall_proj, proj_u, array_size);
//             }
//         }
//         float *v;
//         v = vector_subtraction(u, overall_proj, array_size);
//         p_list_of_vectors_v[i] = v;
//         size_list_vector += 1;
//         free(overall_proj);
//     }
//     
//     // Produces the orthogonolised vectors of the basis vectors and stores them in V_List
//     for (int i = 0; i < array_size; i++) {
//         float result = dot_product(p_list_of_vectors_v[i], p_list_of_vectors_v[i], array_size);
//         v_list[i] = result;
//     }
//
//     final_v_list = v_list;
//     list_of_coeff = p_list_of_coeff;
//     list_of_vectors_v = p_list_of_vectors_v;
// }
