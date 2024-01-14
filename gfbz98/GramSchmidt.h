typedef long double ld;

int extern size; 

float dot_product(float vector_1[], float vector_2[], int size);

float * scalar_vector_multiplication(float scalar, float vector[], int size);

float * vector_subtraction(float vector_1[], float vector_2[], int size);

float * vector_addition(float vector_1[], float vector_2[], int size);

ld mu_calculation(float vector_v[], float vector_u[], int size);

// float * gram_schmidt(float *p_list_of_vectors_v[size], float (*p_list_of_coeff)[size], float v_list[], float **matrix_basis);
// void gram_schmidt(float **matrix_basis);
