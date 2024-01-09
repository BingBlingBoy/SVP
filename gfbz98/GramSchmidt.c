#include "GramSchmidt.h" 
#include "variables.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

int extern size;

float dot_product(float vector_1[], float vector_2[], int array_size) {
    float result = 0;

    for (int i = 0; i < array_size; i++) {
        result += (vector_1[i] * vector_2[i]);
    }
    return result;
}

float * vector_addition(float vector_1[], float vector_2[], int array_size) {
    float *result = malloc(sizeof(array_size));
    if (result == NULL) exit(1);
    // float result[array_size];

    for (int i = 0; i < array_size; i++) {
        float value = vector_1[i] + vector_2[i];
        result[i] = value;
    }

    return result;
}

float * vector_subtraction(float vector_1[], float vector_2[], int array_size) {
    float *result = malloc(sizeof(array_size));
    if (result == NULL) exit(1);
    // float result[array_size];

    for (int i = 0; i < array_size; i++) {
        float value = vector_1[i] - vector_2[i];
        result[i] = value;
    }

    return result;
}

float * scalar_vector_multiplication(float scalar, float vector[], int array_size) {
    float *result = malloc(sizeof(array_size));
    if (result == NULL) exit(1);
    // float result[array_size];

    for (int i = 0; i < array_size; i++) {
        float value = scalar * (float)vector[i];
        result[i] = value;
    }

    return result;
}

ld mu_calculation(float vector_v[], float vector_u[], int array_size) {
    float dp = dot_product(vector_v, vector_u, array_size);
    float norm = dot_product(vector_v, vector_v, array_size);

    return dp/norm;
}

void gram_schmidt() {
   //  int array_size = size;
   //  float *p_basis_norms_squared = malloc(sizeof(array_size));
   //  float *p_list_of_vectors_v[array_size];
   //  for (int i = 0; i < array_size; i++) {
   //      p_list_of_vectors_v[i] = malloc(sizeof(array_size));
   //  }
   //  float (*p_list_of_coeff)[array_size] = calloc(array_size, sizeof *p_list_of_coeff); // From https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
   // 
   //  // Gram Schmidt
   //  int size_list_vector = 0; 
   //  for (int i = 0; i < array_size; i++) {
   //      if (i == 0) {
   //          float *v = lattice_basis[i];
   //          p_list_of_vectors_v[i] = v;
   //          size_list_vector += 1;
   //          continue;
   //      }
   //
   //      float *u = lattice_basis[i];
   //      float *overall_proj = malloc(sizeof(array_size));
   //      for (int j = 0; j < size_list_vector; j++) {
   //          
   //          float mu = mu_calculation(p_list_of_vectors_v[j], u, array_size);
   //
   //          p_basis_norms_squared[j] = dot_product(p_list_of_vectors_v[j], p_list_of_vectors_v[j], array_size);
   //
   //          p_list_of_coeff[i+1][j+1] = mu;
   //
   //          float *proj_u = malloc(sizeof(array_size));
   //          proj_u = scalar_vector_multiplication(mu, p_list_of_vectors_v[j], array_size);
   //
   //          if (j == 0){
   //              overall_proj = proj_u;
   //          } else {
   //              memset(overall_proj, 0, array_size);
   //              overall_proj = vector_addition(overall_proj, proj_u, array_size);
   //          }
   //      }
   //      float *v = malloc(sizeof(array_size));
   //      v = vector_subtraction(overall_proj, u, array_size);
   //      p_list_of_vectors_v[i] = v;
   //      size_list_vector += 1;
   //  }
}
