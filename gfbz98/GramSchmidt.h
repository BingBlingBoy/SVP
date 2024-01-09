typedef long double ld;



// extern float list_of_mu[];
// extern float basis_noms_squared[];
// extern float list_of_vectors_v[];

// extern float *p_list_of_mu[];
// extern float *p_basis_noms_squared[];
// extern float *p_list_of_vectors_v[];

float dot_product(float vector_1[], float vector_2[], int size);

float * scalar_vector_multiplication(float scalar, float vector[], int size);

float * vector_subtraction(float vector_1[], float vector_2[], int size);

float * vector_addition(float vector_1[], float vector_2[], int size);

ld mu_calculation(float vector_v[], float vector_u[], int size);

void gram_schmidt();
